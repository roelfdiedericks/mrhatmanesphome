#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/audio_source/audio_source.h"

namespace esphome {
namespace decibel_meter {

class DecibelMeterSensor : public Component, public sensor::Sensor {
 public:
  void dump_config() override;
  void setup() override;

  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_audio_source(audio_source::AudioSource *source);
  void set_sensitivity(float sensitivity) { this->sensitivity_ = sensitivity; }

 protected:
  audio_source::AudioSource *source_{nullptr};

  float sensitivity_;
};

}  // namespace decibel_meter
}  // namespace esphome
