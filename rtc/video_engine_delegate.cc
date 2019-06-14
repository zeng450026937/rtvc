#include "yealink/rtc/video_engine_delegate.h"

#include <map>
#include <string>

#include "rtc_base/checks.h"
#include "rtc_base/logging.h"

#include "yealink/third_party/vie/include/multimedia_log.h"
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
  rtc::LoggingSeverity level;

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
  multimedia::MultimediaLogApi::SetLogCallback(video_engine_log_hub);
  multimedia::VideoSessionGlobalApi::StartUp(video_engine_event_hub);
}
VideoEngineDelegate::~VideoEngineDelegate() {
  multimedia::VideoSessionGlobalApi::ShutDown();
  // By above RTC_DEFINE_STATIC_LOCAL.
  RTC_NOTREACHED() << "VideoEngineDelegate should never be destructed.";
}

void VideoEngineDelegate::RegisterTransport(TransportDelegate* transport) {}
void VideoEngineDelegate::DeRegisterTransport(TransportDelegate* transport) {}
}  // namespace yealink
