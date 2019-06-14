#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_

#include <vector>

#include "api/media_stream_interface.h"
#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_broadcaster.h"

#include "yealink/rtc/video/video_sink.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class VideoSourceAdapter
    : public multimedia::VideoFrameProvider,
      public rtc::VideoSinkInterface<webrtc::VideoFrame> {
 public:
  VideoSourceAdapter(
      rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source);
  ~VideoSourceAdapter() override;

  int ConnectToDeliverySink(multimedia::VideoFrameDeliverySink* sink) override;

  int DisconnectToDeliverySink(multimedia::VideoFrameDeliverySink* sink) override;

 protected:
  void OnFrame(const webrtc::VideoFrame& frame) override;

  struct SinkPair {
    SinkPair(VideoSink* sink, rtc::VideoSinkWants wants)
        : sink(sink), wants(wants) {}
    VideoSink* sink;
    rtc::VideoSinkWants wants;
  };
  SinkPair* FindSinkPair(const multimedia::VideoFrameDeliverySink* sink);

  std::vector<SinkPair> sinks_;
  rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source_;

  rtc::VideoBroadcaster broadcaster_;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_
