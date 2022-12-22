import esphome.codegen as cg
from esphome.components import audio_source
import esphome.config_validation as cv

from esphome import pins

from esphome.const import CONF_ID, CONF_MODE
from esphome.core import CORE

CODEOWNERS = ["@jesserockz"]
DEPENDENCIES = ["esp32"]

sound_generator_ns = cg.esphome_ns.namespace("sound_generator")

SoundGenerator = sound_generator_ns.class_(
    "SoundGenerator", cg.Component, audio_source.AudioSource
)

CONF_PITCH = "pitch"
CONF_VOLUME = "volume"
CONF_AUDIO_FREQUENCY = "audio_frequency"
CONF_BITS_PER_SAMPLE = "bits_per_sample"
CHANNEL_OPTIONS = ["mono", "stereo"]

CONFIG_SCHEMA = audio_source.AUDIO_SOURCE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SoundGenerator),
        cv.Required(CONF_PITCH): cv.int_,
        cv.Required(CONF_VOLUME): cv.float_,
        cv.Required(CONF_AUDIO_FREQUENCY): cv.int_,
        cv.Required(CONF_BITS_PER_SAMPLE): cv.int_,
        cv.Optional(CONF_MODE, default="mono"): cv.one_of(
            *CHANNEL_OPTIONS, lower=True
        ),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_pitch(config[CONF_PITCH]))
    cg.add(var.set_volume(config[CONF_VOLUME]))
    cg.add(var.set_audio_frequency(config[CONF_AUDIO_FREQUENCY]))
    cg.add(var.set_bits_per_sample(config[CONF_BITS_PER_SAMPLE]))
    cg.add(var.set_channels(2 if config[CONF_MODE] == "stereo" else 1))
