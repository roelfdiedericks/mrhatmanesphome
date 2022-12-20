import esphome.codegen as cg
from esphome.components import audio_source
import esphome.config_validation as cv

from esphome import pins

from esphome.const import CONF_ID, CONF_MODE
from esphome.core import CORE

CODEOWNERS = ["@jesserockz"]
DEPENDENCIES = ["esp32"]

i2s_audio_source_ns = cg.esphome_ns.namespace("i2s_audio_source")

I2SAudioSource = i2s_audio_source_ns.class_(
    "I2SAudioSource", cg.Component, audio_source.AudioSource
)

CONF_I2S_DIN_PIN = "i2s_din_pin"
CONF_I2S_BCLK_PIN = "i2s_bclk_pin"
CONF_I2S_LRCLK_PIN = "i2s_lrclk_pin"
CONF_AUDIO_FREQUENCY = "audio_frequency"
CONF_BITS_PER_SAMPLE = "bits_per_sample"


CONFIG_SCHEMA = audio_source.AUDIO_SOURCE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(I2SAudioSource),
        cv.Required(CONF_I2S_DIN_PIN): pins.internal_gpio_input_pin_number,
        cv.Required(CONF_I2S_BCLK_PIN): pins.internal_gpio_output_pin_number,
        cv.Required(CONF_I2S_LRCLK_PIN): pins.internal_gpio_output_pin_number,
        cv.Required(CONF_AUDIO_FREQUENCY): cv.int_,
        cv.Required(CONF_BITS_PER_SAMPLE): cv.int_,
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_din_pin(config[CONF_I2S_DIN_PIN]))
    cg.add(var.set_bclk_pin(config[CONF_I2S_BCLK_PIN]))
    cg.add(var.set_lrclk_pin(config[CONF_I2S_LRCLK_PIN]))
    cg.add(var.set_audio_frequency(config[CONF_AUDIO_FREQUENCY]))
    cg.add(var.set_bits_per_sample(config[CONF_BITS_PER_SAMPLE]))
