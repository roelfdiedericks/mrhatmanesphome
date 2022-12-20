import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import audio_source, sensor
from esphome.const import (
    CONF_SENSOR_ID,
    CONF_THRESHOLD,
)

decibel_meter_ns = cg.esphome_ns.namespace("decibel_meter")

DecibelMeterSensor = decibel_meter_ns.class_(
    "DecibelMeterSensor", sensor.Sensor, cg.Component
)

CONF_SENSITIVITY = "sensitivity"
CONF_AUDIO_SOURCE = "audio_source"

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(DecibelMeterSensor),
        cv.Required(CONF_AUDIO_SOURCE): cv.use_id(audio_source.AudioSource),
        cv.Required(CONF_SENSITIVITY): cv.float_,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    source = await cg.get_variable(config[CONF_AUDIO_SOURCE])
    cg.add(var.set_audio_source(source))

    cg.add(var.set_sensitivity(config[CONF_SENSITIVITY]))
