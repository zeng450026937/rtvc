#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_

#include "api/media_stream_interface.h"
#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class YealinkVideoSink : public multimedia::VideoFrameDeliverySink {
 public:
  YealinkVideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);
  ~YealinkVideoSink();

  YealinkVideoSink(const YealinkVideoSink&);
  YealinkVideoSink(YealinkVideoSink&&);
  YealinkVideoSink& operator=(const YealinkVideoSink&);
  YealinkVideoSink& operator=(YealinkVideoSink&&);

  void OnFrameIncoming(const multimedia::VideoDeliveryFrame& frame) override;

  rtc::VideoSinkInterface<webrtc::VideoFrame>* GetSink();
  multimedia::VideoFrameDeliverySink* GetRawSink();

 protected:
  rtc::VideoSinkInterface<webrtc::VideoFrame>* sink_;
};

class YealinkVideoSinkWrapper
    : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
 public:
  YealinkVideoSinkWrapper(multimedia::VideoFrameDeliverySink* sink);
  ~YealinkVideoSinkWrapper();

  YealinkVideoSinkWrapper(const YealinkVideoSinkWrapper&);
  YealinkVideoSinkWrapper(YealinkVideoSinkWrapper&&);
  YealinkVideoSinkWrapper& operator=(const YealinkVideoSinkWrapper&);
  YealinkVideoSinkWrapper& operator=(YealinkVideoSinkWrapper&&);

  void OnFrame(const webrtc::VideoFrame& frame) override;

  rtc::VideoSinkInterface<webrtc::VideoFrame>* GetSink();
  multimedia::VideoFrameDeliverySink* GetRawSink() const;

 protected:
  multimedia::VideoFrameDeliverySink* sink_;
};

YealinkVideoSink* ToYealinkVideoSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);

YealinkVideoSinkWrapper* FromYealinkVideoSink(
    multimedia::VideoFrameDeliverySink* sink);

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_