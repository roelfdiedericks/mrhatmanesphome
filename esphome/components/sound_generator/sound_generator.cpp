#include "sound_generator.h"

#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sound_generator {

static const char *const TAG = "sound_generator";



void SoundGenerator::setup() {
  //create a buffer

  //time of a full audio buffer 

  int32_t max_samples = (AUDIO_STREAM_BUFFER_SIZE )/(stream.bits_per_sample/8);
  ESP_LOGD(TAG,"max samples = %d", max_samples); 

  float full_buffer_time = (float)max_samples/ (float)stream.audio_frequency ;
  ESP_LOGD(TAG,"full buffer time = %f", full_buffer_time); 
  //time of a full sign wave at given pitch
  float pitch_time = 1.0 / sound_pitch_;
  ESP_LOGD(TAG,"pitch_time = %f", pitch_time); 

  //signwaves per buffer
  int waves_per_buffer = floor(full_buffer_time/pitch_time);

  ESP_LOGD(TAG,"waves_per_buffer = %d", waves_per_buffer); 

  //Make sure buffer is not too small
  if( waves_per_buffer < 1){
    ESP_LOGE(TAG,"Pitch too low %f %f", full_buffer_time,pitch_time);
  } 

  size_t buffer_size =(size_t) ((pitch_time / full_buffer_time) * (float)waves_per_buffer * (float)max_samples);

  ESP_LOGD(TAG,"buffer_size = %d", buffer_size); 

  for(int q = 0; q< buffer_size ; q++){
    float float_sample = sound_volume_ *  sin(6.28318530718 * waves_per_buffer * ((float) q / (float) buffer_size )) ; 

      int32_t sample = 0;

      switch (stream.bits_per_sample)
      {
      case 8:
        ((int8_t * )stream.audio_buffer)[q] = float_sample * (float) ((1<<7) -1);
        break;
      case 16:
        ((int16_t * )stream.audio_buffer)[q] = float_sample * (float) ((1<<15) -1);
        break;
      case 24:
        break;
      case 32:
        ((int32_t * )stream.audio_buffer)[q] = float_sample * (float) ((1<<31) -1);
        break;
      
      default:
        break;
      } 

      //ESP_LOGD(TAG,"%d",((int16_t * )stream.audio_buffer)[q]);
  }
  ESP_LOGD(TAG,"%d",((int16_t * )stream.audio_buffer)[buffer_size-1]);

  stream.audio_buffer_size = buffer_size*(stream.bits_per_sample/8);

  full_buffer_time_ = (uint32_t)(((float)buffer_size / (float)stream.audio_frequency  )*1000000.0);

  ESP_LOGD(TAG,"%f %d", full_buffer_time , buffer_size); 

  publish_audio();

  ESP_LOGD(TAG,"end %f %d", full_buffer_time , buffer_size); 

  next_time_ = micros() +  full_buffer_time_;

  return;
}

void SoundGenerator::loop() {
  while( micros() + full_buffer_time_ > next_time_)
  {
    ESP_LOGD(TAG,"%d + %d > %d",  micros() , full_buffer_time_ , next_time_); 
    next_time_ += full_buffer_time_;
    publish_audio();
  }
  ESP_LOGD(TAG,"here"); 
}

void SoundGenerator::dump_config() {
  ESP_LOGCONFIG(TAG, "Sound Generator:");
  ESP_LOGCONFIG(TAG, "  Pitch: %d", this->sound_pitch_);
  ESP_LOGCONFIG(TAG, "  Volume: %f11", this->sound_volume_);
  ESP_LOGCONFIG(TAG, "  Audio Frequency: %d", this->stream.audio_frequency);
  ESP_LOGCONFIG(TAG, "  Bits Per Sample: %d", this->stream.bits_per_sample);
  ESP_LOGCONFIG(TAG, "  Channels: %d", this->stream.channels);

}

}  // namespace sound_generator
}  // namespace esphome

