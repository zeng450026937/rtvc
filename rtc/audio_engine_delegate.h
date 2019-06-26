#ifndef YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
#define YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_

#include <map>

#include "api/scoped_refptr.h"
#include "rtc_base/message_handler.h"
#include "rtc_base/message_queue.h"
#include "rtc_base/socket_address.h"
#include "rtc_base/third_party/sigslot/sigslot.h"

#include "yealink/rtc/audio/audio_session.h"
#include "yealink/rtc/transport_delegate.h"

namespace yealink {

class AudioEngineConfig {
 public:
  static void Setup();
};

class AudioEngineDelegate : public rtc::MessageHandler,
                            public sigslot::has_slots<> {
 public:
  static AudioEngineDelegate* Instance();

  AudioEngineDelegate::AudioEngineDelegate();
  AudioEngineDelegate::~AudioEngineDelegate();

  void RegisterTransport(TransportDelegate* transport);
  void DeRegisterTransport(TransportDelegate* transport);

  TransportDelegate* FindTransport(size_t hash);
  TransportDelegate* FindTransport(const rtc::SocketAddress& address);

 protected:
  void OnMessage(rtc::Message* msg) override;
  void OnPacketReceived();

 private:
  int Init();
  int Ready();
  
  bool ready_ = false;
  std::map<size_t, TransportDelegate*> transports_;
  int64_t reschedule_at_;

  webrtc::AudioFrame in_frame_;
  webrtc::AudioFrame out_frame_;

  RTC_DISALLOW_COPY_AND_ASSIGN(AudioEngineDelegate);
};

}  // namespace yealink

#endif  // YEALINK_RTC_VIDEO_ENGINE_DELEGATE_H_
