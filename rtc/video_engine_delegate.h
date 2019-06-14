#ifndef YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
#define YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_

#include "yealink/rtc/transport_delegate.h"

#include "yealink/third_party/vie/include/video_external_transport.h"

namespace yealink {

class VideoEngineDelegate : public multimedia::VideoExternalTransportSink {
 public:
  static VideoEngineDelegate* Instance();

  void RegisterTransport(TransportDelegate* transport);
  void DeRegisterTransport(TransportDelegate* transport);

 protected:
  // impl VideoExternalTransportSink
  int GetHandle(multimedia::VideoTransportHandle handle) override;
  int ReleaseHandle(multimedia::VideoTransportHandle handle) override;

  int Select(const multimedia::VideoTransportHandleSet& check_set,
             multimedia::VideoTransportHandleSet& recv_set,
             const multimedia::VideoTransportTimeValue& timeout) override;
  virtual int Recv(multimedia::VideoTransportHandle handle,
                   char*& buffer,
                   int& buf_len) override;
  virtual int ReleaseRecvBuffer(multimedia::VideoTransportHandle handle,
                                char* buffer) override;

  virtual int Send(multimedia::VideoTransportHandle handle,
                   const char* buffer,
                   int buf_len) override;
  virtual int SendVector(
      multimedia::VideoTransportHandle handle,
      const multimedia::VideoTransportBufferVector& buffers) override;

 private:
  VideoEngineDelegate::VideoEngineDelegate();
  VideoEngineDelegate::~VideoEngineDelegate();

  std::map<int, TransportDelegate*> transports_;
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
