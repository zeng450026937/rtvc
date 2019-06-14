#ifndef YEALINK_RTC_VIDEO_CHANNEL_DELEGATE_H_
#define YEALINK_RTC_VIDEO_CHANNEL_DELEGATE_H_

#include "yealink/rtc/transport_delegate.h"

#include "yealink/third_party/vie/include/video_avc_session.h"

namespace yealink {

class VideoChannelDelegate : public TransportDelegate {
 public:
  VideoChannelDelegate::VideoChannelDelegate();
  VideoChannelDelegate::~VideoChannelDelegate() override;

  private:

};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_CHANNEL_DELEGATE_H_