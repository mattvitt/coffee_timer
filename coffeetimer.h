#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <notification/notification_messages.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/scene_manager.h>
#include <gui/modules/variable_item_list.h>
#include "scenes/coffeetimer_scene.h"
#include "views/coffeetimer_startscreen.h"
#include "views/coffeetimer_scene_1.h"
#include "views/coffeetimer_scene_2.h"
#include "helpers/coffeetimer_storage.h"

#define TAG "Coffeetimer"

typedef struct {
    Gui* gui;
    NotificationApp* notification;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    SceneManager* scene_manager;
    VariableItemList* variable_item_list;
    CoffeetimerStartscreen* coffeetimer_startscreen;
    CoffeetimerScene1* coffeetimer_scene_1;
    CoffeetimerScene2* coffeetimer_scene_2;
    uint32_t haptic; 
    uint32_t speaker;
    uint32_t led;
    uint32_t save_settings;
} Coffeetimer;

typedef enum {
    CoffeetimerViewIdStartscreen,
    CoffeetimerViewIdMenu,
    CoffeetimerViewIdScene1,
    CoffeetimerViewIdScene2,
    CoffeetimerViewIdSettings,
} CoffeetimerViewId;

typedef enum {
    CoffeetimerHapticOff,
    CoffeetimerHapticOn,
} CoffeetimerHapticState;

typedef enum {
    CoffeetimerSpeakerOff,
    CoffeetimerSpeakerOn,
} CoffeetimerSpeakerState;

typedef enum {
    CoffeetimerLedOff,
    CoffeetimerLedOn,
} CoffeetimerLedState;

typedef enum {
    CoffeetimerSettingsOff,
    CoffeetimerSettingsOn,
} CoffeetimerSettingsStoreState;
