#include "yealink/rtc/transport_delegate.h"

#include "rtc_base/checks.h"

namespace yealink {

namespace {
int global_transport_count = 0;
}  // namespace

TransportDelegate::TransportDelegate(cricket::MediaChannel* channel)
    : channel_(channel), id_(global_transport_count++) {
  RTC_DCHECK(channel_);
}

int TransportDelegate::id() {
  return id_;
}

void TransportDelegate::OnPacketReceived(rtc::CopyOnWriteBuffer* packet,
                                         int64_t packet_time_us) {
  rtc::CritScope lock(&buffer_crit_);
  buffered_packet_.emplace_back(packet);
}

void TransportDelegate::OnRtcpReceived(rtc::CopyOnWriteBuffer* packet,
                                       int64_t packet_time_us) {
  rtc::CritScope lock(&buffer_crit_);
  buffered_packet_.emplace_back(packet);
}

bool TransportDelegate::SendPacket(rtc::CopyOnWriteBuffer* packet,
                                   const rtc::PacketOptions& options) {
  return channel_->SendPacket(packet, options);
}

bool TransportDelegate::HasBufferedPacket() {
  rtc::CritScope lock(&buffer_crit_);
  return buffered_packet_.size() > 0;
}

}  // namespace yealink
