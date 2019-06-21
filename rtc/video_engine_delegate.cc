#include "yealink/rtc/video_engine_delegate.h"

#include <map>
#include <string>

#include "rtc_base/checks.h"
#include "rtc_base/logging.h"

#include "yealink/third_party/vie/include/video_external_transport.h"
#include "yealink/third_party/vie/include/video_session_common.h"

namespace yealink {

namespace {
void video_engine_event_hub(int event_id,
                            int stream_type,
                            int stream_id,
                            int event_data_size,
                            const void* event_data_ptr) {
  // TODO: dispatch event specificed media channel
}

void video_engine_log_hub(multimedia::VideoLogLevelType level,
                          const char* data,
                          int len) {
  std::string msg(data);

  switch (level) {
    case multimedia::VideoLogLevelType::VIDEO_LOG_LEVEL_DEBUG:
      RTC_LOG(LS_INFO) << msg;
      break;
    case multimedia::VideoLogLevelType::VIDEO_LOG_LEVEL_INFO:
      RTC_LOG(LS_INFO) << msg;
      break;
    case multimedia::VideoLogLevelType::VIDEO_LOG_LEVEL_WARN:
      RTC_LOG(LS_WARNING) << msg;
      break;
    case multimedia::VideoLogLevelType::VIDEO_LOG_LEVEL_ERR:
      RTC_LOG(LS_ERROR) << msg;
      break;
    default:
      RTC_LOG(LS_INFO) << msg;
      break;
  }
}
}  // namespace

VideoEngineDelegate* VideoEngineDelegate::Instance() {
  static VideoEngineDelegate* const video_engine_delegate =
      new VideoEngineDelegate();
  return video_engine_delegate;
}

VideoEngineDelegate::VideoEngineDelegate() {
  RTC_LOG(LS_INFO) << "VideoEngineDelegate()";
  multimedia::MultimediaLogApi::SetLogCallback(video_engine_log_hub);
  multimedia::VideoSessionGlobalApi::StartUp(video_engine_event_hub);
  multimedia::VideoExternalTransportSink::StartUpExternalTransport(this);
}
VideoEngineDelegate::~VideoEngineDelegate() {
  RTC_LOG(LS_INFO) << "~VideoEngineDelegate()";
  multimedia::VideoSessionGlobalApi::ShutDown();
}

void VideoEngineDelegate::RegisterTransport(TransportDelegate* transport) {
  RTC_DCHECK(transport);
  transports_.emplace(transport->id(), transport);
}
void VideoEngineDelegate::DeRegisterTransport(TransportDelegate* transport) {
  RTC_DCHECK(transport);
  transports_.erase(transport->id());
}

void VideoEngineDelegate::OnPacketRecived(TransportDelegate* transport,
                                          rtc::CopyOnWriteBuffer* data) {
  RTC_DCHECK(data);
  event_.Set();
}

int VideoEngineDelegate::GetHandle(multimedia::VideoTransportHandle handle) {
  return FindTransport(handle) != nullptr ? 0 : -1;
};
int VideoEngineDelegate::ReleaseHandle(
    multimedia::VideoTransportHandle handle) {
  RTC_DCHECK(FindTransport(handle));
  return 0;
};

int VideoEngineDelegate::Select(
    const multimedia::VideoTransportHandleSet& check_set,
    multimedia::VideoTransportHandleSet& recv_set,
    const multimedia::VideoTransportTimeValue& timeout) {
  int recv_count = 0;
  int wait_time =
      static_cast<int>(timeout.secs * 1000 + timeout.micro_secs / 1000);
      //毫秒
  bool is_timeout = false;

  while (!is_timeout && recv_count == 0) {
    for (int i = 0; i < check_set.handle_num; i++) {
      auto it = transports_.find(check_set.handle_array[i]);

      if (it == transports_.end()) {
        continue;
      }

      if (it->second->HasBufferedPacket()) {
        recv_set.handle_array[recv_count] = it->first;
        recv_set.handle_num = ++recv_count;
      }
    }

    if (recv_count == 0) {
      is_timeout = !event_.Wait(wait_time);
      event_.Reset();
    }
  }

  return recv_count;
};
int VideoEngineDelegate::Recv(multimedia::VideoTransportHandle handle,
                              char*& buffer,
                              int& buf_len) {
  auto transport = FindTransport(handle);
  RTC_DCHECK(transport) << "Receive packet on unknown transport.";
  RTC_CHECK_GT(transport->HasBufferedPacket(), 0)
      << "No buffered packet in this transport.";

  rtc::CopyOnWriteBuffer packet = transport->Take();
  // use cdata() to avoid making data copied
  buffer = const_cast<char*>(packet.cdata<char>());
  buf_len = packet.size();

  {
    rtc::CritScope cs(&packet_crit_);
    pending_packets_.emplace(buffer, packet);
  }

  return buf_len;
};
int VideoEngineDelegate::ReleaseRecvBuffer(
    multimedia::VideoTransportHandle handle,
    char* buffer) {
  {
    rtc::CritScope cs(&packet_crit_);
    pending_packets_.erase(buffer);
  }

  return 0;
};

int VideoEngineDelegate::Send(multimedia::VideoTransportHandle handle,
                              const char* buffer,
                              int buf_len) {
  auto transport = FindTransport(handle);
  RTC_DCHECK(transport) << "Send packet on unknown transport.";

  transport->SendPacket(reinterpret_cast<const uint8_t*>(buffer), buf_len);

  return buf_len;
};
int VideoEngineDelegate::SendVector(
    multimedia::VideoTransportHandle handle,
    const multimedia::VideoTransportBufferVector& buffers) {
  int total = 0;
  for (int i = 0; i < buffers.buffer_number; i++) {
    total += buffers.buf_lens[i];
    Send(handle, buffers.buffers[i], buffers.buf_lens[i]);
  }

  return total;
};

TransportDelegate* VideoEngineDelegate::FindTransport(int id) {
  auto it = transports_.find(id);

  if (it != transports_.end()) {
    return it->second;
  }

  return nullptr;
}

}  // namespace yealink
