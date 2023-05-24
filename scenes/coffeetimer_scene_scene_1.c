#include "../coffeetimer.h"
#include "../helpers/coffeetimer_custom_event.h"
#include "../views/coffeetimer_scene_1.h"

void coffeetimer_scene_1_callback(CoffeetimerCustomEvent event, void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, event);
}

void coffeetimer_scene_scene_1_on_enter(void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    coffeetimer_scene_1_set_callback(app->coffeetimer_scene_1, coffeetimer_scene_1_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, CoffeetimerViewIdScene1);
}

bool coffeetimer_scene_scene_1_on_event(void* context, SceneManagerEvent event) {
    Coffeetimer app = context;
    bool consumed = false;
    
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
            case CoffeetimerCustomEventScene1Left:
            case CoffeetimerCustomEventScene1Right:
                break;
            case CoffeetimerCustomEventScene1Up:
            case CoffeetimerCustomEventScene1Down:
                break;
            case CoffeetimerCustomEventScene1Back:
                notification_message(app->notification, &sequence_reset_red);
                notification_message(app->notification, &sequence_reset_green);
                notification_message(app->notification, &sequence_reset_blue);
                if(!scene_manager_search_and_switch_to_previous_scene(
                    app->scene_manager, CoffeetimerSceneMenu)) {
                        scene_manager_stop(app->scene_manager);
                        view_dispatcher_stop(app->view_dispatcher);
                    }
                consumed = true;
                break;
        }
    }
    
    return consumed;
}

void coffeetimer_scene_scene_1_on_exit(void* context) {
    Coffeetimer app = context;
    UNUSED(app);
}