
#include "yealink/rtc/yealink_media_engine.h"

#include <utility>

#include "absl/algorithm/container.h"
#include "absl/memory/memory.h"
#include "api/video/builtin_video_bitrate_allocator_factory.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "media/engine/webrtc_voice_engine.h"
#include "system_wrappers/include/field_trial.h"
#include "yealink/rtc/yealink_video_engine.h"
#include "yealink/rtc/yealink_voice_engine.h"

#ifdef HAVE_WEBRTC_VIDEO
#include "media/engine/webrtc_video_engine.h"
#else
#include "media/engine/null_webrtc_video_engine.h"
#endif

namespace cricket {

std::unique_ptr<MediaEngineInterface> YealinkMediaEngineFactory::Create(
    rtc::scoped_refptr<webrtc::AudioDeviceModule> adm,
    rtc::scoped_refptr<webrtc::AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<webrtc::AudioDecoderFactory> audio_decoder_factory,
    std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
    std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
    rtc::scoped_refptr<webrtc::AudioMixer> audio_mixer,
    rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing) {
  return YealinkMediaEngineFactory::Create(
      adm, audio_encoder_factory, audio_decoder_factory,
      std::move(video_encoder_factory), std::move(video_decoder_factory),
      webrtc::CreateBuiltinVideoBitrateAllocatorFactory(), audio_mixer,
      audio_processing);
}

std::unique_ptr<MediaEngineInterface> YealinkMediaEngineFactory::Create(
    rtc::scoped_refptr<webrtc::AudioDeviceModule> adm,
    rtc::scoped_refptr<webrtc::AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<webrtc::AudioDecoderFactory> audio_decoder_factory,
    std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
    std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
    std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
        video_bitrate_allocator_factory,
    rtc::scoped_refptr<webrtc::AudioMixer> audio_mixer,
    rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing) {
// #ifdef HAVE_WEBRTC_VIDEO
//   auto video_engine = absl::make_unique<WebRtcVideoEngine>(
//       std::move(video_encoder_factory), std::move(video_decoder_factory),
//       std::move(video_bitrate_allocator_factory));
// #else
//   auto video_engine = absl::make_unique<NullWebRtcVideoEngine>();
// #endif
//   auto audio_engine = absl::make_unique<WebRtcVoiceEngine>(
//       adm, audio_encoder_factory, audio_decoder_factory, audio_mixer,
//       audio_processing);

  auto yealink_video_engine = absl::make_unique<YealinkVideoEngine>(
      std::move(video_encoder_factory), std::move(video_decoder_factory),
      std::move(video_bitrate_allocator_factory));

  auto yealink_audio_engine = absl::make_unique<YealinkVoiceEngine>(
      adm, audio_encoder_factory, audio_decoder_factory, audio_mixer,
      audio_processing);

  // return std::unique_ptr<MediaEngineInterface>(new CompositeMediaEngine(
  //     absl::make_unique<WebRtcVoiceEngine>(adm, audio_encoder_factory,
  //                                          audio_decoder_factory,
  //                                          audio_mixer, audio_processing),
  //     std::move(video_engine)));
  return std::unique_ptr<MediaEngineInterface>(new CompositeMediaEngine(
      std::move(yealink_audio_engine), std::move(yealink_video_engine)));
}

}  // namespace cricket
