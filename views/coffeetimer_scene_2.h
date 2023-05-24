#pragma once

#include <gui/view.h>
#include "../helpers/coffeetimer_custom_event.h"

typedef struct CoffeetimerScene2 CoffeetimerScene2;

typedef void (*CoffeetimerScene2Callback)(CoffeetimerCustomEvent event, void* context);

void coffeetimer_scene_2_set_callback(
    CoffeetimerScene2* instance,
    CoffeetimerScene2Callback callback,
    void * context);

CoffeetimerScene2* coffeetimer_scene_2_alloc();

void coffeetimer_scene_2_free(CoffeetimerScene2* coffeetimer_static);

View* coffeetimer_scene_2_get_view(CoffeetimerScene2* boilerpate_static);
