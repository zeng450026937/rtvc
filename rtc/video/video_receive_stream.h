#ifndef YEALINK_RTC_VIDEO_RECEIVE_STREAM_H_
#define YEALINK_RTC_VIDEO_RECEIVE_STREAM_H_

#include "call/video_receive_stream.h"

namespace yealink {

class VideoReceiveStream : public webrtc::VideoReceiveStream {
 public:
  VideoReceiveStream();
  ~VideoReceiveStream() override;

  // webrtc::VideoReceiveStream implementation.
  void Start() override;
  virtual void Stop() override;

  virtual Stats GetStats() const override;

  virtual void AddSecondarySink(webrtc::RtpPacketSinkInterface* sink) override;
  virtual void RemoveSecondarySink(const webrtc::RtpPacketSinkInterface* sink) override;

  virtual std::vector<webrtc::RtpSource> GetSources() const override;

  virtual bool SetBaseMinimumPlayoutDelayMs(int delay_ms) override;

  virtual int GetBaseMinimumPlayoutDelayMs() const override;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_RECEIVE_STREAM_H_