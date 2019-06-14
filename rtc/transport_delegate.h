#ifndef YEALINK_RTC_TRANSPORT_DELEGATE_H_
#define YEALINK_RTC_TRANSPORT_DELEGATE_H_

#include <vector>
#include <map>

#include "media/base/media_channel.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/thread_annotations.h"

namespace yealink {

class TransportDelegate {
 public:
  explicit TransportDelegate(cricket::MediaChannel* channel);
  virtual ~TransportDelegate() = default;

  virtual int id();

  virtual void OnPacketReceived(rtc::CopyOnWriteBuffer* packet,
                                int64_t packet_time_us);

  virtual void OnRtcpReceived(rtc::CopyOnWriteBuffer* packet,
                              int64_t packet_time_us);

  virtual bool SendPacket(rtc::CopyOnWriteBuffer* packet,
                          const rtc::PacketOptions& options);

  bool HasBufferedPacket();

 protected:
  cricket::MediaChannel* channel_;
  int id_;

  rtc::CriticalSection buffer_crit_;
  std::vector<const rtc::CopyOnWriteBuffer> buffered_packet_ RTC_GUARDED_BY(buffer_crit_);
  
  rtc::CriticalSection pending_crit_;
  std::map<const uint8_t*, const rtc::CopyOnWriteBuffer> pending_packet_ RTC_GUARDED_BY(pending_crit_);
};

}  // namespace yealink

#endif  // YEALINK_RTC_TRANSPORT_DELEGATE_H_