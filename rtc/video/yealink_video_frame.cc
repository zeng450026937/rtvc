
#include "yealink/rtc/video/yealink_video_frame.h"

#include "api/video/i420_buffer.h"

namespace yealink {

YealinkVideoFrame::YealinkVideoFrame(
    const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& buffer)
    : video_frame_buffer_(buffer->ToI420()) {}

YealinkVideoFrame::~YealinkVideoFrame() = default;

YealinkVideoFrame::YealinkVideoFrame(const YealinkVideoFrame&) = default;
YealinkVideoFrame::YealinkVideoFrame(YealinkVideoFrame&&) = default;
YealinkVideoFrame& YealinkVideoFrame::operator=(const YealinkVideoFrame&) = default;
YealinkVideoFrame& YealinkVideoFrame::operator=(YealinkVideoFrame&&) = default;

multimedia::VideoRawDataType YealinkVideoFrame::RawDataType() const {
  return multimedia::VIDEO_RAW_DATA_I420;
}

int YealinkVideoFrame::Width() const {
  return video_frame_buffer_->width();
}

int YealinkVideoFrame::Height() const {
  return video_frame_buffer_->height();
}

int YealinkVideoFrame::PlaneNumber() const {
  return 3;
}

const multimedia::Byte* YealinkVideoFrame::PlaneBuffer(
    multimedia::VideoDeliveryFrame::PlaneType type) const {
  rtc::scoped_refptr<webrtc::I420BufferInterface> buffer =
      video_frame_buffer_->GetI420();

  switch (type) {
    case multimedia::VideoDeliveryFrame::PlaneValueType::kYPlane:
      return static_cast<const multimedia::Byte*>(buffer->DataY());
    case multimedia::VideoDeliveryFrame::PlaneValueType::kUPlane:
      return static_cast<const multimedia::Byte*>(buffer->DataU());
    case multimedia::VideoDeliveryFrame::PlaneValueType::kVPlane:
      return static_cast<const multimedia::Byte*>(buffer->DataV());
    default:
      return nullptr;
  }
}

int YealinkVideoFrame::PlaneSize(multimedia::VideoDeliveryFrame::PlaneType type) const {
  return PlaneStride(type);
}

int YealinkVideoFrame::PlaneStride(multimedia::VideoDeliveryFrame::PlaneType type) const {
  rtc::scoped_refptr<webrtc::I420BufferInterface> buffer =
      video_frame_buffer_->GetI420();

  switch (type) {
    case multimedia::VideoDeliveryFrame::PlaneValueType::kYPlane:
      return buffer->StrideY();
    case multimedia::VideoDeliveryFrame::PlaneValueType::kUPlane:
      return buffer->StrideU();
    case multimedia::VideoDeliveryFrame::PlaneValueType::kVPlane:
      return buffer->StrideV();
    default:
      return 0;
  }
}

YealinkVideoFrame ToYealinkVideoFrame(const webrtc::VideoFrame& frame) {
  return YealinkVideoFrame(frame.video_frame_buffer());
}

webrtc::VideoFrame FromYealinkVideoFrame(const multimedia::VideoDeliveryFrame& frame) {
  rtc::scoped_refptr<webrtc::I420Buffer> buffer(webrtc::I420Buffer::Copy(
      frame.Width(), frame.Height(),
      frame.PlaneBuffer(multimedia::VideoDeliveryFrame::PlaneValueType::kYPlane),
      frame.PlaneStride(multimedia::VideoDeliveryFrame::PlaneValueType::kYPlane),
      frame.PlaneBuffer(multimedia::VideoDeliveryFrame::PlaneValueType::kUPlane),
      frame.PlaneStride(multimedia::VideoDeliveryFrame::PlaneValueType::kUPlane),
      frame.PlaneBuffer(multimedia::VideoDeliveryFrame::PlaneValueType::kVPlane),
      frame.PlaneStride(multimedia::VideoDeliveryFrame::PlaneValueType::kVPlane)));

  return webrtc::VideoFrame::Builder().set_video_frame_buffer(buffer).build();
}

}  // namespace yealink
