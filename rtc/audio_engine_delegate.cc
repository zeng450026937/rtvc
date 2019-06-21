#include "yealink/rtc/audio_engine_delegate.h"

#include <string>

#include "rtc_base/logging.h"

#include "yealink/third_party/ipvp/include/service_ipvp.h"

namespace yealink {
namespace {

int audio_engine_log_hub(void* priv,
                         int module,
                         int log_level,
                         const char* fmt,
                         ...) {
  switch (log_level) {
    case 0:
    case 1:
    case 2:
    case 3:
      break;
    case 4:
      break;
    case 5:
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    default:
      break;
  }
}

int audio_engine_configuration_hub(void* priv,
                                   const char* name,
                                   void* value,
                                   size_t vallen) {}

int audio_engine_event_hub(void* priv,
                           int event,
                           unsigned int wparam,
                           unsigned long lparam,
                           const void* data,
                           size_t data_len) {}

int kAudioEngineDSPHz = 100;
int kAudioEngineSampleRate = 32000;
int kAudioEngineSampleSize = 16;
int kAudioEngineChannels = 1;

std::string tune_file = "D:\\workspace\\rtvc\\src\\yealink\\third_party\\ipvp\\assets\\ipvp.tune";

}  // namespace

AudioEngineDelegate* AudioEngineDelegate::Instance() {
  static AudioEngineDelegate* const audio_engine_delegate =
      new AudioEngineDelegate();
  return audio_engine_delegate;
}

AudioEngineDelegate::AudioEngineDelegate() {
  RTC_LOG(LS_INFO) << "AudioEngineDelegate()";
  // init lib
  const char* args[] = {"ipvp",  "-m", "stdout",         "-l",
                        "any=6", "-p", tune_file.c_str()};
  ipvp_init_t init = {7,       args,
                      nullptr, audio_engine_log_hub,
                      this,    audio_engine_configuration_hub,
                      this,    audio_engine_event_hub,
                      this};
  ipvp_lib_init(&init, sizeof(init));

  // init dev
#ifdef WEBRTC_WIN
  ipvp_dev_init2(&kAudioEngineDSPHz);
#else
  ipvp_dev_init(&kAudioEngineSampleRate, &kAudioEngineChannels,
                &kAudioEngineDSPHz);
  ipvp_init(0, 0);
#endif

  // init aec

  // init transport
}
AudioEngineDelegate::~AudioEngineDelegate() {
  RTC_LOG(LS_INFO) << "~AudioEngineDelegate()";
}

int AudioEngineDelegate::InitDev() {
#ifdef WEBRTC_WIN
  ipvp_dev_init2(&kAudioEngineDSPHz);
#else
  ipvp_init(0, 0);
#endif
}
int AudioEngineDelegate::InitLib() {}
int AudioEngineDelegate::InitAEC() {}
int AudioEngineDelegate::ConfigTransport() {}

}  // namespace yealink
