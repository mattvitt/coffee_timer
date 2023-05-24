#pragma once

#include <gui/view.h>
#include "../helpers/coffeetimer_custom_event.h"

typedef struct CoffeetimerStartscreen CoffeetimerStartscreen;

typedef void (*CoffeetimerStartscreenCallback)(CoffeetimerCustomEvent event, void* context);

void coffeetimer_startscreen_set_callback(
    CoffeetimerStartscreen* coffeetimer_startscreen,
    CoffeetimerStartscreenCallback callback,
    void* context);

View* coffeetimer_startscreen_get_view(CoffeetimerStartscreen* coffeetimer_static);

CoffeetimerStartscreen* coffeetimer_startscreen_alloc();

void coffeetimer_startscreen_free(CoffeetimerStartscreen* coffeetimer_static);