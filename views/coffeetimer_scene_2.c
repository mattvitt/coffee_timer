#include "../coffeetimer.h"
#include <furi.h>
#include <furi_hal.h>
#include <input/input.h>
#include <gui/elements.h>
#include <dolphin/dolphin.h>
#include "../helpers/coffeetimer_haptic.h"
#include "../helpers/coffeetimer_speaker.h"
#include "../helpers/coffeetimer_led.h"

struct CoffeetimerScene2 {
    View* view;
    CoffeetimerScene2Callback callback;
    void* context;
};

typedef struct {
    int screen_text;
} CoffeetimerScene2Model;

char buttonText[11][14] = {
    "",
    "Press Up",
    "Press Down",
    "Press Left",
    "Press Right",
    "Press Ok",
    "Release Up",
    "Release Down",
    "Release Left",
    "Release Right",
    "Release Ok",
};

void coffeetimer_scene_2_set_callback(
    CoffeetimerScene2* instance,
    CoffeetimerScene2Callback callback,
    void* context) {
    furi_assert(instance);
    furi_assert(callback);
    instance->callback = callback;
    instance->context = context;
}

void coffeetimer_scene_2_draw(Canvas* canvas, CoffeetimerScene2Model* model) {
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 0, 10, AlignLeft, AlignTop, "Scene 2: Input Examples"); 
    canvas_set_font(canvas, FontSecondary);
    char *strInput = malloc(15);
    strcpy(strInput, buttonText[model->screen_text]);
    canvas_draw_str_aligned(canvas, 0, 22, AlignLeft, AlignTop, strInput); 
    free(strInput);
}

static void coffeetimer_scene_2_model_init(CoffeetimerScene2Model* const model) {
    model->screen_text = 0;
}

bool coffeetimer_scene_2_input(InputEvent* event, void* context) {
    furi_assert(context);
    CoffeetimerScene2* instance = context;
    if (event->type == InputTypeRelease) {
        switch(event->key) {
            case InputKeyBack:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        UNUSED(model);
                        coffeetimer_stop_all_sound(instance->context);
                        instance->callback(CoffeetimerCustomEventScene2Back, instance->context);
                        coffeetimer_play_long_bump(instance->context);
                    },
                    true);
                break;
            case InputKeyUp:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 6;
                        coffeetimer_play_bad_bump(instance->context);
                        coffeetimer_stop_all_sound(instance->context);
                        coffeetimer_led_set_rgb(instance->context, 255, 0, 255);
                    },
                    true);
                break;
            case InputKeyDown:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 7;
                        coffeetimer_play_bad_bump(instance->context);
                        coffeetimer_stop_all_sound(instance->context);
                        coffeetimer_led_set_rgb(instance->context, 255, 255, 0);
                    },
                    true);
                break;
            case InputKeyLeft:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 8;
                        coffeetimer_play_bad_bump(instance->context);
                        coffeetimer_stop_all_sound(instance->context);
                        coffeetimer_led_set_rgb(instance->context, 0, 255, 255);
                    },
                    true);
                break;
            case InputKeyRight:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 9;
                        coffeetimer_play_bad_bump(instance->context);
                        coffeetimer_stop_all_sound(instance->context);
                        coffeetimer_led_set_rgb(instance->context, 255, 0, 0);
                    },
                    true);
                break;
            case InputKeyOk:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 10;
                        coffeetimer_play_bad_bump(instance->context);
                        coffeetimer_stop_all_sound(instance->context);
                        coffeetimer_led_set_rgb(instance->context, 255, 255, 255);
                    },
                    true);
                break;
            case InputKeyMAX:
                break;
        }
    } else if (event->type == InputTypePress) {
         switch(event->key) {
            case InputKeyUp:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 1;
                        coffeetimer_play_happy_bump(instance->context);
                        coffeetimer_play_input_sound(instance->context);
                    },
                    true);
                break;
            case InputKeyDown:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 2;
                        coffeetimer_play_happy_bump(instance->context);
                        coffeetimer_play_input_sound(instance->context);
                    },
                    true);
                break;
            case InputKeyLeft:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 3;
                        coffeetimer_play_happy_bump(instance->context);
                        coffeetimer_play_input_sound(instance->context);
                    },
                    true);
                break;
            case InputKeyRight:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 4;
                        coffeetimer_play_happy_bump(instance->context);
                        coffeetimer_play_input_sound(instance->context);
                    },
                    true);
                break;
            case InputKeyOk:
                with_view_model(
                    instance->view,
                    CoffeetimerScene2Model * model,
                    {
                        model->screen_text = 5;
                        coffeetimer_play_happy_bump(instance->context);
                        coffeetimer_play_input_sound(instance->context);
                    },
                    true);
                break;
            case InputKeyBack:
            case InputKeyMAX:
                break;
        }
    }
    
    return true;
}

void coffeetimer_scene_2_exit(void* context) {
    furi_assert(context);
    Coffeetimer* app = context;
    coffeetimer_stop_all_sound(app);
    //coffeetimer_led_reset(app);
}

void coffeetimer_scene_2_enter(void* context) {
    furi_assert(context);
    DOLPHIN_DEED(DolphinDeedPluginStart);
}

CoffeetimerScene2* coffeetimer_scene_2_alloc() {
    CoffeetimerScene2* instance = malloc(sizeof(CoffeetimerScene2));
    instance->view = view_alloc();
    view_allocate_model(instance->view, ViewModelTypeLocking, sizeof(CoffeetimerScene2Model));
    view_set_context(instance->view, instance);
    view_set_draw_callback(instance->view, (ViewDrawCallback)coffeetimer_scene_2_draw);
    view_set_input_callback(instance->view, coffeetimer_scene_2_input);
    //view_set_enter_callback(instance->view, coffeetimer_scene_2_enter);
    view_set_exit_callback(instance->view, coffeetimer_scene_2_exit);

    with_view_model(
        instance->view,
        CoffeetimerScene2Model * model,
        {
            coffeetimer_scene_2_model_init(model);
        },
        true);
    
    return instance;
}

void coffeetimer_scene_2_free(CoffeetimerScene2* instance) {
    furi_assert(instance);


    view_free(instance->view);
    free(instance);
}

View* coffeetimer_scene_2_get_view(CoffeetimerScene2* instance) {
    furi_assert(instance);


    return instance->view;
}

