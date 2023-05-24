#pragma once

#include <gui/view.h>
#include "../helpers/coffeetimer_custom_event.h"

typedef struct CoffeetimerScene1 CoffeetimerScene1;

typedef void (*CoffeetimerScene1Callback)(CoffeetimerCustomEvent event, void* context);

void coffeetimer_scene_1_set_callback(
    CoffeetimerScene1* coffeetimer_scene_1,
    CoffeetimerScene1Callback callback,
    void* context);

View* coffeetimer_scene_1_get_view(CoffeetimerScene1* coffeetimer_static);

CoffeetimerScene1* coffeetimer_scene_1_alloc();

void coffeetimer_scene_1_free(CoffeetimerScene1* coffeetimer_static);