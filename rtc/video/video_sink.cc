
#include "yealink/rtc/video/video_sink.h"

#include "yealink/rtc/video/video_frame.h"

namespace yealink {

VideoSink::VideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink)
    : rtc_sink_(sink), vie_sink_(nullptr) {}
VideoSink::VideoSink(multimedia::VideoFrameDeliverySink* sink)
    : rtc_sink_(nullptr), vie_sink_(sink) {}
VideoSink::~VideoSink() = default;

VideoSink::VideoSink(const VideoSink&) = default;
VideoSink::VideoSink(VideoSink&&) = default;
VideoSink& VideoSink::operator=(const VideoSink&) = default;
VideoSink& VideoSink::operator=(VideoSink&&) = default;

rtc::VideoSinkInterface<webrtc::VideoFrame>* VideoSink::GetRtcSink() {
  return rtc_sink_ ? rtc_sink_ : static_cast<rtc::VideoSinkInterface<webrtc::VideoFrame>*>(this);
}
multimedia::VideoFrameDeliverySink* VideoSink::GetVieSink() {
  return vie_sink_ ? vie_sink_ : static_cast<multimedia::VideoFrameDeliverySink*>(this);
}

void VideoSink::OnFrameIncoming(const multimedia::VideoDeliveryFrame& frame) {
  if (rtc_sink_) {
    rtc_sink_->OnFrame(WrapVideoFrame(frame));
  }
  if (vie_sink_) {
    vie_sink_->OnFrameIncoming(frame);
  }
}
void VideoSink::OnFrame(const webrtc::VideoFrame& frame) {
  if (rtc_sink_) {
    rtc_sink_->OnFrame(frame);
  }
  if (vie_sink_) {
    vie_sink_->OnFrameIncoming(WrapVideoFrame(frame));
  }
}

VideoSink* WrapVideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) {
  return new VideoSink(sink);
}

VideoSink* WrapVideoSink(multimedia::VideoFrameDeliverySink* sink) {
  return new VideoSink(sink);
}

}  // namespace yealink
