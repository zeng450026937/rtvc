
#include "yealink/rtc/video/video_source_adapter.h"

#include "absl/algorithm/container.h"
#include "rtc_base/checks.h"

#include "yealink/rtc/video/video_frame.h"

namespace yealink {

VideoSourceAdapter::VideoSourceAdapter(
    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> video_source)
    : video_source_(video_source) {
  RTC_DCHECK(video_source_);
  video_source_->AddOrUpdateSink(this, rtc::VideoSinkWants());
}
VideoSourceAdapter::~VideoSourceAdapter() {
  RTC_DCHECK(video_source_);
  video_source_->RemoveSink(this);
}

int VideoSourceAdapter::ConnectToDeliverySink(
    multimedia::VideoFrameDeliverySink* sink) {
  RTC_DCHECK(sink != nullptr);

  SinkPair* sink_pair = FindSinkPair(sink);

  rtc::VideoSinkWants wants;
  VideoSink* sink_wrapper = WrapVideoSink(
      const_cast<multimedia::VideoFrameDeliverySink*>(sink));

  if (!sink_pair) {
    sinks_.push_back(SinkPair(sink_wrapper, wants));
  } else {
    sink_pair->wants = wants;
  }

  broadcaster_.AddOrUpdateSink(sink_wrapper->GetRtcSink(), wants);

  return 0;
}

int VideoSourceAdapter::DisconnectToDeliverySink(
    multimedia::VideoFrameDeliverySink* sink) {
  RTC_DCHECK(sink != nullptr);
  RTC_DCHECK(FindSinkPair(sink));

  sinks_.erase(
      std::remove_if(sinks_.begin(), sinks_.end(),
                     [sink, this](const SinkPair& sink_pair) {
                       if (sink_pair.sink->GetVieSink() == sink) {
                         broadcaster_.RemoveSink(sink_pair.sink->GetRtcSink());
                         delete sink_pair.sink;
                         return true;
                       }
                       return false;
                     }),
      sinks_.end());

  return 0;
}

void VideoSourceAdapter::OnFrame(const webrtc::VideoFrame& frame) {
  broadcaster_.OnFrame(frame);
}

VideoSourceAdapter::SinkPair* VideoSourceAdapter::FindSinkPair(
    const multimedia::VideoFrameDeliverySink* sink) {
  auto sink_pair_it =
      absl::c_find_if(sinks_, [sink](const SinkPair& sink_pair) {
        return sink_pair.sink->GetVieSink() == sink;
      });
  if (sink_pair_it != sinks_.end()) {
    return &*sink_pair_it;
  }
  return nullptr;
}

}  // namespace yealink
