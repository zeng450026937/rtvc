#include "yealink/rtc/audio_engine_delegate.h"

#include <map>
#include <string>
#include <vector>

#include "api/audio/audio_frame.h"
#include "rtc_base/checks.h"
#include "rtc_base/event.h"
#include "rtc_base/logging.h"
#include "rtc_base/thread.h"
#include "rtc_base/time_utils.h"

#include "yealink/third_party/ipvp/include/service_ipvp.h"

namespace yealink {
namespace {

int audio_engine_log_hub(void* priv,
                         int module,
                         int log_level,
                         const char* fmt,
                         ...) {
  switch (log_level) {
    case 0:
    case 1:
    case 2:
    case 3:
      break;
    case 4:
      break;
    case 5:
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    default:
      break;
  }
}

int audio_engine_configuration_hub(void* priv,
                                   const char* name,
                                   void* value,
                                   size_t vallen) {
  RTC_DCHECK(priv);
  AudioEngineDelegate* audio_engine_delegate =
      static_cast<AudioEngineDelegate*>(priv);

  int* result_value = static_cast<int*>(value);
  int default_value = *result_value;

  RTC_LOG(LS_INFO) << "AudioEngine require configuration." << name << ": "
                   << *result_value;
  return 0;
}

int audio_engine_event_hub(void* priv,
                           int event,
                           unsigned int wparam,
                           unsigned long lparam,
                           const void* data,
                           size_t data_len) {}

int global_fd_count = 0;
rtc::Event global_fd_event;
std::map<int, TransportDelegate*> global_binded_transports;

void BindTransport(int fd, TransportDelegate* transport) {
  global_binded_transports.emplace(fd, transport);
}
void UnBindTransport(int fd) {
  global_binded_transports.erase(fd);
}

int TouchTransport(fd_set* readfds) {
  std::vector<int> touched_fds;

  for (const auto& binded : global_binded_transports) {
    if (FD_ISSET(binded.first, readfds) == 0) {
      continue;
    }
    touched_fds.push_back(binded.first);
  }

  FD_ZERO(readfds);

  if (!touched_fds.empty()) {
    for (const auto& touched : touched_fds) {
      FD_SET(touched, readfds);
    }
  }

  return static_cast<int>(touched_fds.size());
}
TransportDelegate* FindTransport(int fd) {
  auto it = global_binded_transports.find(fd);

  if (it != global_binded_transports.end()) {
    return it->second;
  }

  return nullptr;
}

int audio_engine_socket(int af, int type, int protocol) {
  return ++global_fd_count;
}
int audio_engine_setsockopt(int sockfd,
                            int level,
                            int optname,
                            const char* optval,
                            int optlen) {
  // nothing to do as we will delegate all traffic to webrtc voice channel
  return 0;
}
int audio_engine_bind(int sockfd, const struct sockaddr* addr, int addrlen) {
  rtc::SocketAddress address;
  address.FromSockAddr(*(struct sockaddr_in*)addr);

  TransportDelegate* transport =
      AudioEngineDelegate::Instance()->FindTransport(address);

  RTC_DCHECK(transport) << "Failed to bind socket with address: "
                        << address.ToString();

  BindTransport(sockfd, transport);
}
int audio_engine_listen(int sockfd, int backlog) {
  return 0;
}
int audio_engine_accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
  return 0;
}
int audio_engine_connect(int sockfd, const struct sockaddr* addr, int addrlen) {
  return 0;
}
int audio_engine_close(int sockfd) {
  UnBindTransport(sockfd);
  return 0;
}
int audio_engine_select(int nfds,
                        fd_set* readfds,
                        fd_set* writefds,
                        fd_set* exceptfds,
                        struct timeval* timeout) {
  int recv_count = 0;
  int wait_time =
      static_cast<int>(timeout->tv_sec * 1000 + timeout->tv_usec / 1000);
  //毫秒
  bool is_timeout = false;

  while (!is_timeout && recv_count == 0) {
    recv_count = TouchTransport(readfds);

    if (recv_count == 0) {
      is_timeout = !global_fd_event.Wait(wait_time);
      global_fd_event.Reset();
    }
  }

  return recv_count;
}
int audio_engine_sendto(int sockfd,
                        const void* buf,
                        size_t len,
                        int flags,
                        const struct sockaddr* dest_addr,
                        int addrlen) {
  return audio_engine_send(sockfd, buf, len, flags);
}
int audio_engine_send(int sockfd, const void* buf, size_t len, int flags) {
  auto transport = FindTransport(sockfd);
  RTC_DCHECK(transport) << "Send packet on unknown transport.";

  transport->SendPacket(reinterpret_cast<const uint8_t*>(buf), len);

  return len;
}
int audio_engine_recvfrom(int sockfd,
                          void* buf,
                          size_t len,
                          int flags,
                          struct sockaddr* src_addr,
                          int* addrlen) {
  return audio_engine_recv(sockfd, buf, len, flags);
}
int audio_engine_recv(int sockfd, void* buf, size_t len, int flags) {
  auto transport = FindTransport(sockfd);
  RTC_DCHECK(transport) << "Recv packet on unknown transport.";

  absl::optional<rtc::CopyOnWriteBuffer> packet = transport->Take();

  RTC_DCHECK(packet) << "No buffered packet in this transport.";
  // use cdata() to avoid making data copied
  buf = const_cast<char*>(packet.value().cdata<char>());
  len = packet.value().size();

  return len;
}

constexpr int64_t kPollDelayMs = 10;

int kAudioEngineDSPHz = 100;

int kAudioEngineFrameFormat = IPVP_AUDIO_FORMAT_DEFAULT;
int kAudioEngineSampleRate = IPVP_AUDIO_SAMPLERATE_DEFAULT;
int kAudioEngineSampleSize = IPVP_AUDIO_BPS_DEFAULT;
int kAudioEngineChannels = IPVP_AUDIO_CHAN_DEFAULT;

int kAudioEngineSamples = kAudioEngineSampleRate / 100;  // in 10ms
int kAudioEngineFrameSize = kAudioEngineSamples * sizeof(int16_t);

std::string tune_file =
    "D:\\workspace\\rtvc\\src\\yealink\\third_party\\ipvp\\assets\\ipvp.tune";

enum {
  MSG_INIT_ENGINE = 0,
};

void InitAudioFrame(webrtc::AudioFrame* frame) {
  frame->sample_rate_hz_ = kAudioEngineSampleRate;
  frame->samples_per_channel_ = kAudioEngineSamples;
  frame->num_channels_ = kAudioEngineChannels;
}

}  // namespace

AudioEngineDelegate* AudioEngineDelegate::Instance() {
  static AudioEngineDelegate* const audio_engine_delegate =
      new AudioEngineDelegate();
  return audio_engine_delegate;
}

AudioEngineDelegate::AudioEngineDelegate()
    : reschedule_at_(rtc::TimeMillis() + kPollDelayMs) {
  RTC_LOG(LS_INFO) << "AudioEngineDelegate()";
  Init();
}
AudioEngineDelegate::~AudioEngineDelegate() {
  RTC_LOG(LS_INFO) << "~AudioEngineDelegate()";
}

void AudioEngineDelegate::RegisterTransport(TransportDelegate* transport) {
  transports_.emplace(transport->hash(), transport);
}
void AudioEngineDelegate::DeRegisterTransport(TransportDelegate* transport) {
  transports_.erase(transport->hash());
}

TransportDelegate* AudioEngineDelegate::FindTransport(size_t hash) {
  auto it = transports_.find(hash);

  if (it != transports_.end()) {
    return it->second;
  }

  return nullptr;
}
TransportDelegate* AudioEngineDelegate::FindTransport(
    const rtc::SocketAddress& address) {
  return FindTransport(address.Hash());
}

void AudioEngineDelegate::OnMessage(rtc::Message* msg) {
  switch (msg->message_id) {
    case MSG_INIT_ENGINE: {
      ready_ = !ipvp_alive(0);

      if (!ready_) {
        int64_t now = rtc::TimeMillis();
        if (reschedule_at_ < now) {
          reschedule_at_ = now;
        }

        ipvp_dev_framing2(out_frame_.mutable_data(), kAudioEngineFrameSize,
                          in_frame_.mutable_data(), kAudioEngineFrameSize,
                          nullptr, 0);

        rtc::Thread::Current()->PostAt(RTC_FROM_HERE, reschedule_at_, this,
                                       MSG_INIT_ENGINE);
        // Loop after next will be kPollDelayMs later.
        reschedule_at_ += kPollDelayMs;
      } else {
        Ready();
      }
    } break;
    default:
      RTC_NOTREACHED() << "Not implemented";
      break;
  }
}
void AudioEngineDelegate::OnPacketReceived() {
  global_fd_event.Set();
}

int AudioEngineDelegate::Init() {
  // init dev with default frame format, , 32khz 1channel 16bit
  ipvp_dev_init(&kAudioEngineSampleRate, &kAudioEngineChannels,
                &kAudioEngineDSPHz);

  // set framing
  ipvp_frame_t spk_frame_format = {
      kAudioEngineFrameFormat, kAudioEngineSampleRate, kAudioEngineSampleSize,
      kAudioEngineChannels};
  ipvp_frame_t mic_frame_format = {
      kAudioEngineFrameFormat, kAudioEngineSampleRate, kAudioEngineSampleSize,
      kAudioEngineChannels};
  ipvp_dev_set_framing(&spk_frame_format, &mic_frame_format, nullptr);

  // init lib
  const char* args[] = {"ipvp",  "-m", "stdout",         "-l",
                        "any=6", "-p", tune_file.c_str()};
  ipvp_init_t init = {7,       args,
                      nullptr, audio_engine_log_hub,
                      this,    audio_engine_configuration_hub,
                      this,    audio_engine_event_hub,
                      this};
  ipvp_lib_init(&init, sizeof(init));

  // init transport
  ipvp_socket_t socketConfig = {
      audio_engine_socket, audio_engine_setsockopt, audio_engine_bind,
      audio_engine_listen, audio_engine_accept,     audio_engine_connect,
      audio_engine_close,  audio_engine_select,     audio_engine_sendto,
      audio_engine_send,   audio_engine_recvfrom,   audio_engine_recv};
  int nResult = ipvp_config_socket(&socketConfig);

  rtc::Thread::Current()->PostAt(RTC_FROM_HERE, reschedule_at_, this,
                                 MSG_INIT_ENGINE);
}

int AudioEngineDelegate::Ready() {
  ipvp_set_gain(0, 100, 1);
}

}  // namespace yealink
