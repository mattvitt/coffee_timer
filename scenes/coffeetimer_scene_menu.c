#include "../coffeetimer.h"

enum SubmenuIndex {
    SubmenuIndexScene1 = 10,
    SubmenuIndexScene2,
    SubmenuIndexSettings,
};

void coffeetimer_scene_menu_submenu_callback(void* context, uint32_t index) {
    Coffeetimer* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void coffeetimer_scene_menu_on_enter(void* context) {
    Coffeetimer* app = context;

    submenu_add_item(app->submenu, "Scene 1", SubmenuIndexScene1, coffeetimer_scene_menu_submenu_callback, app);
    submenu_add_item(app->submenu, "Scene 2", SubmenuIndexScene2, coffeetimer_scene_menu_submenu_callback, app);
    submenu_add_item(app->submenu, "Settings", SubmenuIndexSettings, coffeetimer_scene_menu_submenu_callback, app);

    submenu_set_selected_item(app->submenu, scene_manager_get_scene_state(app->scene_manager, CoffeetimerSceneMenu));

    view_dispatcher_switch_to_view(app->view_dispatcher, CoffeetimerViewIdMenu);
}

bool coffeetimer_scene_menu_on_event(void* context, SceneManagerEvent event) {
    Coffeetimer* app = context;
    UNUSED(app);
    if(event.type == SceneManagerEventTypeBack) {
        //exit app
        scene_manager_stop(app->scene_manager);
        view_dispatcher_stop(app->view_dispatcher);
        return true;
    } else if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexScene1) {
            scene_manager_set_scene_state(
                app->scene_manager, CoffeetimerSceneMenu, SubmenuIndexScene1);
            scene_manager_next_scene(app->scene_manager, CoffeetimerSceneScene_1);
            return true;
        } else if (event.event == SubmenuIndexScene2) {
            scene_manager_set_scene_state(
                app->scene_manager, CoffeetimerSceneMenu, SubmenuIndexScene2);
            scene_manager_next_scene(app->scene_manager, CoffeetimerSceneScene_2);
            return true;
        } else if (event.event == SubmenuIndexSettings) {
            scene_manager_set_scene_state(
                app->scene_manager, CoffeetimerSceneMenu, SubmenuIndexSettings);
            scene_manager_next_scene(app->scene_manager, CoffeetimerSceneSettings);
            return true;
        }
    }
    return false;
}

void coffeetimer_scene_menu_on_exit(void* context) {
    Coffeetimer* app = context;
    submenu_reset(app->submenu);
}