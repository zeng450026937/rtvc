
#include "yealink/rtc/video/video_track_source.h"

#include "rtc_base/checks.h"
#include "yealink/rtc/video/video_frame.h"

namespace yealink {

VideoTrackSource::VideoTrackSource(
    multimedia::VideoFrameProvider* source,
    bool is_screencast,
    bool is_remote)
    : rtc::AdaptedVideoTrackSource(1),
      source_(source),
      is_screencast_(is_screencast),
      is_remote_(is_remote) {
  RTC_DCHECK(source_);
  source_->ConnectToDeliverySink(this);
}
VideoTrackSource::~VideoTrackSource() {
  RTC_DCHECK(source_);
  source_->DisconnectToDeliverySink(this);
}

bool VideoTrackSource::is_screencast() const {
  return is_screencast_;
}

absl::optional<bool> VideoTrackSource::needs_denoising() const {
  return false;
}

void VideoTrackSource::SetState(
    webrtc::MediaSourceInterface::SourceState new_state) {
  if (state_ != new_state) {
    state_ = new_state;
    FireOnChanged();
  }
}

webrtc::MediaSourceInterface::SourceState VideoTrackSource::state()
    const {
  return state_;
}

bool VideoTrackSource::remote() const {
  return is_remote_;
}

void VideoTrackSource::OnFrameIncoming(
    const multimedia::VideoDeliveryFrame& frame) {
  rtc::AdaptedVideoTrackSource::OnFrame(WrapVideoFrame(frame));
}

}  // namespace yealink
