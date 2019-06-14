#include "yealink/rtc/video_transport_delegate.h"

namespace yealink {

VideoTransportDelegate::VideoTransportDelegate(cricket::MediaChannel* channel)
    : TransportDelegate(channel) {}

}  // namespace yealink
