#ifndef YEALINK_RTC_AUDIO_AUDIO_TRANSPORT_IMPL_H_
#define YEALINK_RTC_AUDIO_AUDIO_TRANSPORT_IMPL_H_

#include <vector>

#include "api/audio/audio_mixer.h"
#include "api/scoped_refptr.h"
#include "audio/audio_level.h"
#include "common_audio/resampler/include/push_resampler.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "modules/audio_processing/typing_detection.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/thread_annotations.h"

namespace webrtc {
class AudioSendStream;
}

namespace yealink {

class AudioSession;

class AudioTransportImpl : public webrtc::AudioTransport {
 public:
  AudioTransportImpl(webrtc::AudioMixer* mixer,
                     webrtc::AudioProcessing* audio_processing,
                     AudioSession* audio_session);
  ~AudioTransportImpl() override;

  int32_t RecordedDataIsAvailable(const void* audioSamples,
                                  const size_t nSamples,
                                  const size_t nBytesPerSample,
                                  const size_t nChannels,
                                  const uint32_t samplesPerSec,
                                  const uint32_t totalDelayMS,
                                  const int32_t clockDrift,
                                  const uint32_t currentMicLevel,
                                  const bool keyPressed,
                                  uint32_t& newMicLevel) override;

  int32_t NeedMorePlayData(const size_t nSamples,
                           const size_t nBytesPerSample,
                           const size_t nChannels,
                           const uint32_t samplesPerSec,
                           void* audioSamples,
                           size_t& nSamplesOut,
                           int64_t* elapsed_time_ms,
                           int64_t* ntp_time_ms) override;

  void PullRenderData(int bits_per_sample,
                      int sample_rate,
                      size_t number_of_channels,
                      size_t number_of_frames,
                      void* audio_data,
                      int64_t* elapsed_time_ms,
                      int64_t* ntp_time_ms) override;

  void UpdateSendingStreams(std::vector<webrtc::AudioSendStream*> streams,
                            int send_sample_rate_hz,
                            size_t send_num_channels);
  void SetStereoChannelSwapping(bool enable);
  bool typing_noise_detected() const;
  const webrtc::voe::AudioLevel& audio_level() const { return audio_level_; }

  void SetUsingAudioSession(bool enable);

 private:
  // Shared.
  webrtc::AudioProcessing* audio_processing_ = nullptr;

  // Capture side.
  rtc::CriticalSection capture_lock_;
  std::vector<webrtc::AudioSendStream*> sending_streams_
      RTC_GUARDED_BY(capture_lock_);
  int send_sample_rate_hz_ RTC_GUARDED_BY(capture_lock_) = 8000;
  size_t send_num_channels_ RTC_GUARDED_BY(capture_lock_) = 1;
  bool typing_noise_detected_ RTC_GUARDED_BY(capture_lock_) = false;
  bool swap_stereo_channels_ RTC_GUARDED_BY(capture_lock_) = false;
  webrtc::PushResampler<int16_t> capture_resampler_;
  webrtc::voe::AudioLevel audio_level_;
  webrtc::TypingDetection typing_detection_;

  // Render side.
  rtc::scoped_refptr<webrtc::AudioMixer> mixer_;
  webrtc::AudioFrame mixed_frame_;
  // Converts mixed audio to the audio device output rate.
  webrtc::PushResampler<int16_t> render_resampler_;

  // yealink
  rtc::scoped_refptr<AudioSession> audio_session_;
  rtc::CriticalSection session_lock_;
  bool use_audio_session_ = false;

  RTC_DISALLOW_IMPLICIT_CONSTRUCTORS(AudioTransportImpl);
};
}  // namespace yealink

#endif  // YEALINK_RTC_AUDIO_AUDIO_TRANSPORT_IMPL_H_
