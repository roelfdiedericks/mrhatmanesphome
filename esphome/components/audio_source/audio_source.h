#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sensor/filter.h"

#include <vector>

namespace esphome {
namespace audio_source {

class AudioSource : public EntityBase {
 public:
  explicit AudioSource();

  /** 
   *  8  bit samples : 1
   *  16 bit samples : 2
   *  24 bit samples : 3
   *  32 bit samples : 4
   */
  //const BYTES_PER_SAMPLE = 2;


  /** 
   *  Channel count
   *  1 Mono
   *  2 Stereo
   */
  //const CHANNEL_CPOUNT = 1;
  
  /** 
   *  Samples per second
   */
  //const uint32_t SAMPLES_PER_SECOND = 16000;
  
  uint8_t audio_buffer[16000*1*2 / 10];
  
  /** Publish a new state to the front-end.
   *
   * First, the new state will be assigned to the raw_value. Then it's passed through all filters
   * until it finally lands in the .value member variable and a callback is issued.
   *
   */
  void publish_audio(size_t size);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Add a callback that will be called every time a filtered value arrives.
  void add_audio_callback(std::function<void(uint8_t * , size_t)> &&callback);
  


  /** A unique ID for this sensor, empty for no unique id. See unique ID requirements:
   * https://developers.home-assistant.io/docs/en/entity_registry_index.html#unique-id-requirements
   *
   * @return The unique id as a string.
   */
  virtual std::string unique_id();


 protected:
 
  CallbackManager<void(uint8_t * , size_t)> callback_;      ///< Storage for audio buffer callbacks.
                        
};

}  // namespace audio_source
}  // namespace esphome
