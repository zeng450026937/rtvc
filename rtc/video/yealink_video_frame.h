#ifndef YEALINK_RTC_VIDEO_YEALINK_VIDEO_FRAME_H_
#define YEALINK_RTC_VIDEO_YEALINK_VIDEO_FRAME_H_

#include "api/video/video_frame.h"

#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class YealinkVideoFrame : public multimedia::VideoDeliveryFrame {
 public:
  YealinkVideoFrame(const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& buffer);
  ~YealinkVideoFrame();

  // Support move and copy.
  YealinkVideoFrame(const YealinkVideoFrame&);
  YealinkVideoFrame(YealinkVideoFrame&&);
  YealinkVideoFrame& operator=(const YealinkVideoFrame&);
  YealinkVideoFrame& operator=(YealinkVideoFrame&&);

  multimedia::VideoRawDataType RawDataType() const override;
  int Width() const override;
  int Height() const override;

  int PlaneNumber() const override;
  const multimedia::Byte* PlaneBuffer(PlaneType type) const override;
  int PlaneSize(PlaneType type) const override;
  int PlaneStride(PlaneType type) const override;

 private:
  rtc::scoped_refptr<webrtc::VideoFrameBuffer> video_frame_buffer_;
};

YealinkVideoFrame ToYealinkVideoFrame(const webrtc::VideoFrame& frame);

webrtc::VideoFrame FromYealinkVideoFrame(const multimedia::VideoDeliveryFrame& frame);

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_YEALINK_VIDEO_FRAME_H_