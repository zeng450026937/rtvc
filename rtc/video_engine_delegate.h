#ifndef YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
#define YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_

#include <map>

#include "yealink/rtc/transport_delegate.h"

#include "media/base/codec.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/event.h"
#include "rtc_base/logging.h"
#include "rtc_base/thread.h"
#include "rtc_base/third_party/sigslot/sigslot.h"

#include "yealink/rtc/video/avc_session.h"

#include "yealink/third_party/vie/include/video_external_transport.h"

namespace yealink {

class VideoEngineDelegate : public multimedia::VideoExternalTransportSink,
                            public sigslot::has_slots<> {
 public:
  static VideoEngineDelegate* Instance();

  void RegisterTransport(TransportDelegate* transport);
  void DeRegisterTransport(TransportDelegate* transport);

  void OnPacketReceived();
  
 protected:
  // impl VideoExternalTransportSink
  int GetHandle(multimedia::VideoTransportHandle handle) override;
  int ReleaseHandle(multimedia::VideoTransportHandle handle) override;

  int Select(const multimedia::VideoTransportHandleSet& check_set,
             multimedia::VideoTransportHandleSet& recv_set,
             const multimedia::VideoTransportTimeValue& timeout) override;
  int Recv(multimedia::VideoTransportHandle handle,
           char*& buffer,
           int& buf_len) override;
  int ReleaseRecvBuffer(multimedia::VideoTransportHandle handle,
                        char* buffer) override;

  int Send(multimedia::VideoTransportHandle handle,
           const char* buffer,
           int buf_len) override;
  int SendVector(
      multimedia::VideoTransportHandle handle,
      const multimedia::VideoTransportBufferVector& buffers) override;

 private:
  VideoEngineDelegate::VideoEngineDelegate();
  VideoEngineDelegate::~VideoEngineDelegate();

  TransportDelegate* FindTransport(int id);

  rtc::Event event_;
  rtc::Thread* worker_thread_;

  std::map<size_t, TransportDelegate*> transports_;
  std::map<char*, rtc::CopyOnWriteBuffer> pending_packets_;

  RTC_DISALLOW_COPY_AND_ASSIGN(VideoEngineDelegate);
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
