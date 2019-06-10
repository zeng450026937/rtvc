#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_

#include <vector>

#include "api/media_stream_interface.h"
#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_broadcaster.h"

#include "yealink/rtc/video/yealink_video_sink.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

struct VideoCaptureParam {
  VideoCaptureParam()
      : width(640),
        height(480),
        frame_rate(30),
        raw_type(multimedia::VIDEO_RAW_DATA_I420) {}

  int width;
  int height;
  int frame_rate;
  multimedia::VideoRawDataType raw_type;
};

class IVideoCaptureSource {
 public:
  virtual int SetDeliverySink(const multimedia::VideoFrameDeliverySink* sink,
                              const VideoCaptureParam& param) = 0;
  virtual int UnsetDeliverySink(const multimedia::VideoFrameDeliverySink* sink) = 0;

 protected:
  virtual ~IVideoCaptureSource() {}
};

class YealinkVideoSourceAdapter
    : public IVideoCaptureSource,
      public rtc::VideoSinkInterface<webrtc::VideoFrame> {
 public:
  YealinkVideoSourceAdapter(
      rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source);
  ~YealinkVideoSourceAdapter() override;

  int SetDeliverySink(const multimedia::VideoFrameDeliverySink* sink,
                      const VideoCaptureParam& param) override;

  int UnsetDeliverySink(const multimedia::VideoFrameDeliverySink* sink) override;

 protected:
  void OnFrame(const webrtc::VideoFrame& frame) override;

  struct SinkPair {
    SinkPair(YealinkVideoSinkWrapper* sink, rtc::VideoSinkWants wants)
        : sink(sink), wants(wants) {}
    YealinkVideoSinkWrapper* sink;
    rtc::VideoSinkWants wants;
  };
  SinkPair* FindSinkPair(const multimedia::VideoFrameDeliverySink* sink);

  std::vector<SinkPair> sinks_;
  rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source_;

  rtc::VideoBroadcaster broadcaster_;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_SOURCE_ADAPTER_H_
