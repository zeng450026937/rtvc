#include "yealink/rtc/audio/audio_session.h"

#include "api/call/audio_sink.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "rtc_base/thread_annotations.h"

#include "yealink/rtc/transport_delegate.h"

namespace yealink {
namespace {

int gloable_audio_session_id = 0;

class AudioSessionInternal : public AudioSession {
 public:
  AudioSessionInternal(std::unique_ptr<TransportDelegate> rtp_transport,
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
    transport->ReceivePacket(packet);
  }

  void SendAudioData(std::unique_ptr<webrtc::AudioFrame> audio_frame) override {
    // audio framing
  }

  void GetAudioFrameWithInfo(int sample_rate_hz,
                             webrtc::AudioFrame* audio_frame) override {
    rtc::CritScope cs(&sink_crit_);

    if (sink_) {
      webrtc::AudioSinkInterface::Data data(
          audio_frame->data(), audio_frame->samples_per_channel_,
          audio_frame->sample_rate_hz_, audio_frame->num_channels_,
          audio_frame->timestamp_);
      sink_->OnData(data);
    }
  }

  void SetSink(webrtc::AudioSinkInterface* sink) override {
    rtc::CritScope cs(&sink_crit_);
    sink_ = sink;
  }

  void SetSendCodecs(
      absl::optional<std::vector<cricket::AudioCodec>> codecs) override {
    send_codecs_ = codecs;
  }
  void SetRecvCodecs(
      absl::optional<std::vector<cricket::AudioCodec>> codecs) override {
    recv_codecs_ = codecs;
  }

  void SetSelectedSendCodec(
      absl::optional<cricket::AudioCodec> codec) override {
    selected_send_codecs_ = codec;
  }
  void SetSelectedRecvCodec(
      absl::optional<cricket::AudioCodec> codec) override {
    selected_recv_codecs_ = codec;
  }

  void SetSend(bool enable) override { send_ = enable; }
  void SetRecv(bool enable) override { recv_ = enable; }

 private:
  bool is_ready() {
    return send_codecs_ && recv_codecs_ && selected_send_codecs_ &&
           selected_recv_codecs_;
  }
  bool can_start() { return send_ || recv_; }

  std::unique_ptr<TransportDelegate> rtp_transport_;
  std::unique_ptr<TransportDelegate> rtcp_transport_;

  bool send_ = false;
  bool recv_ = false;

  rtc::CriticalSection sink_crit_;
  webrtc::AudioSinkInterface* sink_ = nullptr RTC_GUARDED_BY(sink_crit_);

  absl::optional<std::vector<cricket::AudioCodec>> send_codecs_;
  absl::optional<std::vector<cricket::AudioCodec>> recv_codecs_;

  absl::optional<cricket::AudioCodec> selected_send_codecs_;
  absl::optional<cricket::AudioCodec> selected_recv_codecs_;

  RTC_DISALLOW_COPY_AND_ASSIGN(AudioSessionInternal);
};

}  // namespace

rtc::scoped_refptr<AudioSession> AudioSession::Create(
    cricket::YealinkVideoChannel* channel) {
  return new rtc::RefCountedObject<AudioSessionInternal>(
      absl::make_unique<TransportDelegate>(channel, false /* rtp_transport */),
      absl::make_unique<TransportDelegate>(channel, true /* rtcp_transport */));
}

}  // namespace yealink
