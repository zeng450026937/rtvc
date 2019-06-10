#ifndef YEALINK_API_CREATE_PEERCONNECTION_FACTORY_H_
#define YEALINK_API_CREATE_PEERCONNECTION_FACTORY_H_

#include <memory>

#include "api/audio/audio_mixer.h"
#include "api/audio_codecs/audio_decoder_factory.h"
#include "api/audio_codecs/audio_encoder_factory.h"
#include "api/fec_controller.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "api/transport/network_control.h"

namespace rtc {
// TODO(bugs.webrtc.org/9987): Move rtc::Thread to api/ or expose a better
// type. At the moment, rtc::Thread is not part of api/ so it cannot be
// included in order to avoid to leak internal types.
class Thread;
}  // namespace rtc

namespace webrtc {
class AudioDeviceModule;
class AudioProcessing;
}  // namespace webrtc

namespace yealink {
// Create a new instance of PeerConnectionFactoryInterface with optional video
// codec factories. These video factories represents all video codecs, i.e. no
// extra internal video codecs will be added.
RTC_EXPORT rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
CreatePeerConnectionFactory(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    rtc::scoped_refptr<webrtc::AudioDeviceModule> default_adm,
    rtc::scoped_refptr<webrtc::AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<webrtc::AudioDecoderFactory> audio_decoder_factory,
    std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory,
    std::unique_ptr<webrtc::VideoDecoderFactory> video_decoder_factory,
    rtc::scoped_refptr<webrtc::AudioMixer> audio_mixer,
    rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing);
}  // namespace yealink

#endif  // YEALINK_API_CREATE_PEERCONNECTION_FACTORY_H_
