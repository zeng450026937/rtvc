
#include "api/audio/audio_frame.h"
#include "api/scoped_refptr.h"
#include "media/base/codec.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/ref_count.h"

namespace cricket {
class YealinkVideoChannel;
class AudioSource;
}  // namespace cricket

namespace webrtc {
class AudioSinkInterface;
}

namespace yealink {

class AudioEngineDelegate;
class TransportDelegate;

class AudioSession : public rtc::RefCountInterface {
 public:
  static rtc::scoped_refptr<AudioSession> Create(
      cricket::YealinkVideoChannel* channel);

  virtual ~AudioSession() = default;

  virtual void DeliverPacket(rtc::CopyOnWriteBuffer* packet, bool rtcp) = 0;

  virtual void SendAudioData(
      std::unique_ptr<webrtc::AudioFrame> audio_frame) = 0;
  virtual void GetAudioFrameWithInfo(int sample_rate_hz,
                                     webrtc::AudioFrame* audio_frame) = 0;

  virtual void SetSink(webrtc::AudioSinkInterface* sink) = 0;

  virtual void SetSendCodecs(absl::optional<std::vector<cricket::AudioCodec>>
                                 codecs = absl::nullopt) = 0;
  virtual void SetRecvCodecs(absl::optional<std::vector<cricket::AudioCodec>>
                                 codecs = absl::nullopt) = 0;

  virtual void SetSelectedSendCodec(
      absl::optional<cricket::AudioCodec> codec = absl::nullopt) = 0;
  virtual void SetSelectedRecvCodec(
      absl::optional<cricket::AudioCodec> codec = absl::nullopt) = 0;

  virtual void SetSend(bool enable) = 0;
  virtual void SetRecv(bool enable) = 0;
};

}  // namespace yealink
