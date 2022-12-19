#include "i2s_audio_source.h"

#ifdef USE_ESP32_FRAMEWORK_ARDUINO

#include "esphome/core/log.h"
#include <driver/i2s.h>

namespace esphome {
namespace i2s_audio_source {

static const char *const TAG = "i2s_audio_source";



void I2SAudioSource::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Audio...");
  esp_err_t err = ESP_OK;

  i2s_config_t i2s_config = {
	.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
	.sample_rate = 16000,
	.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
	.channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
	.communication_format = I2S_COMM_FORMAT_STAND_I2S,
	.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
	.dma_buf_count = 6,
	.dma_buf_len = 60,
  };


  ESP_LOGV(TAG, "'%s': Installing driver", this->name_.c_str());
  err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  
  if( err != ESP_OK){
	   ESP_LOGE(TAG, "'%s': Received audio setup error: %d", this->name_.c_str(), err);
  }
  i2s_pin_config_t tx_pin_config;

  tx_pin_config.mck_io_num = 0;
  tx_pin_config.bck_io_num = this->bclk_pin_;
  tx_pin_config.ws_io_num = this->lrclk_pin_;
  tx_pin_config.data_out_num = 0;
  tx_pin_config.data_in_num = this->din_pin_;


  ESP_LOGV(TAG, "'%s': setting pins", this->name_.c_str());
  err = i2s_set_pin(I2S_NUM_0, &tx_pin_config);
  if( err != ESP_OK){
	   ESP_LOGE(TAG, "'%s': Received audio setup error: %d", this->name_.c_str(), err);
  }
  
  ESP_LOGV(TAG, "'%s':setting clocks", this->name_.c_str());
  err = i2s_set_clk(I2S_NUM_0, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

  if( err != ESP_OK){
	   ESP_LOGE(TAG, "'%s': Received audio setup error: %d", this->name_.c_str(), err);
  }
  
  return;
}

void I2SAudioSource::loop() {
  size_t byte_read;
  i2s_read(I2S_NUM_0, audio_buffer, 1024, &byte_read, 0);
  this->publish_audio(byte_read);
}

void I2SAudioSource::dump_config() {
  ESP_LOGCONFIG(TAG, "Audio:");

}

}  // namespace i2s_audio_source
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ARDUINO
