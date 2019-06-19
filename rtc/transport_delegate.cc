#include "yealink/rtc/transport_delegate.h"

#include "rtc_base/checks.h"

#include "yealink/rtc/video_engine_delegate.h"

namespace yealink {

namespace {
int global_transport_count = 0;
}  // namespace

TransportDelegate::TransportDelegate(webrtc::Transport* transport,
                                     bool is_rtcp)
    : transport_(transport), id_(++global_transport_count), is_rtcp_(is_rtcp) {
  RTC_DCHECK(transport_);
  VideoEngineDelegate::Instance()->RegisterTransport(this);
}
TransportDelegate::~TransportDelegate() {
  VideoEngineDelegate::Instance()->DeRegisterTransport(this);
}

void TransportDelegate::OnPacketReceived(rtc::CopyOnWriteBuffer* packet) {
  rtc::CritScope lock(&buffer_crit_);
  buffered_packet_.emplace_back(
      rtc::CopyOnWriteBuffer(packet->cdata(), packet->size()));
  VideoEngineDelegate::Instance()->OnPacketRecived(this, packet);
}

bool TransportDelegate::SendPacket(const uint8_t* data, size_t len) {
  return is_rtcp_ ? transport_->SendRtcp(data, len)
                  : transport_->SendRtp(data, len, webrtc::PacketOptions());
}

bool TransportDelegate::HasBufferedPacket() const {
  rtc::CritScope lock(&buffer_crit_);
  return buffered_packet_.size() > 0;
}

rtc::CopyOnWriteBuffer TransportDelegate::Take() {
  rtc::CritScope lock(&buffer_crit_);
  rtc::CopyOnWriteBuffer buffer = buffered_packet_.front();
  buffered_packet_.pop_front();
  return buffer;
}

}  // namespace yealink
