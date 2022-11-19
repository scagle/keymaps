#include "feature/key_functions/combo.h"
#include QMK_KEYBOARD_H
#include "globals.h"

static uint8_t current_layer = HUB;

const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, KC_F, COMBO_END};

// Note: When adding/deleting, you must update the COMBO_COUNT in
//       config.h to match the number of combos in this array.
combo_t key_combos[COMBO_COUNT] = {
    [CO_QWERTY_ART] = COMBO_ACTION(sdf_combo),
};


void process_combo_event(uint16_t combo_index, bool pressed)
{
    switch (combo_index)
    {
        case CO_QWERTY_ART:

            if (pressed)
            {
                if      (current_layer == HUB)  tap_code16(TO(ART1));
                else if (current_layer == ART1) tap_code16(TO(HUB));
            }
    }
}

void update_combo(const uint8_t layer)
{
    current_layer = layer;
}
