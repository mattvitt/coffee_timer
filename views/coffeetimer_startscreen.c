#include "../coffeetimer.h"
#include <furi.h>
#include <furi_hal.h>
#include <input/input.h>
#include <gui/elements.h>

struct CoffeetimerStartscreen {
    View* view;
    CoffeetimerStartscreenCallback callback;
    void* context;
};


typedef struct {
    int some_value;
} CoffeetimerStartscreenModel;

void coffeetimer_startscreen_set_callback(
    CoffeetimerStartscreen* instance,
    CoffeetimerStartscreenCallback callback,
    void* context) {
    furi_assert(instance);
    furi_assert(callback);
    instance->callback = callback;
    instance->context = context;
}

void coffeetimer_startscreen_draw(Canvas* canvas, CoffeetimerStartscreenModel* model) {
    UNUSED(model);
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignTop, "Start Screen"); 
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str_aligned(canvas, 64, 22, AlignCenter, AlignTop, "Explain your app"); 
    canvas_draw_str_aligned(canvas, 64, 32, AlignCenter, AlignTop, "on this screen");
    elements_button_center(canvas, "Start"); 
}

static void coffeetimer_startscreen_model_init(CoffeetimerStartscreenModel* const model) {
    model->some_value = 1;
}

bool coffeetimer_startscreen_input(InputEvent* event, void* context) {
    furi_assert(context); 
    CoffeetimerStartscreen* instance = context;
    if (event->type == InputTypeRelease) {
        switch(event->key) {
            case InputKeyBack:
                with_view_model(
                    instance->view,
                    CoffeetimerStartscreenModel * model,
                    {
                        UNUSED(model);
                        instance->callback(CoffeetimerCustomEventStartscreenBack, instance->context);
                    },
                    true);
                break;
            case InputKeyLeft:
            case InputKeyRight:
            case InputKeyUp:
            case InputKeyDown:
            case InputKeyOk:
                with_view_model(
                    instance->view,
                    CoffeetimerStartscreenModel* model,
                    {
                        UNUSED(model);
                        instance->callback(CoffeetimerCustomEventStartscreenOk, instance->context);
                    },
                    true);
                break;
            case InputKeyMAX:
                break;
        }
    }
    return true;
}

void coffeetimer_startscreen_exit(void* context) {
    furi_assert(context);
}

void coffeetimer_startscreen_enter(void* context) {
    furi_assert(context);
    CoffeetimerStartscreen* instance = (CoffeetimerStartscreen*)context;
    with_view_model(
        instance->view,
        CoffeetimerStartscreenModel * model,
        {
            coffeetimer_startscreen_model_init(model);
        },
        true
    );
}

CoffeetimerStartscreen* coffeetimer_startscreen_alloc() {
    CoffeetimerStartscreen* instance = malloc(sizeof(CoffeetimerStartscreen));
    instance->view = view_alloc();
    view_allocate_model(instance->view, ViewModelTypeLocking, sizeof(CoffeetimerStartscreenModel));
    view_set_context(instance->view, instance); // furi_assert crashes in events without this
    view_set_draw_callback(instance->view, (ViewDrawCallback)coffeetimer_startscreen_draw);
    view_set_input_callback(instance->view, coffeetimer_startscreen_input);
    //view_set_enter_callback(instance->view, coffeetimer_startscreen_enter);
    //view_set_exit_callback(instance->view, coffeetimer_startscreen_exit);

    with_view_model(
        instance->view,
        CoffeetimerStartscreenModel * model,
        {
            coffeetimer_startscreen_model_init(model);
        },
        true
    );
    
    return instance;
}

void coffeetimer_startscreen_free(CoffeetimerStartscreen* instance) {
    furi_assert(instance);

    with_view_model(
        instance->view,
        CoffeetimerStartscreenModel * model,
        {
            UNUSED(model);
        },
        true);
    view_free(instance->view);
    free(instance);
}

View* coffeetimer_startscreen_get_view(CoffeetimerStartscreen* instance) {
    furi_assert(instance);
    return instance->view;
}

