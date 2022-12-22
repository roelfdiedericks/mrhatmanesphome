#pragma once


#include "esphome/components/audio_source/audio_source.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/helpers.h"



namespace esphome {
namespace sound_generator {

class SoundGenerator : public Component, public audio_source::AudioSource {
 public:
  void setup() override;
  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void loop() override;

  void dump_config() override;


  void set_pitch(uint32_t frequency) { this->sound_pitch_ = frequency;}
  void set_volume(float volume) { this->sound_volume_ = volume;}
  void set_audio_frequency(uint32_t frequency) { this->stream.audio_frequency = frequency;}
  void set_bits_per_sample(uint8_t bits) { this->stream.bits_per_sample = bits; }
  void set_channels(uint8_t channels) { this->stream.channels = channels; }

 protected:

  uint32_t sound_pitch_;
  float sound_volume_;

  uint32_t next_time_;
  uint32_t full_buffer_time_;

};

}  // namespace i2s_audio_source
}  // namespace esphome

