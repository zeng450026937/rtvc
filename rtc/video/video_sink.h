#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_

#include "api/media_stream_interface.h"
#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class VideoSink : public multimedia::VideoFrameDeliverySink,
                  public rtc::VideoSinkInterface<webrtc::VideoFrame> {
 public:
  VideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);
  VideoSink(multimedia::VideoFrameDeliverySink* sink);
  ~VideoSink();

  VideoSink(const VideoSink&);
  VideoSink(VideoSink&&);
  VideoSink& operator=(const VideoSink&);
  VideoSink& operator=(VideoSink&&);

  rtc::VideoSinkInterface<webrtc::VideoFrame>* GetRtcSink();
  multimedia::VideoFrameDeliverySink* GetVieSink();

 protected:
  void OnFrameIncoming(const multimedia::VideoDeliveryFrame& frame) override;
  void OnFrame(const webrtc::VideoFrame& frame) override;

  rtc::VideoSinkInterface<webrtc::VideoFrame>* rtc_sink_;
  multimedia::VideoFrameDeliverySink* vie_sink_;
};

VideoSink* WrapVideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);

VideoSink* WrapVideoSink(multimedia::VideoFrameDeliverySink* sink);

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_SINK_H_