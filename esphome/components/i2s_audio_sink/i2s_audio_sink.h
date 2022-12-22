#pragma once

#ifdef USE_ESP32_FRAMEWORK_ARDUINO

#include "esphome/components/audio_source/audio_source.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/helpers.h"



namespace esphome {
namespace i2s_audio_sink {

class I2SAudioSink : public Component, public EntityBase {
 public:
  void dump_config() override;
  void setup() override;

  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_audio_source(audio_source::AudioSource *source);

  void set_dout_pin(uint8_t pin) { this->dout_pin_ = pin; }
  void set_bclk_pin(uint8_t pin) { this->bclk_pin_ = pin; }
  void set_lrclk_pin(uint8_t pin) { this->lrclk_pin_ = pin; }

 protected:
  audio_source::AudioSource *source_{nullptr};
  uint8_t dout_pin_{0};
  uint8_t bclk_pin_;
  uint8_t lrclk_pin_;

};

}  // namespace i2s_audio_sink
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ARDUINO
