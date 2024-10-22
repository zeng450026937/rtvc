#ifndef YEALINK_RTC_AUDIO_AUDIO_STATE_H_
#define YEALINK_RTC_AUDIO_AUDIO_STATE_H_

#include <map>
#include <memory>
#include <unordered_set>

#include "yealink/rtc/audio/audio_transport_impl.h"
#include "audio/null_audio_poller.h"
#include "call/audio_state.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/ref_count.h"
#include "rtc_base/thread_checker.h"

namespace webrtc {
class AudioSendStream;
class AudioReceiveStream;
}

namespace yealink {
namespace internal {

class AudioState : public webrtc::AudioState {
 public:
  explicit AudioState(const AudioState::Config& config);
  ~AudioState() override;

  webrtc::AudioProcessing* audio_processing() override;
  webrtc::AudioTransport* audio_transport() override;

  void SetPlayout(bool enabled) override;
  void SetRecording(bool enabled) override;

  Stats GetAudioInputStats() const override;
  void SetStereoChannelSwapping(bool enable) override;

  webrtc::AudioDeviceModule* audio_device_module() {
    RTC_DCHECK(config_.audio_device_module);
    return config_.audio_device_module.get();
  }

  bool typing_noise_detected() const;

  void AddReceivingStream(webrtc::AudioReceiveStream* stream);
  void RemoveReceivingStream(webrtc::AudioReceiveStream* stream);

  void AddSendingStream(webrtc::AudioSendStream* stream,
                        int sample_rate_hz,
                        size_t num_channels);
  void RemoveSendingStream(webrtc::AudioSendStream* stream);

 private:
  void UpdateAudioTransportWithSendingStreams();

  rtc::ThreadChecker thread_checker_;
  rtc::ThreadChecker process_thread_checker_;
  const webrtc::AudioState::Config config_;
  bool recording_enabled_ = true;
  bool playout_enabled_ = true;

  // Transports mixed audio from the mixer to the audio device and
  // recorded audio to the sending streams.
  yealink::AudioTransportImpl audio_transport_;

  // Null audio poller is used to continue polling the audio streams if audio
  // playout is disabled so that audio processing still happens and the audio
  // stats are still updated.
  std::unique_ptr<webrtc::internal::NullAudioPoller> null_audio_poller_;

  std::unordered_set<webrtc::AudioReceiveStream*> receiving_streams_;
  struct StreamProperties {
    int sample_rate_hz = 0;
    size_t num_channels = 0;
  };
  std::map<webrtc::AudioSendStream*, StreamProperties> sending_streams_;

  RTC_DISALLOW_IMPLICIT_CONSTRUCTORS(AudioState);
};
}  // namespace internal
}  // namespace yealink

#endif  // YEALINK_RTC_AUDIO_AUDIO_STATE_H_
