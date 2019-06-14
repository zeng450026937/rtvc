#ifndef YEALINK_RTC_VIDEO_VIDEO_SEND_STREAM_H_
#define YEALINK_RTC_VIDEO_VIDEO_SEND_STREAM_H_

#include "call/video_send_stream.h"

namespace yealink {

class VideoSendStream : public webrtc::VideoSendStream {
 public:
  VideoSendStream();
  ~VideoSendStream() override;

  // webrtc::VideoSendStream implementation.
  void UpdateActiveSimulcastLayers(
      const std::vector<bool> active_layers) override;
  void Start() override;
  void Stop() override;

  void SetSource(rtc::VideoSourceInterface<webrtc::VideoFrame>* source,
                 const webrtc::DegradationPreference& degradation_preference) override;

  void ReconfigureVideoEncoder(webrtc::VideoEncoderConfig) override;
  Stats GetStats() override;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_VIDEO_SEND_STREAM_H_