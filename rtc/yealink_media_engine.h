
#ifndef YEALINK_RTC_YEALINK_MEDIA_ENGINE_H_
#define YEALINK_RTC_YEALINK_MEDIA_ENGINE_H_

#include <memory>
#include <string>
#include <vector>

#include "call/call.h"
#include "media/base/media_engine.h"
#include "modules/audio_device/include/audio_device.h"

namespace webrtc {
class AudioDecoderFactory;
class AudioMixer;
class AudioProcessing;
class VideoDecoderFactory;
class VideoEncoderFactory;
class VideoBitrateAllocatorFactory;
}  // namespace webrtc

namespace cricket {

class YealinkMediaEngineFactory {
 public:
  // These Create methods may be called on any thread, though the engine is
  // only expected to be used on one thread, internally called the "worker
  // thread". This is the thread Init must be called on.

  // Create a MediaEngineInterface with optional video codec factories. These
  // video factories represents all video codecs, i.e. no extra internal video
  // codecs will be added.
  static std::unique_ptr<MediaEngineInterface> Create(
      rtc::scoped_refptr<webrtc::AudioDeviceModule> adm,
      rtc::scoped_refptr<webrtc::AudioEncoderFactory> audio_encoder_factory,
      rtc::scoped_refptr<webrtc::AudioDecoderFactory> audio_decoder_factory,
      std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
      std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
      rtc::scoped_refptr<webrtc::AudioMixer> audio_mixer,
      rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing);

  static std::unique_ptr<MediaEngineInterface> Create(
      rtc::scoped_refptr<webrtc::AudioDeviceModule> adm,
      rtc::scoped_refptr<webrtc::AudioEncoderFactory> audio_encoder_factory,
      rtc::scoped_refptr<webrtc::AudioDecoderFactory> audio_decoder_factory,
      std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
      std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
      std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
          video_bitrate_allocator_factory,
      rtc::scoped_refptr<webrtc::AudioMixer> audio_mixer,
      rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing);
};

}  // namespace cricket

#endif  // YEALINK_RTC_YEALINK_MEDIA_ENGINE_H_
