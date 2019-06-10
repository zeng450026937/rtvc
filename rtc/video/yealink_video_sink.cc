
#include "yealink/rtc/video/yealink_video_sink.h"

#include "yealink/rtc/video/yealink_video_frame.h"

namespace yealink {

YealinkVideoSink::YealinkVideoSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink)
    : sink_(sink) {}
YealinkVideoSink::~YealinkVideoSink() = default;

YealinkVideoSink::YealinkVideoSink(const YealinkVideoSink&) = default;
YealinkVideoSink::YealinkVideoSink(YealinkVideoSink&&) = default;
YealinkVideoSink& YealinkVideoSink::operator=(const YealinkVideoSink&) =
    default;
YealinkVideoSink& YealinkVideoSink::operator=(YealinkVideoSink&&) = default;

void YealinkVideoSink::OnFrameIncoming(
    const multimedia::VideoDeliveryFrame& frame) {
  if (sink_) {
    sink_->OnFrame(FromYealinkVideoFrame(frame));
  }
}

rtc::VideoSinkInterface<webrtc::VideoFrame>* YealinkVideoSink::GetSink() {
  return sink_;
}
multimedia::VideoFrameDeliverySink* YealinkVideoSink::GetRawSink() {
  return static_cast<multimedia::VideoFrameDeliverySink*>(this);
}

YealinkVideoSinkWrapper::YealinkVideoSinkWrapper(
    multimedia::VideoFrameDeliverySink* sink)
    : sink_(sink) {}
YealinkVideoSinkWrapper::~YealinkVideoSinkWrapper() = default;

YealinkVideoSinkWrapper::YealinkVideoSinkWrapper(
    const YealinkVideoSinkWrapper&) = default;
YealinkVideoSinkWrapper::YealinkVideoSinkWrapper(YealinkVideoSinkWrapper&&) =
    default;
YealinkVideoSinkWrapper& YealinkVideoSinkWrapper::operator=(
    const YealinkVideoSinkWrapper&) = default;
YealinkVideoSinkWrapper& YealinkVideoSinkWrapper::operator=(
    YealinkVideoSinkWrapper&&) = default;

void YealinkVideoSinkWrapper::OnFrame(const webrtc::VideoFrame& frame) {
  if (sink_) {
    sink_->OnFrameIncoming(ToYealinkVideoFrame(frame));
  }
}

rtc::VideoSinkInterface<webrtc::VideoFrame>* YealinkVideoSinkWrapper::GetSink() {
  return static_cast<rtc::VideoSinkInterface<webrtc::VideoFrame>*>(this);
}
multimedia::VideoFrameDeliverySink* YealinkVideoSinkWrapper::GetRawSink() const {
  return sink_;
}

YealinkVideoSink* ToYealinkVideoSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) {
  return new YealinkVideoSink(sink);
}

YealinkVideoSinkWrapper* FromYealinkVideoSink(
    multimedia::VideoFrameDeliverySink* sink) {
  return new YealinkVideoSinkWrapper(sink);
}

}  // namespace yealink
