#ifndef YEALINK_RTC_TRANSPORT_DELEGATE_H_
#define YEALINK_RTC_TRANSPORT_DELEGATE_H_

#include <deque>

#include "api/call/transport.h"
#include "rtc_base/async_invoker.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/thread.h"
#include "rtc_base/thread_checker.h"
#include "rtc_base/thread_annotations.h"

namespace yealink {

class TransportDelegate {
 public:
  explicit TransportDelegate(webrtc::Transport* transport, bool is_rtcp);
  ~TransportDelegate();

  int id() { return id_; }
  bool is_rtcp() { return is_rtcp_; }

  void OnPacketReceived(rtc::CopyOnWriteBuffer* packet);

  bool SendPacket(const uint8_t* data, size_t len);

  bool HasBufferedPacket() const;

  rtc::CopyOnWriteBuffer Take();

 protected:
  webrtc::Transport* transport_;

  int id_;
  bool is_rtcp_;

  rtc::ThreadChecker thread_checker_;
  rtc::Thread worker_thread_;
  rtc::AsyncInvoker invoker_;

  rtc::CriticalSection buffer_crit_;
  std::deque<rtc::CopyOnWriteBuffer> buffered_packet_
      RTC_GUARDED_BY(buffer_crit_);

  RTC_DISALLOW_COPY_AND_ASSIGN(TransportDelegate);
};

}  // namespace yealink

#endif  // YEALINK_RTC_TRANSPORT_DELEGATE_H_