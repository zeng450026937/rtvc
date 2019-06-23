
#include "api/audio/audio_frame.h"
#include "api/scoped_refptr.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/ref_count.h"

namespace yealink {

class AudioEngineDelegate;
class TransportDelegate;

class AudioSession : public rtc::RefCountInterface {
 public:
  virtual ~AudioSession() = default;

  virtual void DeliverPacket(rtc::CopyOnWriteBuffer* packet, bool rtcp) = 0;
  virtual void SendPacket(const uint8_t* data, size_t len);

  virtual void ProcessAudioData(webrtc::AudioFrame* audio_frame) = 0;
  virtual void GetAudioFrameWithInfo(int sample_rate_hz,
                                     webrtc::AudioFrame* audio_frame) = 0;

  virtual void SetSource() = 0;
  virtual void SetSink() = 0;

  virtual void SetSendCodecs() = 0;
  virtual void SetRecvCodecs() = 0;

  virtual void SetSelectedSendCodec() = 0;
  virtual void SetSelectedRecvCodec() = 0;

  virtual void SetSend() = 0;
  virtual void SetRecv() = 0;
};

}  // namespace yealink
