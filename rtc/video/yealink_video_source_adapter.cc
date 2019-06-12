
#include "yealink/rtc/video/yealink_video_source_adapter.h"

#include "absl/algorithm/container.h"
#include "rtc_base/checks.h"

#include "yealink/rtc/video/yealink_video_frame.h"

namespace yealink {

namespace {
rtc::VideoSinkWants FromCaptureParam(const VideoCaptureParam& param) {
  rtc::VideoSinkWants wants;

  wants.max_framerate_fps = param.frame_rate;
  wants.target_pixel_count = param.width * param.height;

  return wants;
}
}  // namespace

YealinkVideoSourceAdapter::YealinkVideoSourceAdapter(
    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source)
    : video_source_(video_source) {
  RTC_DCHECK(video_source_);
  video_source_->AddOrUpdateSink(this, rtc::VideoSinkWants());
}
YealinkVideoSourceAdapter::~YealinkVideoSourceAdapter() {
  RTC_DCHECK(video_source_);
  video_source_->RemoveSink(this);
}

int YealinkVideoSourceAdapter::SetDeliverySink(
    const multimedia::VideoFrameDeliverySink* sink,
    const VideoCaptureParam& param) {
  RTC_DCHECK(sink != nullptr);

  SinkPair* sink_pair = FindSinkPair(sink);

  rtc::VideoSinkWants wants = FromCaptureParam(param);
  YealinkVideoSinkWrapper* sink_wrapper = FromYealinkVideoSink(
      const_cast<multimedia::VideoFrameDeliverySink*>(sink));

  if (!sink_pair) {
    sinks_.push_back(SinkPair(sink_wrapper, wants));
  } else {
    sink_pair->wants = wants;
  }

  broadcaster_.AddOrUpdateSink(sink_wrapper->GetSink(), wants);

  return 0;
}

int YealinkVideoSourceAdapter::UnsetDeliverySink(
    const multimedia::VideoFrameDeliverySink* sink) {
  RTC_DCHECK(sink != nullptr);
  RTC_DCHECK(FindSinkPair(sink));

  sinks_.erase(
      std::remove_if(sinks_.begin(), sinks_.end(),
                     [sink, this](const SinkPair& sink_pair) {
                       if (sink_pair.sink->GetRawSink() == sink) {
                         broadcaster_.RemoveSink(sink_pair.sink->GetSink());
                         delete sink_pair.sink;
                         return true;
                       }
                       return false;
                     }),
      sinks_.end());

  return 0;
}

void YealinkVideoSourceAdapter::OnFrame(const webrtc::VideoFrame& frame) {
  broadcaster_.OnFrame(frame);
}

YealinkVideoSourceAdapter::SinkPair* YealinkVideoSourceAdapter::FindSinkPair(
    const multimedia::VideoFrameDeliverySink* sink) {
  auto sink_pair_it =
      absl::c_find_if(sinks_, [sink](const SinkPair& sink_pair) {
        return sink_pair.sink->GetRawSink() == sink;
      });
  if (sink_pair_it != sinks_.end()) {
    return &*sink_pair_it;
  }
  return nullptr;
}

}  // namespace yealink
