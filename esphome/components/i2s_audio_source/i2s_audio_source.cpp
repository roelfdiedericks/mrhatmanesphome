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
	.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX ),
	.sample_rate = stream.audio_frequency,
	.bits_per_sample = (i2s_bits_per_sample_t)stream.bits_per_sample, // is fixed at 12bit, stereo, MSB
	.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
	.communication_format = I2S_COMM_FORMAT_STAND_I2S,
	.intr_alloc_flags = ESP_INTR_FLAG_LEVEL2,
	.dma_buf_count = 3,
	.dma_buf_len = 300,
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
  err = i2s_set_clk(I2S_NUM_0, stream.audio_frequency, (i2s_bits_per_sample_t)stream.bits_per_sample, (i2s_channel_t)stream.channels);

  if( err != ESP_OK){
	   ESP_LOGE(TAG, "'%s': Received audio setup error: %d", this->name_.c_str(), err);
  }
  

  return;
}

void I2SAudioSource::loop() {
  i2s_read(I2S_NUM_0, stream.audio_buffer , AUDIO_STREAM_BUFFER_SIZE, &(stream.audio_buffer_size), 0);
  this->publish_audio();
}

void I2SAudioSource::dump_config() {
  ESP_LOGCONFIG(TAG, "I2S Audio Source:");
  ESP_LOGCONFIG(TAG, "  LRClk Pin: %d", this->lrclk_pin_);
  ESP_LOGCONFIG(TAG, "  BClk Pin: %d", this->bclk_pin_);
  ESP_LOGCONFIG(TAG, "  Din Pin: %d", this->din_pin_);
  ESP_LOGCONFIG(TAG, "  Audio Frequency: %d", this->stream.audio_frequency);
  ESP_LOGCONFIG(TAG, "  Bits Per Sample: %d", this->stream.bits_per_sample);
  ESP_LOGCONFIG(TAG, "  Channels: %d", this->stream.channels);

}

}  // namespace i2s_audio_source
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ARDUINO
