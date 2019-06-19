#ifndef YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
#define YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_

#include <map>

#include "yealink/rtc/transport_delegate.h"

namespace yealink {

class AudioEngineDelegate {
 public:
  static AudioEngineDelegate* Instance();

  void RegisterTransport(TransportDelegate* transport);
  void DeRegisterTransport(TransportDelegate* transport);

  void OnPacketRecived(TransportDelegate* transport,
                       rtc::CopyOnWriteBuffer* packet);

 private:
  AudioEngineDelegate::AudioEngineDelegate();
  AudioEngineDelegate::~AudioEngineDelegate();

  TransportDelegate* FindTransport(int id);

  rtc::Event event_;

  std::map<int, TransportDelegate*> transports_;

  rtc::CriticalSection packet_crit_;
  std::map<char*, rtc::CopyOnWriteBuffer> pending_packets_
      RTC_GUARDED_BY(packet_crit_);

  RTC_DISALLOW_COPY_AND_ASSIGN(AudioEngineDelegate);
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
