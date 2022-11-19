#include "feature/ui_functions/leds.h"
#include QMK_KEYBOARD_H
#include "globals.h"

static uint8_t enabled = 1;

void update_leds(uint8_t layer)
{
    if (!enabled) return;

    // Check if Indicator LEDs should be on
    if (layer) {
        ergodox_board_led_on();
    } else {
        ergodox_board_led_off();
    }

    // Turn on LEDs to represent current layer (as binary)
    for (int i = NUM_LEDS; i > 0; i--) {
        if (layer >> (NUM_LEDS - i) & 0x1) {
            ergodox_right_led_on(i);
        } else {
            ergodox_right_led_off(i);
        }
    }
}

void set_led_enabled(uint8_t enable) 
{
    enabled = enable;    
    if (!enabled) ergodox_led_all_off();
}
