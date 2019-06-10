
#ifndef YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_
#define YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_

#include "api/video/video_bitrate_allocator_factory.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "media/engine/webrtc_video_engine.h"

namespace cricket {

class YealinkVideoChannel;

// YealinkVideoEngine is used for the new native WebRTC Video API (webrtc:1667).
class YealinkVideoEngine : public WebRtcVideoEngine {
 public:
  // These video codec factories represents all video codecs, i.e. both software
  // and external hardware codecs.
  YealinkVideoEngine(
      std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
      std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
      std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
          video_bitrate_allocator_factory);

  ~YealinkVideoEngine() override;
};

class YealinkVideoChannel : public WebRtcVideoChannel {
 public:
  YealinkVideoChannel(
      webrtc::Call* call,
      const MediaConfig& config,
      const VideoOptions& options,
      const webrtc::CryptoOptions& crypto_options,
      webrtc::VideoEncoderFactory* encoder_factory,
      webrtc::VideoDecoderFactory* decoder_factory,
      webrtc::VideoBitrateAllocatorFactory* bitrate_allocator_factory);
  ~YealinkVideoChannel() override;
};

}  // namespace cricket

#endif  // YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_
