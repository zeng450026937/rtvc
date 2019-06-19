#include "yealink/rtc/audio_engine_delegate.h"

#include <string>

#include "rtc_base/logging.h"

#include "yealink/third_party/ipvp/include/service_ipvp.h"

namespace yealink {

namespace {
int kDSPHz = 100;

void audio_engine_log_hub(void* priv,
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

void audio_engine_configuration_hub(void* priv,
                                    const char* name,
                                    void* value,
                                    size_t vallen) {}

void audio_engine_event_hub(void* priv,
                            int event,
                            unsigned int wparam,
                            unsigned long lparam,
                            const void* data,
                            size_t data_len) {}
}  // namespace

AudioEngineDelegate* AudioEngineDelegate::Instance() {
  static AudioEngineDelegate* const audio_engine_delegate =
      new AudioEngineDelegate();
  return audio_engine_delegate;
}

AudioEngineDelegate::AudioEngineDelegate() {
  std::string strTuneFile = m_strRootPath + "/ipvp.tune";
  const char* args[] = {"ipvp",  "-m", "stdout",           "-l",
                        "any=6", "-p", strTuneFile.c_str()};
  ipvp_init_t init = {7,          args, nullptr,      OnAudioLog, this,
                      OnAudioCfg, this, OnAudioEvent, this};

  ipvp_lib_init(&init, sizeof(init));
}
AudioEngineDelegate::~AudioEngineDelegate() {
  // By above RTC_DEFINE_STATIC_LOCAL.
  RTC_NOTREACHED() << "VideoEngineDelegate should never be destructed.";
}

}  // namespace yealink
