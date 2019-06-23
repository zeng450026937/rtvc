#include "yealink/rtc/audio/audio_session.h"

#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "rtc_base/ref_counted_object.h"

#include "yealink/rtc/transport_delegate.h"

namespace yealink {
namespace {

int gloable_audio_session_id = 0;

class AudioSessionInternal : public AudioSession {
 public:
  AudioSessionInternal(AudioEngineDelegate* engine_,
                       std::unique_ptr<TransportDelegate> rtp_transport,
                       std::unique_ptr<TransportDelegate> rtcp_transport)
      : rtp_transport_(std::move(rtp_transport)),
        rtcp_transport_(std::move(rtcp_transport)) {
    RTC_LOG(LS_INFO) << "AudioSessionInternal()";
  }
  ~AudioSessionInternal() override {
    RTC_LOG(LS_INFO) << "~AudioSessionInternal()";
  }

  void DeliverPacket(rtc::CopyOnWriteBuffer* packet, bool rtcp) override {
    auto transport = rtcp ? rtcp_transport_.get() : rtp_transport_.get();
    transport->OnPacketReceived(packet);
  }

 private:
  std::unique_ptr<TransportDelegate> rtp_transport_;
  std::unique_ptr<TransportDelegate> rtcp_transport_;
};

}  // namespace

}  // namespace yealink
