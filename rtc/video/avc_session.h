#ifndef YEALINK_RTC_VIDEO_AVC_SESSION_H_
#define YEALINK_RTC_VIDEO_AVC_SESSION_H_

#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "rtc_base/ref_count.h"

namespace yealink {

class TransportDelegate;

// make internal IAVCSessionApi can be shared with VideoSendStream and
// VideoReceiveStream
class AVCSession : public rtc::RefCountInterface {
 public:
  virtual void SetVideoSource(
      rtc::VideoSourceInterface<webrtc::VideoFrame>* source) = 0;

  virtual void SetVideoSink(
      rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) = 0;

  virtual void SetInterface(TransportDelegate* rtp,
                            TransportDelegate* rtcp) = 0;

 protected:
  virtual ~AVCSession() {}
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_AVC_SESSION_H_