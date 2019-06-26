#ifndef YEALINK_RTC_TRANSPORT_DELEGATE_H_
#define YEALINK_RTC_TRANSPORT_DELEGATE_H_

#include <deque>

#include "absl/types/optional.h"
#include "api/call/transport.h"
#include "rtc_base/async_invoker.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/copy_on_write_buffer.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/socket_address.h"
#include "rtc_base/thread.h"
#include "rtc_base/thread_annotations.h"

#include "rtc_base/third_party/sigslot/sigslot.h"

namespace yealink {

class TransportDelegate {
 public:
  explicit TransportDelegate(bool is_rtcp);
  ~TransportDelegate();

  bool is_rtcp() { return is_rtcp_; }

  size_t hash() { return address_.Hash(); }
  const rtc::SocketAddress& address() { return address_; }

  webrtc::Transport* transport() { return transport_; }
  void SetTransport(webrtc::Transport* transport);

  void ReceivePacket(rtc::CopyOnWriteBuffer* packet);
  bool SendPacket(const uint8_t* data, size_t len);

  void Flush();

  bool has_bufferred() const;
  absl::optional<rtc::CopyOnWriteBuffer> Take();

  sigslot::signal0<> SignalPacketReceived;

 protected:
  bool is_rtcp_;
  webrtc::Transport* transport_;
  rtc::SocketAddress address_;
  rtc::Thread* worker_thread_;

  rtc::CriticalSection buffer_crit_;
  std::deque<rtc::CopyOnWriteBuffer> buffered_packet_
      RTC_GUARDED_BY(buffer_crit_);

  RTC_DISALLOW_COPY_AND_ASSIGN(TransportDelegate);
};

}  // namespace yealink

#endif  // YEALINK_RTC_TRANSPORT_DELEGATE_H_