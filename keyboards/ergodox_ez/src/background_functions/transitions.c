#include "include/background_functions/transitions.h"

#include "globals.h"

#include "feature/background_functions/sleep.h"
#include "feature/ui_functions/rgb_light.h"
#include "feature/ui_functions/leds.h"


// Function Prototypes
static void disable_all(void);
static void enable_all(void);
static void update_all(void);

void transition(transition_t state)
{
    switch (state)
    {
        #if defined(SCAGLE_SLEEP_ENABLE)
        case WAKEUP_FROM_IDLE:
            enable_all();
            break;

        case SLEEP_FROM_IDLE:
            disable_all();
            break;
        #endif  // defined(SCAGLE_SLEEP_ENABLE)

        case WAKEUP_FROM_POWER:
            debug_enable = DISABLED;
            enable_all();
            break;

        case WAKEUP_FROM_HOST:
            enable_all();
            break;

        case SLEEP_FROM_HOST:
            disable_all();
            break;

        default:
            break;
    }
}

static void disable_all(void)
{
    rgblight_disable_noeeprom();
    set_led_enabled(DISABLED);
}

static void enable_all(void)
{
    rgblight_enable_noeeprom();
    set_led_enabled(ENABLED);
    update_all();
}

static void update_all(void)
{
    #if defined(SCAGLE_LEDS_ENABLE)
    update_leds(biton32(GLOBAL_LAYER_STATE));
    #endif  // defined(SCAGLE_LEDS_ENABLE)

    #if defined(RGBLIGHT_ENABLE)
    update_rgb(biton32(GLOBAL_LAYER_STATE));
    #endif  // defined(RGBLIGHT_ENABLE)
}

