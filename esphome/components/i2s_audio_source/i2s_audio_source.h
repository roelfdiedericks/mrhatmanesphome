#pragma once

#ifdef USE_ESP32_FRAMEWORK_ARDUINO

#include "esphome/components/audio_source/audio_source.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/helpers.h"



namespace esphome {
namespace i2s_audio_source {

class I2SAudioSource : public Component, public audio_source::AudioSource {
 public:
  void setup() override;
  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void loop() override;

  void dump_config() override;

  void set_din_pin(uint8_t pin) { this->din_pin_ = pin; }
  void set_bclk_pin(uint8_t pin) { this->bclk_pin_ = pin; }
  void set_lrclk_pin(uint8_t pin) { this->lrclk_pin_ = pin; }
  void set_audio_frequency(uint32_t frequency) { this->stream.audio_frequency = frequency;}
  void set_bits_per_sample(uint8_t bits) { this->stream.bits_per_sample = bits; }
  void set_channels(uint8_t channels) { this->stream.channels = channels; }

 protected:

  uint8_t din_pin_{0};
  uint8_t bclk_pin_;
  uint8_t lrclk_pin_;
  

};

}  // namespace i2s_audio_source
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ARDUINO
