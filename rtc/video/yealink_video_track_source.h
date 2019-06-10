#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_TRACK_SOURCE_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_TRACK_SOURCE_H_

#include "yealink/rtc/video/yealink_video_frame.h"

#include "media/base/adapted_video_track_source.h"

#include "yealink/third_party/vie/include/multimedia_interface.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class IVideoCaptureSource;

class YealinkVideoTrackSource : public rtc::AdaptedVideoTrackSource,
                                public multimedia::VideoFrameDeliverySink {
 public:
  explicit YealinkVideoTrackSource(multimedia::IVideoCaptureSource* source,
                                   bool is_screencast,
                                   bool is_remote);
  explicit YealinkVideoTrackSource(IVideoCaptureSource* source,
                                   bool is_screencast,
                                   bool is_remote);
  ~YealinkVideoTrackSource() override;

  bool is_screencast() const override;

  absl::optional<bool> needs_denoising() const override;

  void SetState(SourceState new_state);
  SourceState state() const override;

  bool remote() const override;

 protected:
  void OnFrameIncoming(const multimedia::VideoDeliveryFrame& frame) override;

 private:
  multimedia::IVideoCaptureSource* source_;
  IVideoCaptureSource* secondary_source_;
  SourceState state_;
  const bool is_screencast_;
  const bool is_remote_;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_TRACK_SOURCE_H_