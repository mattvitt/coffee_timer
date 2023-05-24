#include "coffeetimer.h"

bool coffeetimer_custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    Coffeetimer* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, event);
}

void coffeetimer_tick_event_callback(void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    scene_manager_handle_tick_event(app->scene_manager);
}

//leave app if back button pressed
bool coffeetimer_navigation_event_callback(void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

Coffeetimer* coffeetimer_app_alloc() {
    Coffeetimer* app = malloc(sizeof(Coffeetimer));
    app->gui = furi_record_open(RECORD_GUI);
    app->notification = furi_record_open(RECORD_NOTIFICATION);
    
    //Turn backlight on, believe me this makes testing your app easier
    notification_message(app->notification, &sequence_display_backlight_on);

    //Scene additions
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);

    app->scene_manager = scene_manager_alloc(&coffeetimer_scene_handlers, app);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, coffeetimer_navigation_event_callback);
    view_dispatcher_set_tick_event_callback(app->view_dispatcher, coffeetimer_tick_event_callback, 100);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, coffeetimer_custom_event_callback);
    app->submenu = submenu_alloc();

    // Set defaults, in case no config loaded
    app->haptic = 1;
    app->speaker = 1;
    app->led = 1;
    app->save_settings = 1;

    // Load configs
    coffeetimer_read_settings(app);

    view_dispatcher_add_view(app->view_dispatcher, CoffeetimerViewIdMenu, submenu_get_view(app->submenu));
    app->coffeetimer_startscreen = coffeetimer_startscreen_alloc();
    view_dispatcher_add_view(app->view_dispatcher, CoffeetimerViewIdStartscreen, coffeetimer_startscreen_get_view(app->coffeetimer_startscreen));
    app->coffeetimer_scene_1 = coffeetimer_scene_1_alloc();
    view_dispatcher_add_view(app->view_dispatcher, CoffeetimerViewIdScene1, coffeetimer_scene_1_get_view(app->coffeetimer_scene_1));
    app->coffeetimer_scene_2 = coffeetimer_scene_2_alloc();
    view_dispatcher_add_view(app->view_dispatcher, CoffeetimerViewIdScene2, coffeetimer_scene_2_get_view(app->coffeetimer_scene_2));
    app->variable_item_list = variable_item_list_alloc();
    view_dispatcher_add_view(app->view_dispatcher, CoffeetimerViewIdSettings, variable_item_list_get_view(app->variable_item_list));

    //End Scene Additions

    return app;
}

void coffeetimer_app_free(Coffeetimer* app) {
    furi_assert(app);
    
    // Scene manager
    scene_manager_free(app->scene_manager);

    // View Dispatcher
    view_dispatcher_remove_view(app->view_dispatcher, CoffeetimerViewIdMenu);
    view_dispatcher_remove_view(app->view_dispatcher, CoffeetimerViewIdScene1);
    view_dispatcher_remove_view(app->view_dispatcher, CoffeetimerViewIdScene2);
    view_dispatcher_remove_view(app->view_dispatcher, CoffeetimerViewIdSettings);
    submenu_free(app->submenu);

    view_dispatcher_free(app->view_dispatcher);
    furi_record_close(RECORD_GUI);
    
    app->gui = NULL;
    app->notification = NULL;

    //Remove whatever is left
    free(app);
}

int32_t coffeetimer_app(void* p) {
    UNUSED(p);
    Coffeetimer* app = coffeetimer_app_alloc();
    
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    
    scene_manager_next_scene(app->scene_manager, CoffeetimerSceneStartscreen); //Start with start screen
    //scene_manager_next_scene(app->scene_manager, CoffeetimerSceneMenu); //if you want to directly start with Menu

    furi_hal_power_suppress_charge_enter();

    view_dispatcher_run(app->view_dispatcher);

    coffeetimer_save_settings(app);
    
    furi_hal_power_suppress_charge_exit();
    coffeetimer_app_free(app);

    return 0;
}



