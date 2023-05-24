#include "coffeetimer_scene.h"

// Generate scene on_enter handlers array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_enter,
void (*const coffeetimer_on_enter_handlers[])(void*) = {
#include "coffeetimer_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_event handlers array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_event,
bool (*const coffeetimer_on_event_handlers[])(void* context, SceneManagerEvent event) = {
#include "coffeetimer_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_exit handlers array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_exit,
void (*const coffeetimer_on_exit_handlers[])(void* context) = {
#include "coffeetimer_scene_config.h"
};
#undef ADD_SCENE

// Initialize scene handlers configuration structure
const SceneManagerHandlers coffeetimer_scene_handlers = {
    .on_enter_handlers = coffeetimer_on_enter_handlers,
    .on_event_handlers = coffeetimer_on_event_handlers,
    .on_exit_handlers = coffeetimer_on_exit_handlers,
    .scene_num = CoffeetimerSceneNum,
};
