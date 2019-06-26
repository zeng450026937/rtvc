#include "yealink/rtc/transport_delegate.h"

#include "rtc_base/checks.h"
#include "rtc_base/logging.h"

#include "yealink/rtc/video_engine_delegate.h"

namespace yealink {

namespace {
std::string global_fake_ip = "127.0.0.1";
int global_transport_count = 0;
}  // namespace

TransportDelegate::TransportDelegate(bool is_rtcp)
    : is_rtcp_(is_rtcp),
      transport_(nullptr),
      worker_thread_(rtc::Thread::Current()) {
  address_.SetIP(global_fake_ip);
  address_.SetPort(++global_transport_count);
}

TransportDelegate::~TransportDelegate() = default;

void TransportDelegate::SetTransport(webrtc::Transport* transport) {
  transport_ = transport;
}

void TransportDelegate::ReceivePacket(rtc::CopyOnWriteBuffer* packet) {
  // if (!worker_thread_->IsCurrent()) {
  //   return worker_thread_->Invoke<void>(RTC_FROM_HERE,
  //                                       [&] { return ReceivePacket(packet);
  //                                       });
  // }
  buffered_packet_.emplace_back(rtc::CopyOnWriteBuffer(*packet));
  SignalPacketReceived();
  // VideoEngineDelegate::Instance()->OnPacketReceived();
}

bool TransportDelegate::SendPacket(const uint8_t* data, size_t len) {
  if (!transport_)
    return false;

  return is_rtcp_ ? transport_->SendRtcp(data, len)
                  : transport_->SendRtp(data, len, webrtc::PacketOptions());
}

void TransportDelegate::Flush() {
  rtc::CritScope lock(&buffer_crit_);
  buffered_packet_.clear();
}

bool TransportDelegate::has_bufferred() const {
  // if (!worker_thread_->IsCurrent()) {
  //   return worker_thread_->Invoke<bool>(RTC_FROM_HERE,
  //                                       [&] { return has_bufferred(); });
  // }
  rtc::CritScope lock(&buffer_crit_);
  RTC_LOG(LS_INFO) << "buffered_packet_: " << buffered_packet_.size();
  return buffered_packet_.size() > 0;
}

absl::optional<rtc::CopyOnWriteBuffer> TransportDelegate::Take() {
  // if (!worker_thread_->IsCurrent()) {
  //   return worker_thread_->Invoke<absl::optional<rtc::CopyOnWriteBuffer>>(
  //       RTC_FROM_HERE, [&] { return Take(); });
  // }
  rtc::CritScope lock(&buffer_crit_);
  if (buffered_packet_.size() <= 0)
    return absl::nullopt;

  rtc::CopyOnWriteBuffer buffer = buffered_packet_.front();
  buffered_packet_.pop_front();

  return absl::optional<rtc::CopyOnWriteBuffer>(buffer);
}

}  // namespace yealink
