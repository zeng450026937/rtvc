#ifndef YEALINK_RTC_YEALINK_VIDEO_TRANSPORT_DELEGATE_H_
#define YEALINK_RTC_YEALINK_VIDEO_TRANSPORT_DELEGATE_H_

#include "yealink/rtc/transport_delegate.h"

namespace yealink {
  
class VideoTransportDelegate : public TransportDelegate {
 public:
  explicit VideoTransportDelegate(cricket::MediaChannel* channel);
  ~VideoTransportDelegate() override = default;

  int id() override;
};

}  // namespace yealink

#endif  // YEALINK_RTC_YEALINK_VIDEO_TRANSPORT_DELEGATE_H_