#include "decibel_meter.h"
#include "esphome/core/log.h"

namespace esphome {
namespace decibel_meter {

static const char *const TAG = "decibel_meter";

void DecibelMeterSensor::setup() {
}

void DecibelMeterSensor::set_audio_source(audio_source::AudioSource *source){
  this->source_ = source;

  this->source_->add_audio_callback([this](uint8_t * audio_data, size_t size) {
	
	//Convert to 16 bits
	//TODO fixme for not 16 nit streams
	
	int16_t * stream =  (int16_t *) audio_data;	
	int BYTES_PER_SAMPLE = 2;
	
	//Collect max 
	
	int16_t max = 0;
	
	for(int q =0; q< size/BYTES_PER_SAMPLE; q++){
		if(stream[q] > max){
			max = stream[q];
		}
	}
	

	
	float decibels = (20.0* log10( (float)max / (float)32767)) + this->sensitivity_ + 95.0 ;
	
	this->publish_state((float)decibels);
	
  });
}

void DecibelMeterSensor::dump_config() {
  LOG_SENSOR("", "Decibel Meter", this);
  ESP_LOGCONFIG(TAG, "  Sensitivity %.11f", this->sensitivity_);
}

}  // namespace decibel_meter
}  // namespace esphome
