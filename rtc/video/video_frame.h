#ifndef YEALINK_RTC_VIDEO_VIDEO_FRAME_H_
#define YEALINK_RTC_VIDEO_VIDEO_FRAME_H_

#include "api/video/video_frame.h"

#include "yealink/third_party/vie/include/video_frame_delivery.h"

namespace yealink {

class VideoFrame : public multimedia::VideoDeliveryFrame {
 public:
  VideoFrame(const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& buffer);
  ~VideoFrame();

  // Support move and copy.
  VideoFrame(const VideoFrame&);
  VideoFrame(VideoFrame&&);
  VideoFrame& operator=(const VideoFrame&);
  VideoFrame& operator=(VideoFrame&&);

  multimedia::VideoRawDataType RawDataType() const override;
  int Width() const override;
  int Height() const override;

  int PlaneNumber() const override;
  const multimedia::Byte* PlaneBuffer(PlaneType type) const override;
  int PlaneSize(PlaneType type) const override;
  int PlaneStride(PlaneType type) const override;

  rtc::scoped_refptr<webrtc::VideoFrameBuffer> buffer() {
    return video_frame_buffer_;
  }

 private:
  rtc::scoped_refptr<webrtc::VideoFrameBuffer> video_frame_buffer_;
};

VideoFrame WrapVideoFrame(const webrtc::VideoFrame& frame);

webrtc::VideoFrame WrapVideoFrame(const multimedia::VideoDeliveryFrame& frame);

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_VIDEO_FRAME_H_