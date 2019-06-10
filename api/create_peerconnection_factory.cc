
#include "yealink/api/create_peerconnection_factory.h"

#include <memory>
#include <utility>

#include "api/audio/audio_mixer.h"
#include "api/audio_codecs/audio_decoder_factory.h"
#include "api/audio_codecs/audio_encoder_factory.h"
#include "api/call/call_factory_interface.h"
#include "api/fec_controller.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "api/transport/network_control.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "logging/rtc_event_log/rtc_event_log_factory.h"
#include "logging/rtc_event_log/rtc_event_log_factory_interface.h"
#include "media/base/media_engine.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "rtc_base/thread.h"
#include "yealink/rtc/yealink_media_engine.h"

namespace yealink {

rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
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
    rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing) {
  if (!audio_processing)
    audio_processing = webrtc::AudioProcessingBuilder().Create();

  std::unique_ptr<cricket::MediaEngineInterface> media_engine =
      cricket::YealinkMediaEngineFactory::Create(
          default_adm, audio_encoder_factory, audio_decoder_factory,
          std::move(video_encoder_factory), std::move(video_decoder_factory),
          audio_mixer, audio_processing);

  std::unique_ptr<webrtc::CallFactoryInterface> call_factory =
      webrtc::CreateCallFactory();

  std::unique_ptr<webrtc::RtcEventLogFactoryInterface> event_log_factory =
      webrtc::CreateRtcEventLogFactory();
  webrtc::PeerConnectionFactoryDependencies dependencies;
  dependencies.network_thread = network_thread;
  dependencies.worker_thread = worker_thread;
  dependencies.signaling_thread = signaling_thread;
  dependencies.media_engine = std::move(media_engine);
  dependencies.call_factory = std::move(call_factory);
  dependencies.event_log_factory = std::move(event_log_factory);
  return webrtc::CreateModularPeerConnectionFactory(std::move(dependencies));
}

}  // namespace yealink
