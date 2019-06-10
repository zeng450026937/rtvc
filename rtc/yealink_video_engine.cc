#include "yealink/rtc/yealink_video_engine.h"

namespace cricket {

YealinkVideoEngine::YealinkVideoEngine(
    std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
    std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
    std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
        video_bitrate_allocator_factory)
    : WebRtcVideoEngine(std::move(video_encoder_factory),
                        std::move(video_decoder_factory),
                        std::move(video_bitrate_allocator_factory)) {
  RTC_LOG(LS_INFO) << "YealinkVideoEngine::YealinkVideoEngine()";
}

YealinkVideoEngine::~YealinkVideoEngine() {
  RTC_LOG(LS_INFO) << "YealinkVideoEngine::~YealinkVideoEngine";
}

YealinkVideoChannel::YealinkVideoChannel(
    webrtc::Call* call,
    const MediaConfig& config,
    const VideoOptions& options,
    const webrtc::CryptoOptions& crypto_options,
    webrtc::VideoEncoderFactory* encoder_factory,
    webrtc::VideoDecoderFactory* decoder_factory,
    webrtc::VideoBitrateAllocatorFactory* bitrate_allocator_factory)
    : WebRtcVideoChannel(call,
                         config,
                         options,
                         crypto_options,
                         encoder_factory,
                         decoder_factory,
                         bitrate_allocator_factory) {
  RTC_LOG(LS_INFO) << "YealinkVideoChannel::YealinkVideoChannel()";
}

YealinkVideoChannel::~YealinkVideoChannel() {
  RTC_LOG(LS_INFO) << "YealinkVideoChannel::~YealinkVideoChannel";
}

}  // namespace cricket
