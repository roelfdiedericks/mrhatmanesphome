from esphome import automation
import esphome.config_validation as cv
import esphome.codegen as cg

from esphome.automation import maybe_simple_id
from esphome.const import CONF_ID, CONF_ON_STATE, CONF_TRIGGER_ID
from esphome.core import CORE
from esphome.coroutine import coroutine_with_priority
from esphome.cpp_helpers import setup_entity


CODEOWNERS = ["@jesserockz"]

IS_PLATFORM_COMPONENT = True

audio_source_ns = cg.esphome_ns.namespace("audio_source")

AudioSource = audio_source_ns.class_("AudioSource")


async def setup_audio_source_core_(var, config):
    await setup_entity(var, config)


async def register_audio_source(var, config):
    if not CORE.has_id(config[CONF_ID]):
        var = cg.Pvariable(config[CONF_ID], var)
    cg.add(cg.App.register_audio_source(var))
    await setup_audio_source_core_(var, config)


AUDIO_SOURCE_SCHEMA = cv.ENTITY_BASE_SCHEMA.extend({})


@coroutine_with_priority(100.0)
async def to_code(config):
    cg.add_global(audio_source_ns.using)
    cg.add_define("USE_AUDIO_SOURCE")
