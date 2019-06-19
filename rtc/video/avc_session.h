#ifndef YEALINK_RTC_VIDEO_AVC_SESSION_H_
#define YEALINK_RTC_VIDEO_AVC_SESSION_H_

#include "api/rtp_parameters.h"
#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "api/video_codecs/video_encoder_config.h"
#include "media/base/codec.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/ref_count.h"

#include "yealink/third_party/vie/include/video_avc_session.h"

namespace cricket {
class YealinkVideoChannel;
}

namespace yealink {

class TransportDelegate;

// make internal IAVCSessionApi can be shared with VideoSendStream and
// VideoReceiveStream
class AVCSession : public rtc::RefCountInterface {
 public:
  virtual ~AVCSession() = default;

  virtual void DeliverPacket(rtc::CopyOnWriteBuffer* packet, bool rtcp) = 0;

  virtual void SetSource(
      rtc::VideoSourceInterface<webrtc::VideoFrame>* source,
      const webrtc::DegradationPreference& degradation_preference) = 0;

  virtual void SetSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) = 0;

  virtual void SetSend(bool send) = 0;
  virtual void SetReceive(bool receive) = 0;

  virtual void SetSendCodecs(std::vector<cricket::VideoCodec> codecs) = 0;
  virtual void SetReceiveCodecs(std::vector<cricket::VideoCodec> codecs) = 0;

  virtual void SetSelectedSendCodec(cricket::VideoCodec codec) = 0;
  virtual void SetSelectedReceiveCodec(cricket::VideoCodec codec) = 0;
};

class AVCSessionFactory {
 public:
  AVCSessionFactory();
  virtual ~AVCSessionFactory();

  virtual rtc::scoped_refptr<AVCSession> CreateAVCSession(
      cricket::YealinkVideoChannel* channel);
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_AVC_SESSION_H_