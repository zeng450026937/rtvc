
#include "yealink/rtc/video/video_frame.h"

#include "api/video/i420_buffer.h"

namespace yealink {

VideoFrame::VideoFrame(
    const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& buffer)
    : video_frame_buffer_(buffer->ToI420()) {}

VideoFrame::~VideoFrame() = default;

VideoFrame::VideoFrame(const VideoFrame&) = default;
VideoFrame::VideoFrame(VideoFrame&&) = default;
VideoFrame& VideoFrame::operator=(const VideoFrame&) = default;
VideoFrame& VideoFrame::operator=(VideoFrame&&) = default;

multimedia::VideoRawDataType VideoFrame::RawDataType() const {
  return multimedia::VIDEO_RAW_DATA_I420;
}

int VideoFrame::Width() const {
  return video_frame_buffer_->width();
}

int VideoFrame::Height() const {
  return video_frame_buffer_->height();
}

int VideoFrame::PlaneNumber() const {
  return 3;
}

const multimedia::Byte* VideoFrame::PlaneBuffer(
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

int VideoFrame::PlaneSize(multimedia::VideoDeliveryFrame::PlaneType type) const {
  return PlaneStride(type);
}

int VideoFrame::PlaneStride(multimedia::VideoDeliveryFrame::PlaneType type) const {
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

VideoFrame WrapVideoFrame(const webrtc::VideoFrame& frame) {
  return VideoFrame(frame.video_frame_buffer());
}

webrtc::VideoFrame WrapVideoFrame(const multimedia::VideoDeliveryFrame& frame) {
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
