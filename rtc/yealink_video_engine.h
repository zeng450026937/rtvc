
#ifndef YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_
#define YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "absl/types/optional.h"
#include "api/call/transport.h"
#include "api/video/video_bitrate_allocator_factory.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "api/video_codecs/sdp_video_format.h"
#include "call/call.h"
#include "call/flexfec_receive_stream.h"
#include "call/video_receive_stream.h"
#include "call/video_send_stream.h"
#include "media/base/media_engine.h"
#include "rtc_base/async_invoker.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/network_route.h"
#include "rtc_base/thread_annotations.h"
#include "rtc_base/thread_checker.h"

#include "yealink/rtc/video/avc_session.h"
#include "yealink/rtc/transport_delegate.h"

namespace webrtc {
class VideoDecoderFactory;
class VideoEncoderFactory;
struct MediaConfig;
}  // namespace webrtc

namespace rtc {
class Thread;
}  // namespace rtc

namespace cricket {

class YealinkVideoChannel;

class UnsignalledSsrcHandlerInternal {
 public:
  enum Action {
    kDropPacket,
    kDeliverPacket,
  };
  virtual Action OnUnsignalledSsrc(YealinkVideoChannel* channel,
                                   uint32_t ssrc) = 0;
  virtual ~UnsignalledSsrcHandlerInternal() = default;
};

// TODO(pbos): Remove, use external handlers only.
class YealinkUnsignalledSsrcHandler : public UnsignalledSsrcHandlerInternal {
 public:
  YealinkUnsignalledSsrcHandler();
  Action OnUnsignalledSsrc(YealinkVideoChannel* channel,
                           uint32_t ssrc) override;

  rtc::VideoSinkInterface<webrtc::VideoFrame>* GetDefaultSink() const;
  void SetDefaultSink(YealinkVideoChannel* channel,
                      rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);

  virtual ~YealinkUnsignalledSsrcHandler() = default;

 private:
  rtc::VideoSinkInterface<webrtc::VideoFrame>* default_sink_;
};

// YealinkVideoEngine is used for the new native WebRTC Video API (webrtc:1667).
class YealinkVideoEngine : public VideoEngineInterface {
 public:
  // These video codec factories represents all video codecs, i.e. both software
  // and external hardware codecs.
  YealinkVideoEngine(
      std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
      std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
      std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
          video_bitrate_allocator_factory);

  ~YealinkVideoEngine() override;

  VideoMediaChannel* CreateMediaChannel(
      webrtc::Call* call,
      const MediaConfig& config,
      const VideoOptions& options,
      const webrtc::CryptoOptions& crypto_options) override;

  std::vector<VideoCodec> codecs() const override;
  RtpCapabilities GetCapabilities() const override;

 private:
  const std::unique_ptr<webrtc::VideoDecoderFactory> decoder_factory_;
  const std::unique_ptr<webrtc::VideoEncoderFactory> encoder_factory_;
  const std::unique_ptr<webrtc::VideoBitrateAllocatorFactory>
      bitrate_allocator_factory_;
  const std::unique_ptr<yealink::AVCSessionFactory> avc_session_factory_;
};

class YealinkVideoChannel : public VideoMediaChannel, public webrtc::Transport {
 public:
  YealinkVideoChannel(
      webrtc::Call* call,
      const MediaConfig& config,
      const VideoOptions& options,
      const webrtc::CryptoOptions& crypto_options,
      webrtc::VideoEncoderFactory* encoder_factory,
      webrtc::VideoDecoderFactory* decoder_factory,
      webrtc::VideoBitrateAllocatorFactory* bitrate_allocator_factory,
      yealink::AVCSessionFactory* avc_session_factory);
  ~YealinkVideoChannel() override;

  // VideoMediaChannel implementation
  rtc::DiffServCodePoint PreferredDscp() const override;

  bool SetSendParameters(const VideoSendParameters& params) override;
  bool SetRecvParameters(const VideoRecvParameters& params) override;
  webrtc::RtpParameters GetRtpSendParameters(uint32_t ssrc) const override;
  webrtc::RTCError SetRtpSendParameters(
      uint32_t ssrc,
      const webrtc::RtpParameters& parameters) override;
  webrtc::RtpParameters GetRtpReceiveParameters(uint32_t ssrc) const override;
  bool SetRtpReceiveParameters(
      uint32_t ssrc,
      const webrtc::RtpParameters& parameters) override;
  bool GetSendCodec(VideoCodec* send_codec) override;
  bool SetSend(bool send) override;
  bool SetVideoSend(
      uint32_t ssrc,
      const VideoOptions* options,
      rtc::VideoSourceInterface<webrtc::VideoFrame>* source) override;
  bool AddSendStream(const StreamParams& sp) override;
  bool RemoveSendStream(uint32_t ssrc) override;
  bool AddRecvStream(const StreamParams& sp) override;
  bool AddRecvStream(const StreamParams& sp, bool default_stream);
  bool RemoveRecvStream(uint32_t ssrc) override;
  bool SetSink(uint32_t ssrc,
               rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override;
  void FillBitrateInfo(BandwidthEstimationInfo* bwe_info) override;
  bool GetStats(VideoMediaInfo* info) override;

  void OnPacketReceived(rtc::CopyOnWriteBuffer* packet,
                        int64_t packet_time_us) override;
  void OnRtcpReceived(rtc::CopyOnWriteBuffer* packet,
                      int64_t packet_time_us) override;
  void OnReadyToSend(bool ready) override;
  void OnNetworkRouteChanged(const std::string& transport_name,
                             const rtc::NetworkRoute& network_route) override;
  void SetInterface(NetworkInterface* iface,
                    webrtc::MediaTransportInterface* media_transport) override;

  // E2E Encrypted Video Frame API
  // Set a frame decryptor to a particular ssrc that will intercept all
  // incoming video frames and attempt to decrypt them before forwarding the
  // result.
  void SetFrameDecryptor(uint32_t ssrc,
                         rtc::scoped_refptr<webrtc::FrameDecryptorInterface>
                             frame_decryptor) override;
  // Set a frame encryptor to a particular ssrc that will intercept all
  // outgoing video frames and attempt to encrypt them and forward the result
  // to the packetizer.
  void SetFrameEncryptor(uint32_t ssrc,
                         rtc::scoped_refptr<webrtc::FrameEncryptorInterface>
                             frame_encryptor) override;

  bool SetBaseMinimumPlayoutDelayMs(uint32_t ssrc, int delay_ms) override;

  absl::optional<int> GetBaseMinimumPlayoutDelayMs(
      uint32_t ssrc) const override;

  // Implemented for VideoMediaChannelTest.
  bool sending() const {
    RTC_DCHECK_RUN_ON(&thread_checker_);
    return sending_;
  }

  absl::optional<uint32_t> GetDefaultReceiveStreamSsrc();

  StreamParams unsignaled_stream_params() {
    RTC_DCHECK_RUN_ON(&thread_checker_);
    return unsignaled_stream_params_;
  }

  // AdaptReason is used for expressing why a WebRtcVideoSendStream request
  // a lower input frame size than the currently configured camera input frame
  // size. There can be more than one reason OR:ed together.
  enum AdaptReason {
    ADAPTREASON_NONE = 0,
    ADAPTREASON_CPU = 1,
    ADAPTREASON_BANDWIDTH = 2,
  };

  static constexpr int kDefaultQpMax = 56;

  std::vector<webrtc::RtpSource> GetSources(uint32_t ssrc) const override;

 private:
  class WebRtcVideoReceiveStream;
  struct VideoCodecSettings {
    VideoCodecSettings();

    // Checks if all members of |*this| are equal to the corresponding members
    // of |other|.
    bool operator==(const VideoCodecSettings& other) const;
    bool operator!=(const VideoCodecSettings& other) const;

    // Checks if all members of |a|, except |flexfec_payload_type|, are equal
    // to the corresponding members of |b|.
    static bool EqualsDisregardingFlexfec(const VideoCodecSettings& a,
                                          const VideoCodecSettings& b);

    VideoCodec codec;
    webrtc::UlpfecConfig ulpfec;
    int flexfec_payload_type;
    int rtx_payload_type;
  };

  struct ChangedSendParameters {
    // These optionals are unset if not changed.
    absl::optional<VideoCodecSettings> codec;
    absl::optional<std::vector<webrtc::RtpExtension>> rtp_header_extensions;
    absl::optional<std::string> mid;
    absl::optional<bool> extmap_allow_mixed;
    absl::optional<int> max_bandwidth_bps;
    absl::optional<bool> conference_mode;
    absl::optional<webrtc::RtcpMode> rtcp_mode;
  };

  struct ChangedRecvParameters {
    // These optionals are unset if not changed.
    absl::optional<std::vector<VideoCodecSettings>> codec_settings;
    absl::optional<std::vector<webrtc::RtpExtension>> rtp_header_extensions;
    // Keep track of the FlexFEC payload type separately from |codec_settings|.
    // This allows us to recreate the FlexfecReceiveStream separately from the
    // VideoReceiveStream when the FlexFEC payload type is changed.
    absl::optional<int> flexfec_payload_type;
  };

  bool GetChangedSendParameters(const VideoSendParameters& params,
                                ChangedSendParameters* changed_params) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  bool GetChangedRecvParameters(const VideoRecvParameters& params,
                                ChangedRecvParameters* changed_params) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);

  void SetMaxSendBandwidth(int bps);

  void ConfigureReceiverRtp(
      webrtc::VideoReceiveStream::Config* config,
      webrtc::FlexfecReceiveStream::Config* flexfec_config,
      const StreamParams& sp) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  bool ValidateSendSsrcAvailability(const StreamParams& sp) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  bool ValidateReceiveSsrcAvailability(const StreamParams& sp) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  void DeleteReceiveStream(WebRtcVideoReceiveStream* stream)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);

  static std::string CodecSettingsVectorToString(
      const std::vector<VideoCodecSettings>& codecs);

  // Wrapper for the sender part.
  class WebRtcVideoSendStream
      : public rtc::VideoSourceInterface<webrtc::VideoFrame> {
   public:
    WebRtcVideoSendStream(
        webrtc::Call* call,
        const StreamParams& sp,
        webrtc::VideoSendStream::Config config,
        const VideoOptions& options,
        bool enable_cpu_overuse_detection,
        int max_bitrate_bps,
        const absl::optional<VideoCodecSettings>& codec_settings,
        const absl::optional<std::vector<webrtc::RtpExtension>>& rtp_extensions,
        const VideoSendParameters& send_params,
        rtc::scoped_refptr<yealink::AVCSession> session);
    virtual ~WebRtcVideoSendStream();

    void SetSendParameters(const ChangedSendParameters& send_params);
    webrtc::RTCError SetRtpParameters(const webrtc::RtpParameters& parameters);
    webrtc::RtpParameters GetRtpParameters() const;

    void SetFrameEncryptor(
        rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frame_encryptor);

    // Implements rtc::VideoSourceInterface<webrtc::VideoFrame>.
    // WebRtcVideoSendStream acts as a source to the webrtc::VideoSendStream
    // in |stream_|. This is done to proxy VideoSinkWants from the encoder to
    // the worker thread.
    void AddOrUpdateSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink,
                         const rtc::VideoSinkWants& wants) override;
    void RemoveSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override;

    bool SetVideoSend(const VideoOptions* options,
                      rtc::VideoSourceInterface<webrtc::VideoFrame>* source);

    void SetSend(bool send);

    const std::vector<uint32_t>& GetSsrcs() const;
    VideoSenderInfo GetVideoSenderInfo(bool log_stats);
    void FillBitrateInfo(BandwidthEstimationInfo* bwe_info);

   private:
    // Parameters needed to reconstruct the underlying stream.
    // webrtc::VideoSendStream doesn't support setting a lot of options on the
    // fly, so when those need to be changed we tear down and reconstruct with
    // similar parameters depending on which options changed etc.
    struct VideoSendStreamParameters {
      VideoSendStreamParameters(
          webrtc::VideoSendStream::Config config,
          const VideoOptions& options,
          int max_bitrate_bps,
          const absl::optional<VideoCodecSettings>& codec_settings);
      webrtc::VideoSendStream::Config config;
      VideoOptions options;
      int max_bitrate_bps;
      bool conference_mode;
      absl::optional<VideoCodecSettings> codec_settings;
      // Sent resolutions + bitrates etc. by the underlying VideoSendStream,
      // typically changes when setting a new resolution or reconfiguring
      // bitrates.
      webrtc::VideoEncoderConfig encoder_config;
    };

    rtc::scoped_refptr<webrtc::VideoEncoderConfig::EncoderSpecificSettings>
    ConfigureVideoEncoderSettings(const VideoCodec& codec);
    void SetCodec(const VideoCodecSettings& codec);
    void RecreateWebRtcStream();
    webrtc::VideoEncoderConfig CreateVideoEncoderConfig(
        const VideoCodec& codec) const;
    void ReconfigureEncoder();

    // Calls Start or Stop according to whether or not |sending_| is true,
    // and whether or not the encoding in |rtp_parameters_| is active.
    void UpdateSendState();

    webrtc::DegradationPreference GetDegradationPreference() const
        RTC_EXCLUSIVE_LOCKS_REQUIRED(&thread_checker_);

    rtc::ThreadChecker thread_checker_;
    rtc::AsyncInvoker invoker_;
    rtc::Thread* worker_thread_;
    const std::vector<uint32_t> ssrcs_ RTC_GUARDED_BY(&thread_checker_);
    const std::vector<SsrcGroup> ssrc_groups_ RTC_GUARDED_BY(&thread_checker_);
    webrtc::Call* const call_;
    const bool enable_cpu_overuse_detection_;
    rtc::VideoSourceInterface<webrtc::VideoFrame>* source_
        RTC_GUARDED_BY(&thread_checker_);

    webrtc::VideoSendStream* stream_ RTC_GUARDED_BY(&thread_checker_);
    rtc::VideoSinkInterface<webrtc::VideoFrame>* encoder_sink_
        RTC_GUARDED_BY(&thread_checker_);
    // Contains settings that are the same for all streams in the MediaChannel,
    // such as codecs, header extensions, and the global bitrate limit for the
    // entire channel.
    VideoSendStreamParameters parameters_ RTC_GUARDED_BY(&thread_checker_);
    // Contains settings that are unique for each stream, such as max_bitrate.
    // Does *not* contain codecs, however.
    // TODO(skvlad): Move ssrcs_ and ssrc_groups_ into rtp_parameters_.
    // TODO(skvlad): Combine parameters_ and rtp_parameters_ once we have only
    // one stream per MediaChannel.
    webrtc::RtpParameters rtp_parameters_ RTC_GUARDED_BY(&thread_checker_);

    bool sending_ RTC_GUARDED_BY(&thread_checker_);

    rtc::scoped_refptr<yealink::AVCSession> session_;
  };

  // Wrapper for the receiver part, contains configs etc. that are needed to
  // reconstruct the underlying VideoReceiveStream.
  class WebRtcVideoReceiveStream
      : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
   public:
    WebRtcVideoReceiveStream(
        webrtc::Call* call,
        const StreamParams& sp,
        webrtc::VideoReceiveStream::Config config,
        webrtc::VideoDecoderFactory* decoder_factory,
        bool default_stream,
        const std::vector<VideoCodecSettings>& recv_codecs,
        const webrtc::FlexfecReceiveStream::Config& flexfec_config,
        rtc::scoped_refptr<yealink::AVCSession> session);
    ~WebRtcVideoReceiveStream();

    const std::vector<uint32_t>& GetSsrcs() const;

    std::vector<webrtc::RtpSource> GetSources();

    // Does not return codecs, they are filled by the owning
    // YealinkVideoChannel.
    webrtc::RtpParameters GetRtpParameters() const;

    void SetLocalSsrc(uint32_t local_ssrc);
    // TODO(deadbeef): Move these feedback parameters into the recv parameters.
    void SetFeedbackParameters(bool nack_enabled,
                               bool remb_enabled,
                               bool transport_cc_enabled,
                               webrtc::RtcpMode rtcp_mode);
    void SetRecvParameters(const ChangedRecvParameters& recv_params);

    void OnFrame(const webrtc::VideoFrame& frame) override;
    bool IsDefaultStream() const;

    void SetFrameDecryptor(
        rtc::scoped_refptr<webrtc::FrameDecryptorInterface> frame_decryptor);

    bool SetBaseMinimumPlayoutDelayMs(int delay_ms);

    int GetBaseMinimumPlayoutDelayMs() const;

    void SetSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink);

    VideoReceiverInfo GetVideoReceiverInfo(bool log_stats);

   private:
    void RecreateWebRtcVideoStream();
    void MaybeRecreateWebRtcFlexfecStream();

    void MaybeAssociateFlexfecWithVideo();
    void MaybeDissociateFlexfecFromVideo();

    void ConfigureCodecs(const std::vector<VideoCodecSettings>& recv_codecs);
    void ConfigureFlexfecCodec(int flexfec_payload_type);

    std::string GetCodecNameFromPayloadType(int payload_type);

    webrtc::Call* const call_;
    const StreamParams stream_params_;

    // Both |stream_| and |flexfec_stream_| are managed by |this|. They are
    // destroyed by calling call_->DestroyVideoReceiveStream and
    // call_->DestroyFlexfecReceiveStream, respectively.
    webrtc::VideoReceiveStream* stream_;
    const bool default_stream_;
    webrtc::VideoReceiveStream::Config config_;
    webrtc::FlexfecReceiveStream::Config flexfec_config_;
    webrtc::FlexfecReceiveStream* flexfec_stream_;

    webrtc::VideoDecoderFactory* const decoder_factory_;

    rtc::CriticalSection sink_lock_;
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink_
        RTC_GUARDED_BY(sink_lock_);
    // Expands remote RTP timestamps to int64_t to be able to estimate how long
    // the stream has been running.
    rtc::TimestampWrapAroundHandler timestamp_wraparound_handler_
        RTC_GUARDED_BY(sink_lock_);
    int64_t first_frame_timestamp_ RTC_GUARDED_BY(sink_lock_);
    // Start NTP time is estimated as current remote NTP time (estimated from
    // RTCP) minus the elapsed time, as soon as remote NTP time is available.
    int64_t estimated_remote_start_ntp_time_ms_ RTC_GUARDED_BY(sink_lock_);

    rtc::scoped_refptr<yealink::AVCSession> session_;
  };

  void Construct(webrtc::Call* call, YealinkVideoEngine* engine);

  bool SendRtp(const uint8_t* data,
               size_t len,
               const webrtc::PacketOptions& options) override;
  bool SendRtcp(const uint8_t* data, size_t len) override;

  static std::vector<VideoCodecSettings> MapCodecs(
      const std::vector<VideoCodec>& codecs);
  // Select what video codec will be used for sending, i.e. what codec is used
  // for local encoding, based on supported remote codecs. The first remote
  // codec that is supported locally will be selected.
  absl::optional<VideoCodecSettings> SelectSendVideoCodec(
      const std::vector<VideoCodecSettings>& remote_mapped_codecs) const
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);

  static bool NonFlexfecReceiveCodecsHaveChanged(
      std::vector<VideoCodecSettings> before,
      std::vector<VideoCodecSettings> after);

  void FillSenderStats(VideoMediaInfo* info, bool log_stats)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  void FillReceiverStats(VideoMediaInfo* info, bool log_stats)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  void FillBandwidthEstimationStats(const webrtc::Call::Stats& stats,
                                    VideoMediaInfo* info)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);
  void FillSendAndReceiveCodecStats(VideoMediaInfo* video_media_info)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(thread_checker_);

  rtc::ThreadChecker thread_checker_;

  uint32_t rtcp_receiver_report_ssrc_ RTC_GUARDED_BY(thread_checker_);
  bool sending_ RTC_GUARDED_BY(thread_checker_);
  webrtc::Call* const call_ RTC_GUARDED_BY(thread_checker_);

  YealinkUnsignalledSsrcHandler default_unsignalled_ssrc_handler_
      RTC_GUARDED_BY(thread_checker_);
  UnsignalledSsrcHandlerInternal* const unsignalled_ssrc_handler_
      RTC_GUARDED_BY(thread_checker_);

  // Delay for unsignaled streams, which may be set before the stream exists.
  int default_recv_base_minimum_delay_ms_ RTC_GUARDED_BY(thread_checker_) = 0;

  const MediaConfig::Video video_config_ RTC_GUARDED_BY(thread_checker_);

  // Using primary-ssrc (first ssrc) as key.
  std::map<uint32_t, WebRtcVideoSendStream*> send_streams_
      RTC_GUARDED_BY(thread_checker_);
  std::map<uint32_t, WebRtcVideoReceiveStream*> receive_streams_
      RTC_GUARDED_BY(thread_checker_);
  std::set<uint32_t> send_ssrcs_ RTC_GUARDED_BY(thread_checker_);
  std::set<uint32_t> receive_ssrcs_ RTC_GUARDED_BY(thread_checker_);

  absl::optional<VideoCodecSettings> send_codec_
      RTC_GUARDED_BY(thread_checker_);
  absl::optional<std::vector<webrtc::RtpExtension>> send_rtp_extensions_
      RTC_GUARDED_BY(thread_checker_);

  webrtc::VideoEncoderFactory* const encoder_factory_
      RTC_GUARDED_BY(thread_checker_);
  webrtc::VideoDecoderFactory* const decoder_factory_
      RTC_GUARDED_BY(thread_checker_);
  webrtc::VideoBitrateAllocatorFactory* const bitrate_allocator_factory_
      RTC_GUARDED_BY(thread_checker_);
  std::vector<VideoCodecSettings> recv_codecs_ RTC_GUARDED_BY(thread_checker_);
  std::vector<webrtc::RtpExtension> recv_rtp_extensions_
      RTC_GUARDED_BY(thread_checker_);
  // See reason for keeping track of the FlexFEC payload type separately in
  // comment in YealinkVideoChannel::ChangedRecvParameters.
  int recv_flexfec_payload_type_ RTC_GUARDED_BY(thread_checker_);
  webrtc::BitrateConstraints bitrate_config_ RTC_GUARDED_BY(thread_checker_);
  // TODO(deadbeef): Don't duplicate information between
  // send_params/recv_params, rtp_extensions, options, etc.
  VideoSendParameters send_params_ RTC_GUARDED_BY(thread_checker_);
  rtc::DiffServCodePoint preferred_dscp_ RTC_GUARDED_BY(thread_checker_);
  VideoOptions default_send_options_ RTC_GUARDED_BY(thread_checker_);
  VideoRecvParameters recv_params_ RTC_GUARDED_BY(thread_checker_);
  int64_t last_stats_log_ms_ RTC_GUARDED_BY(thread_checker_);
  const bool discard_unknown_ssrc_packets_ RTC_GUARDED_BY(thread_checker_);
  // This is a stream param that comes from the remote description, but wasn't
  // signaled with any a=ssrc lines. It holds information that was signaled
  // before the unsignaled receive stream is created when the first packet is
  // received.
  StreamParams unsignaled_stream_params_ RTC_GUARDED_BY(thread_checker_);
  // Per peer connection crypto options that last for the lifetime of the peer
  // connection.
  const webrtc::CryptoOptions crypto_options_ RTC_GUARDED_BY(thread_checker_);

  yealink::AVCSessionFactory* const avc_session_facotry_;
  // yealink video engine session, responsible for encode/decode
  // and send/recv video stream.
  rtc::scoped_refptr<yealink::AVCSession> avc_session_;
};

}  // namespace cricket

#endif  // YEALINK_RTC_YEALINK_VIDEO_ENGINE_H_
