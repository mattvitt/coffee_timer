#include "../coffeetimer.h"
#include "../helpers/coffeetimer_custom_event.h"
#include "../views/coffeetimer_startscreen.h"

void coffeetimer_scene_startscreen_callback(CoffeetimerCustomEvent event, void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, event);
}

void coffeetimer_scene_startscreen_on_enter(void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    coffeetimer_startscreen_set_callback(app->coffeetimer_startscreen, coffeetimer_scene_startscreen_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, CoffeetimerViewIdStartscreen);
}

bool coffeetimer_scene_startscreen_on_event(void* context, SceneManagerEvent event) {
    Coffeetimer* app = context;
    bool consumed = false;
    
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
            case CoffeetimerCustomEventStartscreenLeft:
            case CoffeetimerCustomEventStartscreenRight:
                break;
            case CoffeetimerCustomEventStartscreenUp:
            case CoffeetimerCustomEventStartscreenDown:
                break;
            case CoffeetimerCustomEventStartscreenOk:
                scene_manager_next_scene(app->scene_manager, CoffeetimerSceneMenu);
                consumed = true;
                break;
            case CoffeetimerCustomEventStartscreenBack:
                notification_message(app->notification, &sequence_reset_red);
                notification_message(app->notification, &sequence_reset_green);
                notification_message(app->notification, &sequence_reset_blue);
                if(!scene_manager_search_and_switch_to_previous_scene(
                    app->scene_manager, CoffeetimerSceneStartscreen)) {
                        scene_manager_stop(app->scene_manager);
                        view_dispatcher_stop(app->view_dispatcher);
                    }
                consumed = true;
                break;
        }
    }
    
    return consumed;
}

void coffeetimer_scene_startscreen_on_exit(void* context) {
    Coffeetimer* app = context;
    UNUSED(app);
}