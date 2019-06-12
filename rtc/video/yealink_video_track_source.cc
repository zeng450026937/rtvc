
#include "yealink/rtc/video/yealink_video_track_source.h"

#include "rtc_base/checks.h"
#include "yealink/rtc/video/yealink_video_frame.h"
#include "yealink/rtc/video/yealink_video_source_adapter.h"

namespace yealink {

YealinkVideoTrackSource::YealinkVideoTrackSource(
    multimedia::IVideoCaptureSource* source,
    bool is_screencast,
    bool is_remote)
    : rtc::AdaptedVideoTrackSource(1),
      source_(source),
      secondary_source_(nullptr),
      is_screencast_(is_screencast),
      is_remote_(is_remote) {
  RTC_DCHECK(source_);
  source_->SetDeliverySink(this);
}
YealinkVideoTrackSource::YealinkVideoTrackSource(IVideoCaptureSource* source,
                                                 bool is_screencast,
                                                 bool is_remote)
    : rtc::AdaptedVideoTrackSource(1),
      source_(nullptr),
      secondary_source_(source),
      is_screencast_(is_screencast),
      is_remote_(is_remote) {
  RTC_DCHECK(secondary_source_);
  secondary_source_->SetDeliverySink(this, VideoCaptureParam());
}
YealinkVideoTrackSource::~YealinkVideoTrackSource() {
  if (source_) {
    source_->SetDeliverySink();
  }
  if (secondary_source_) {
    secondary_source_->UnsetDeliverySink(this);
  }
}

bool YealinkVideoTrackSource::is_screencast() const {
  return is_screencast_;
}

absl::optional<bool> YealinkVideoTrackSource::needs_denoising() const {
  return false;
}

void YealinkVideoTrackSource::SetState(
    webrtc::MediaSourceInterface::SourceState new_state) {
  if (state_ != new_state) {
    state_ = new_state;
    FireOnChanged();
  }
}

webrtc::MediaSourceInterface::SourceState YealinkVideoTrackSource::state()
    const {
  return state_;
}

bool YealinkVideoTrackSource::remote() const {
  return is_remote_;
}

void YealinkVideoTrackSource::OnFrameIncoming(
    const multimedia::VideoDeliveryFrame& frame) {
  rtc::AdaptedVideoTrackSource::OnFrame(FromYealinkVideoFrame(frame));
}

}  // namespace yealink
