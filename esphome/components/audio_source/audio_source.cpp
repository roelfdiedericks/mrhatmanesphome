#include "audio_source.h"
#include "esphome/core/log.h"

namespace esphome {
namespace audio_source {

static const char *const TAG = "audio_source";

AudioSource::AudioSource() {}


void AudioSource::publish_audio(size_t size) {
  ESP_LOGV(TAG, "'%s': Published new audio data %d", this->name_.c_str(), size);
	
  this->callback_.call(audio_buffer,size);
}

void AudioSource::add_audio_callback(std::function<void(uint8_t * , size_t )> &&callback) { this->callback_.add(std::move(callback)); }

std::string AudioSource::unique_id() { return ""; }

}  // namespace audio_source
}  // namespace esphome
