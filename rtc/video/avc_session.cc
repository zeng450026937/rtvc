#include "yealink/rtc/video/avc_session.h"

#include <memory>

#include "absl/types/optional.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "rtc_base/ref_counted_object.h"

#include "yealink/rtc/transport_delegate.h"
#include "yealink/rtc/video/video_frame.h"
#include "yealink/rtc/video/video_sink.h"
#include "yealink/rtc/video/video_source_adapter.h"
#include "yealink/rtc/video_engine_delegate.h"
#include "yealink/rtc/yealink_video_engine.h"

#include "yealink/third_party/vie/include/video_avc_session.h"
#include "yealink/third_party/vie/include/video_capture_source.h"
#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

namespace {

int global_session_id = 0;

class AVCSessionInternal : public AVCSession,
                           multimedia::VideoFrameDeliverySink,
                           VideoSourceAdapter {
 public:
  AVCSessionInternal(multimedia::VideoSessionType type,
                     std::unique_ptr<TransportDelegate> rtp_transport,
                     std::unique_ptr<TransportDelegate> rtcp_transport)
      : VideoSourceAdapter(nullptr),
        id_(++global_session_id),
        type_(type),
        session_(nullptr),
        rtp_transport_(std::move(rtp_transport)),
        rtcp_transport_(std::move(rtcp_transport)) {
    VideoEngineDelegate::Instance()->RegisterTransport(rtp_transport_.get());
    VideoEngineDelegate::Instance()->RegisterTransport(rtcp_transport_.get());
    RTC_LOG(LS_INFO) << "AVCSessionInternal()";
    MaybeRecreateSession();
    MaybeInitSession();
    RTC_DCHECK(session_);

    session_->StartSession(GetSessionDirection());
    started_ = true;
  }
  ~AVCSessionInternal() override {
    RTC_LOG(LS_INFO) << "~AVCSessionInternal()";
    rtp_transport_->Flush();
    rtcp_transport_->Flush();
    if (session_) {
      session_->DisconnectToDeliverySink(this);
      session_->DisconncetToFrameProvider(this);
      session_->StopSession();
      multimedia::IAVCSessionApi::DestroyInstance(session_);
    }
    VideoEngineDelegate::Instance()->DeRegisterTransport(rtp_transport_.get());
    VideoEngineDelegate::Instance()->DeRegisterTransport(rtcp_transport_.get());

    RTC_LOG(LS_INFO) << "~AVCSessionInternal()!!";
  };

  int id() { return id_; }

  void DeliverPacket(rtc::CopyOnWriteBuffer* packet, bool rtcp) override {
    RTC_LOG(LS_INFO) << "DeliverPacket";
    auto transport = rtcp ? rtcp_transport_.get() : rtp_transport_.get();
    transport->ReceivePacket(packet);
  }

  void SetSource(
      rtc::VideoSourceInterface<webrtc::VideoFrame>* source,
      const webrtc::DegradationPreference& degradation_preference) override {
    source_ = source;
    // VideoSourceAdapter::SetVideoSource(source);
  }

  void SetSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override {
    sink_ = sink;
  }

  void SetSend(bool send) override {
    if (send == sending_)
      return;
    sending_ = send;
    // UpdateDirection();
  }
  void SetReceive(bool receive) override {
    if (receive == receiving_)
      return;
    receiving_ = receive;
    // UpdateDirection();
  }

  void SetSendCodecs(std::vector<cricket::VideoCodec> codecs) override {
    send_codecs_ = codecs;
  };
  void SetReceiveCodecs(std::vector<cricket::VideoCodec> codecs) override {
    recv_codecs_ = codecs;
  };

  void SetSelectedSendCodec(cricket::VideoCodec codec) override {
    selected_send_codecs_ = codec;
  };
  void SetSelectedReceiveCodec(cricket::VideoCodec codec) override {
    selected_recv_codecs_ = codec;
  };

 private:
  void OnFrameIncoming(const multimedia::VideoDeliveryFrame& frame) override {
    if (sink_) {
      sink_->OnFrame(yealink::WrapVideoFrame(frame));
    }
  };

  void UpdateDirection() {
    if (inited_) {
      session_->StopSession();
      started_ = false;
    }

    if (sending_ || receiving_) {
      session_->StartSession(GetSessionDirection());
      started_ = true;
    }
  }

  void MaybeRecreateSession() {
    if (inited_ && session_) {
      session_->StopSession();
      multimedia::IAVCSessionApi::DestroyInstance(session_);
      session_ = nullptr;
      inited_ = false;
    }

    if (!session_) {
      multimedia::IAVCSessionApi::CreateInstance(session_, type_);
    }
  }

  void MaybeInitSession() {
    multimedia::AvcConfig config;

    config.stream_id = id();

    config.remote_private_capset.clock_rate = 0;
    config.remote_private_capset.payload_type = 0;
    std::strcpy(config.remote_private_capset.codec_name, "\0");
    std::strcpy(config.remote_private_capset.private_capacity, "\0");

    config.codecs.determined_recv_codec.codec_type =
        multimedia::VIDEO_CODEC_H264;
    config.codecs.determined_recv_codec.height = 480;
    config.codecs.determined_recv_codec.width = 640;
    config.codecs.determined_recv_codec.key_frame_interval = 0;
    config.codecs.determined_recv_codec.packet_mtu_size = 1200;
    config.codecs.determined_recv_codec.payload_type = 97;
    config.codecs.determined_recv_codec.profile =
        multimedia::VIDEO_CODEC_PROFILE_BASE;
    config.codecs.determined_recv_codec.slice_mode =
        multimedia::VIDEO_CODEC_SLICE_SINGLE;
    config.codecs.determined_recv_codec.target_bitrate = 2448000;
    config.codecs.determined_recv_codec.target_framerate = 60;

    config.codecs.available_recv_codecs_num = 1;
    config.codecs.available_recv_codecs[0] =
        config.codecs.determined_recv_codec;

    config.codecs.determined_send_codec.codec_type =
        multimedia::VIDEO_CODEC_H264;
    config.codecs.determined_send_codec.height = 480;
    config.codecs.determined_send_codec.width = 640;
    config.codecs.determined_send_codec.key_frame_interval = 0;
    config.codecs.determined_send_codec.packet_mtu_size = 1200;
    config.codecs.determined_send_codec.payload_type = 97;
    config.codecs.determined_send_codec.profile =
        multimedia::VIDEO_CODEC_PROFILE_BASE;
    config.codecs.determined_send_codec.slice_mode =
        multimedia::VIDEO_CODEC_SLICE_SINGLE;
    config.codecs.determined_send_codec.target_bitrate = 2448000;
    config.codecs.determined_send_codec.target_framerate = 60;

    config.codecs.available_send_codecs_num = 1;
    config.codecs.available_send_codecs[0] =
        config.codecs.determined_send_codec;

    config.sess_pars.multiplex.enable_rtcp_multiplex = false;
    config.sess_pars.multiplex.enable_rtp_multiplex = false;
    // config.sess_pars.multiplex.rtp_multiplex_id = 983319775;
    config.sess_pars.enable_incomplete_decoding = true;
    config.sess_pars.enable_net_address_adpter = true;
    config.sess_pars.enable_net_adpter = true;
    config.sess_pars.qos_value = 0;
    config.sess_pars.quality_policy =
        multimedia::VideoQualityPolicyType::HighFrameRatePrefered;

    config.transport_config.transport_type =
        multimedia::MediaTransportType::MEDIA_TRANSPORT_TYPE_EXTERNAL;
    config.transport_config.rtp_handle = rtp_transport_->hash();
    config.transport_config.rtcp_handle = rtcp_transport_->hash();

    config.rtcp_pars.flow_control_method =
        multimedia::VideoFlowControlMethod::FLOWCTL_NONE;
    config.rtcp_pars.keyframe_request_method =
        multimedia::VideoKeyFrameRequestMethod::KEYREQU_PLI_RTCP;
    config.rtcp_pars.keep_alive_config.enable = false;
    // config.rtcp_pars.no_data_report_secs = 25;

    config.encrypt_pars.encrypt_key_pattern =
        multimedia::MediaEncryptKeyPattern::MEK_MASTER_KEY;
    config.encrypt_pars.send_encrypt_key.type =
        multimedia::MediaEncryptType::MET_NONE;
    config.encrypt_pars.recv_encrypt_key.type =
        multimedia::MediaEncryptType::MET_NONE;

    session_->InitConfig(config);

    const size_t kWidth = 640;
    const size_t kHeight = 480;
    const size_t kFps = 30;

    const int kMaxDeviceCount = 10;
    int device_count = 0;
    multimedia::VideoCameraDeviceDescriptor devices[kMaxDeviceCount];
    multimedia::IVideoCameraDeviceAccess::EnumCameraDevices(devices, 10,
                                                            device_count);

    multimedia::IVideoCaptureSource* source;
    multimedia::IVideoCaptureSource::CreateInstance(source);

    multimedia::VideoCaptureSourceInfo constraints;

    constraints.capture_type = multimedia::VIDEO_CAPTURE_SOURCE_CAMERA;
    constraints.format.width = kWidth;
    constraints.format.height = kHeight;
    constraints.format.frame_rate = kFps;
    constraints.format.raw_type = multimedia::VIDEO_RAW_DATA_I420;
    constraints.camera_param.unique_id = devices[0].unique_id;
    constraints.camera_param.camera_format =
        multimedia::VideoCameraCaptureFormat();

    source->Start(constraints);
    session_->ConnectToFrameProvider(source);
    session_->ConnectToDeliverySink(this);

    inited_ = true;
  }

  multimedia::VideoSessionOrient GetSessionDirection() {
    return multimedia::VideoSessionOrient::VIDEO_SESSION_ORIENT_BOTH;
    if (sending_ && receiving_) {
      return multimedia::VideoSessionOrient::VIDEO_SESSION_ORIENT_BOTH;
    } else if (sending_) {
      return multimedia::VideoSessionOrient::VIDEO_SESSION_ORIENT_SEND;
    } else if (receiving_) {
      return multimedia::VideoSessionOrient::VIDEO_SESSION_ORIENT_RECV;
    } else {
      return multimedia::VideoSessionOrient::VIDEO_SESSION_ORIENT_UNDEF;
    }
  }

  multimedia::VideoSessionType type_;
  multimedia::IAVCSessionApi* session_;

  absl::optional<std::vector<cricket::VideoCodec>> send_codecs_;
  absl::optional<std::vector<cricket::VideoCodec>> recv_codecs_;

  absl::optional<cricket::VideoCodec> selected_send_codecs_;
  absl::optional<cricket::VideoCodec> selected_recv_codecs_;

  std::unique_ptr<TransportDelegate> rtp_transport_;
  std::unique_ptr<TransportDelegate> rtcp_transport_;

  rtc::VideoSinkInterface<webrtc::VideoFrame>* sink_;
  rtc::VideoSourceInterface<webrtc::VideoFrame>* source_;

  int id_;
  bool inited_ = false;
  bool started_ = false;
  bool sending_ = false;
  bool receiving_ = false;
};
}  // namespace

AVCSessionFactory::AVCSessionFactory() {
  RTC_LOG(LS_INFO) << "AVCSessionFactory()";
}
AVCSessionFactory::~AVCSessionFactory() {
  RTC_LOG(LS_INFO) << "~AVCSessionFactory()";
}

rtc::scoped_refptr<AVCSession> AVCSessionFactory::CreateAVCSession(
    cricket::YealinkVideoChannel* channel) {
  auto rtp_transport = absl::make_unique<TransportDelegate>(false);
  rtp_transport->SetTransport(channel);
  auto rtcp_transport = absl::make_unique<TransportDelegate>(true);
  rtcp_transport->SetTransport(channel);

  return new rtc::RefCountedObject<AVCSessionInternal>(
      multimedia::VideoSessionType::VIDEO_SESSION_CAMERA,
      std::move(rtp_transport), std::move(rtcp_transport));
}

}  // namespace yealink
