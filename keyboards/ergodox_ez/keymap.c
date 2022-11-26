// vim: foldmethod=marker

// Quick Help for Vim users, as this file will be folded by markers
//     Vim-Folds:
//         zo     open fold
//         zc     close fold
//         zj/zk  jump between folds
//         zn     no folds (disable them)
//         zM     fold everything (enable them)

// Includes {{{

#include QMK_KEYBOARD_H   // [KC_*, TO(), etc] (defined externally)
#include "version.h"      // [LAYOUT_ergodox]  (defined externally)
#include "globals.h"

#include "include/background_functions/transitions.h"

#include "feature/ui_functions/leds.h"
#include "feature/ui_functions/rgb_light.h"
#include "feature/key_functions/tap_dance.h"
#include "feature/key_functions/key_swap.h"
#include "feature/key_functions/combo.h"
#include "feature/background_functions/sleep.h"

// }}}

// Spongebob Mock States {{{
static bool alt_case_toggle = false;
static bool alt_case_shift  = false;
// }}}

// Keyboard Layer Mappings {{{
// For all keycodes go here: ../../../../docs/keycodes.md

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

    // Central Hub: Acts as router to other layers {{{

    [HUB] = LAYOUT_ergodox(

        // Left Hand {{{

        KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,
        KC_TAB,         TO(QWERTY),     ______________, ______________, ______________, ______________, CKC_DOCS,
        KC_LCTL,        TO(UI),         ______________, ______________, ______________, ______________,
        KC_LALT,        ______________, ______________, ______________, AG_TOGG,        TD(TD_SWAP_OS), CKC_SHOW_VERSION,
        ______________, ______________, ______________, ______________, TT(EXTRA),

        // Thumb cluster
                        ______________, ______________,
                                        ______________,
        KC_SPACE,       KC_LSHIFT,      TRI_LEFT,

        //}}}

        // Right Hand {{{

        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_F13,
        ______________, ______________, ______________, ______________, ______________, ______________, KC_F14,
                        ______________, ______________, ______________, ______________, ______________, KC_ENTER,
        ______________, ______________, ______________, ______________, ______________, ______________, ______________,
                                        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       ______________,

        // Thumb cluster
        RESET,          ______________,
        ______________,
        TRI_RIGHT,      KC_ENTER,       KC_BSPACE

        //}}}

    ),

    //}}}

    // QWERTY Base {{{

    [QWERTY] = LAYOUT_ergodox(

        // Left Hand {{{

        KC_ESC,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           XXXXXXXXXXXXXX,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           XXXXXXXXXXXXXX,
        KC_LCTL,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_LALT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           XXXXXXXXXXXXXX,
        TO(HUB),        XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX,

        // Thumb cluster
                        MO(NUMPAD),     ALTCASE,
                                        KC_LCMD,
        KC_SPACE,       KC_LSHIFT,      TRI_LEFT,

        //}}}

        // Right Hand {{{

        XXXXXXXXXXXXXX, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           XXXXXXXXXXXXXX,
        XXXXXXXXXXXXXX, KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_SLASH,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOT,
        XXXXXXXXXXXXXX, KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       LT(EXTRA, KC_ENTER),
                                        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_MEH,

        // Thumb cluster
        XXXXXXXXXXXXXX, XXXXXXXXXXXXXX,
        KC_RCMD,
        TRI_RIGHT,      KC_ENTER,       KC_BSPACE

        //}}}

    ),

    //}}}

    // Generic Symbols {{{

    [SYMBOLS] = LAYOUT_ergodox(

        // Left Hand {{{

        ______________, ______________, ______________, ______________, ______________, ______________, ______________,
        ______________, KC_PLUS,        KC_PIPE,        KC_LABK,        KC_SLSH,        KC_GRV,         ______________,
        MO(EXTRA),      KC_MINS,        KC_LCBR,        KC_LBRC,        KC_LPRN,        KC_TILD,
        MO(NUMPAD),     KC_EXLM,        KC_AT,          KC_DQUO,        KC_DLR,         KC_PERC,        ______________,
        TO(HUB),        ______________, ______________, ______________, ______________,

        // Thumb cluster
                        ______________, ______________,
                                        ______________,
        KC_SPACE,       KC_LSHIFT,      ___CRITICAL___,

        //}}}

        // Right Hand {{{

        ______________, ______________, ______________, ______________, ______________, ______________, ______________,
        ______________, KC_QUOT,        KC_BSLASH,      KC_RABK,        KC_AMPR,        ______________, ______________,
                        KC_DQT,         KC_RPRN,        KC_RBRC,        KC_RCBR,        KC_UNDS,        ______________,
        ______________, KC_CIRC,        KC_AMPR,        KC_ASTR,        ______________, KC_EQUAL,       ______________,
                                        ______________, ______________, ______________, ______________, ______________,

        // Thumb cluster
        ______________, ______________,
        ______________,
        TRI_RIGHT,      KC_ENTER,       KC_BSPACE

        //}}}

    ),

    //}}}

    // NUMPAD Base {{{
    // @brief Main NUMPAD layer with programmable buttons on left hand to allow more than enough remappable keys for applications
    // @note https://github.com/qmk/qmk_firmware/blob/master/docs/feature_programmable_button.md

    [NUMPAD] = LAYOUT_ergodox(

        // Left Hand {{{
        ______________, KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    ______________, ______________,
        ______________, KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_PLUS,     ______________, ______________,
        ______________, KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_ENTER,    ______________,
        ___CRITICAL___, KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_0,        ______________, ______________,
        ______________, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX,

        // Thumb cluster
                        ___CRITICAL___, ______________,
                                        ______________,
        ______________, MO(EXTRA),      TRI_LEFT,

        //}}}

        // Right Hand {{{

        KC_INSERT,      KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    KC_INSERT,      KC_HOME,
        KC_PGUP,        KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_PLUS,     KC_DELETE,      KC_END,
                        KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_EQUAL,       KC_PGDOWN,      KC_PGUP,
        KC_PGDOWN,      KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_ENTER,    XXXXXXXXXXXXXX, XXXXXXXXXXXXXX,
                                        KC_KP_0,        KC_KP_DOT,      XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX,

        // Thumb cluster
        ______________, ______________,
        ______________,
        ___CRITICAL___, ______________, ______________

        //}}}

    ),

    //}}}

    // EXTRA {{{
    // @note For F13-F24 keys, the intention here is to have left thumb mash the MO(NUMPAD) + SHIFT buttons to allow
    //       left-handed access to the upper function keys (for games where extra inputs are useful, that don't need
    //       to be pressed quickly)

    [EXTRA] = LAYOUT_ergodox(

        // Left Hand {{{

        ______________, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,
        ______________, KC_F13,         KC_F14,         KC_F15,         KC_F16,         ______________, ______________,
        ___CRITICAL___, KC_F17,         KC_F18,         KC_F19,         KC_F20,         ______________,
        ______________, KC_F21,         KC_F22,         KC_F23,         KC_F24,         ______________, ______________,
        TO(HUB),        ______________, ______________, ______________, ______________,

        // Thumb cluster
                        ______________, ______________,
                                        ______________,
        ______________, ___CRITICAL___, ______________,

        //}}}

        // Right Hand {{{

        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         ______________,
        ______________, ______________, ______________, ______________, ______________, ______________, ______________,
                        ______________, ______________, ______________, ______________, ______________, ______________,
        ______________, ______________, ______________, ______________, ______________, ______________, ______________,
                                        ______________, ______________, ______________, ______________, ______________,

        // Thumb cluster
        ______________, ______________,
        ______________,
        ______________, ______________, ______________

        //}}}

    ),

    //}}}

    // User Interface {{{

    [UI] = LAYOUT_ergodox(

        // Left Hand {{{

        ______________, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,
        ______________, XXXXXXXXXXXXXX, KC_MS_BTN2,     KC_MS_UP,       KC_MS_BTN1,     KC_MS_WH_UP,    ______________,
        ______________, XXXXXXXXXXXXXX, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_WH_DOWN,
        ______________, XXXXXXXXXXXXXX, XXXXXXXXXXXXXX, KC_MS_WH_LEFT,  KC_MS_WH_RIGHT, KC_MS_BTN3,     ______________,
        TO(HUB),        ______________, ______________, ______________, ______________,

        // Thumb cluster
                        ______________, ______________,
                                        ______________,
        ______________, ______________, ___CRITICAL___,

        //}}}

        // Right Hand {{{

        KC_F7,               KC_F8,               KC_F9,               KC_F10,              KC_F11,              KC_F12,              ______________,
        XXXXXXXXXXXXXX,      KC_MS_WH_UP,         KC_MS_LEFT,          KC_MS_DOWN,          KC_MS_UP,            KC_MS_RIGHT,         ______________,
                             KC_MS_WH_DOWN,       KC_MS_BTN1,          KC_MS_BTN2,          KC_MS_BTN3,          XXXXXXXXXXXXXX,      KC_LSHIFT,
        XXXXXXXXXXXXXX,      KC_AUDIO_MUTE,       KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,     KC_MEDIA_NEXT_TRACK, ______________,
                                                  RGB_TOG,             RGB_MODE_REVERSE,    RGB_MODE_FORWARD,    XXXXXXXXXXXXXX,      ______________,

        // Thumb cluster
        ______________, ______________,
        ______________,
        ___CRITICAL___, ______________, KC_MS_BTN1

        //}}}

    ),

    //}}}

};

//}}}

// Keyboard Functions {{{

void matrix_scan_user(void)
{
    #if (SLEEP_TIME != 0) && defined(SCAGLE_SLEEP_ENABLE)
    update_idle();
    #endif  // (SLEEP_TIME != 0) && defined(SCAGLE_SLEEP_ENABLE)
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    #if defined(SCAGLE_SLEEP_ENABLE)
    caffeinate_idle();  // Gotta make sure we don't fall asleep :)
    #endif  // defined(SCAGLE_SLEEP_ENABLE)

    switch (keycode)
    {
        case CKC_SHOW_VERSION:  // Print out the version/branch/date of compilation upon keypress

            if (record->event.pressed)
            {
                // IE: "ergodox_ez/scagle @ master Wed Feb  3 01:00:00 AM PST 2021 Features: [rgb_light, tap_dance,]"
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " KEYMAP_BRANCH " " KEYMAP_DATE " Features: [" ENABLED_FEATURES "]");
            }

            return false;

        case CKC_DOCS:  // Output URL to this file in github for easy viewing of keyboard layout (SINCE I FORGET ALL THE TIME!)

            if (record->event.pressed)
            {
                SEND_STRING("https://github.com/scagle/keymaps/blob/master/keyboards/ergodox_ez/keymap.c");
            }

            return false;

        case TRI_LEFT:

            if (record->event.pressed)
            {
                layer_on(SYMBOLS);
            }
            else
            {
                layer_off(SYMBOLS);
            }
            update_tri_layer(SYMBOLS, NUMPAD, UI);

            return false;

        case TRI_RIGHT:

            if (record->event.pressed)
            {
                layer_on(NUMPAD);
            }
            else
            {
                layer_off(NUMPAD);
            }
            update_tri_layer(SYMBOLS, NUMPAD, UI);

            return false;

        // Spongebob Mock Logic: {{{
        // Credit: https://www.reddit.com/r/olkb/comments/ja4c4q/qmk_how_do_i_use_process_record_user_to_change_an/
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⢯⡙⠳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡁⠀⠀⠀⠙⣆⠹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣇⠀⣀⠀⠀⠘⣦⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡄⠸⣇⡀⠀⠘⢧⡹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣄⠙⣇⠀⡀⠈⠳⡽⣆⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⠀⣀⣀⣀⣀⣀⠀⣀⣠⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠖⠲⣦⣤⣿⣶⠻⠗⠃⠀⠀⢹⣾⡟⠲⣶⣖⣞⠋⠉⠉⠛⠒⣻⣿⣷⣦⡉⠙⠛⠉⣠⠞⠛⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⢀⣀⣴⡾⠁⠘⣿⣿⣿⣿⣿⣿⣄⡀⣀⣠⣾⣿⣷⡄⠙⣿⣿⣷⣤⣤⣄⡀⠈⠙⠛⠛⠁⠀⣠⠞⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⣀⣴⠟⠁⠀⠀⠀⠀⢸⣿⣿⣦⠀⠀⣸⣿⡿⠟⠛⢹⣿⠃⠐⢿⣿⣿⣿⣿⣿⠟⠀⠀⠀⠀⣠⠼⠃⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⣴⡿⠿⢦⣀⣀⡤⠶⠷⠶⠬⣉⡉⣹⡶⠟⠋⠁⠀⢀⣴⣿⠏⠠⢤⣠⣤⠾⠟⠛⡶⠤⠤⠤⠴⠾⡅⠀⠀⢀⣴⣶⣦⠘⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠂⠹⣧⡀⣶⣶⣶⡆⠀⠀⠀⠀⠀⠀⢿⣷⣤⣤⣴⣶⣿⠿⠋⠀⠀⠀⠀⠀⣀⣤⠾⢿⣷⣀⡀⠀⠀⣿⠀⢠⣿⣿⣿⣿⡇⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀
        //  ⠀⠀⠈⢹⣿⡭⠙⣿⠀⢠⡀⠀⠀⠀⠀⠉⠙⠛⠋⠉⠁⠀⠀⠀⠀⠀⡴⠛⠉⣷⡀⢠⣧⠈⠙⠂⠀⣿⠀⠸⣿⣿⣿⣿⠃⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠛⢻⡇⠀⠀⠀⠀
        //  ⠀⠀⢠⡾⣿⣴⠾⠛⠓⠛⠿⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡶⠚⠛⠛⠛⠛⠲⣤⡀⠀⢻⡄⠀⠘⠛⠛⠁⠀⠀⠳⣄⠀⠀⠀⢀⣀⡀⣀⡴⠛⣵⠀⣸⡇⠀⠀⠀⠀
        //  ⠀⠀⢻⡿⣫⣤⣤⣄⡀⠀⠀⠀⢻⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠁⠀⠀⠀⠀⣤⣤⣤⠈⢿⠀⠀⠙⢦⠀⠀⢠⣴⣿⣇⠀⢹⣆⣠⠟⠉⠀⠉⠻⣤⠟⣽⠀⣿⠀⣠⣤⣀⠀
        //  ⠀⠀⢸⡃⣿⣿⣷⢌⡷⠀⠀⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⢾⣿⣿⣮⣷⣼⠀⠀⠀⠸⡇⠀⠀⠸⡿⠃⠀⢸⣿⠁⠀⠀⠀⠀⠀⣿⠀⡿⠀⣿⣸⣿⢏⣿⡦
        //  ⠀⠀⠘⢧⡙⠻⠿⠛⠁⠀⠀⢀⡾⠁⣀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠘⢧⡀⠀⠀⠀⠈⠻⣿⣿⣯⠟⠀⠀⠀⠀⡇⠀⠀⠀⠀⢀⣠⣾⠁⠀⠀⠀⠀⢀⣤⠋⢀⡇⢀⣿⣿⡟⣼⢁⣿
        //  ⠀⠀⠀⠈⠹⢦⣄⣀⣀⡤⠶⠋⣀⡴⠋⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣶⠶⠶⠶⢛⣉⣥⠆⠀⠀⢀⠀⠹⣄⠀⠀⢠⣾⣿⡇⠀⠀⢀⣀⣶⣿⣷⣶⣿⡇⠸⣋⡤⠘⠃⣼⠇
        //  ⠀⠀⠀⠀⠀⠀⠙⢻⣏⣀⣴⠞⠋⠀⢠⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠓⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠈⢳⡀⢸⣿⣿⣿⡶⠒⠛⠛⢿⣿⣿⣿⣿⣧⠀⠟⠁⣠⣾⠁⠀
        //  ⠀⠀⠀⠀⠀⠀⣴⠟⠋⠁⠀⠀⠀⣠⠟⠀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠈⠻⠿⠋⠀⠀⣤⣄⠀⢹⠏⠀⠸⣿⣿⣶⣿⣿⣿⡆⠀
        //  ⠀⠀⠀⠀⠀⠀⠻⣇⣀⣀⣠⣤⠞⠁⠀⠘⠛⠀⠀⠀⠀⠀⢀⣤⣴⣶⣿⣿⣿⣿⣶⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠦⣄⠀⠀⠀⠘⣿⣿⠀⠸⣆⠀⠀⢿⣿⣿⣿⣿⣿⣿⡆
        //  ⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⡿⠁⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⡿⠿⠟⠛⠋⠉⣀⠀⠀⠀⣠⣴⣶⣶⣶⣦⣤⠀⠀⠈⢧⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠘⣿⣿⣿⣿⡿⠿⠉
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀⢀⣴⢿⣿⡿⠟⠋⠉⣁⣀⣠⡤⠶⠶⠛⠉⠀⠀⠀⠻⠿⠿⠿⠿⠟⠋⢀⡀⠀⠘⢧⣠⣀⡀⠀⠀⠀⣿⠀⠀⠀⣿⡿⠛⠉⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⣰⢿⡿⠛⢉⣲⣶⣶⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡿⠀⠀⠀⠈⠹⠶⡶⢶⡘⣦⡴⠖⠋⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⠀⠀⠀⣰⠇⠈⠛⠛⠉⠁⠀⠈⠙⠓⣶⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⣀⣠⣤⣤⣤⣶⣾⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢷⡀⢠⠏⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⠟⠉⠙⠛⠛⠛⠛⠛⠛⠋⠉⠉⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⠟⢋⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⡏⢹⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣞⢁⣾⣟⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡎⢀⣿⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⡛⠦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣇⣸⣷⣦⣀⣀⣠⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣷⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣿⣀⠉⢻⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⠿⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        //  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠻⠿⠿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        case KC_A ... KC_Z:  // Hijack keys to follow alternating upper case pattern if toggled

            if (alt_case_toggle && record->event.pressed) {
                if (alt_case_shift) {
                    tap_code16(S(keycode));
                    alt_case_shift = !alt_case_shift;
                    return false;
                } else {
                    alt_case_shift = !alt_case_shift;
                }
            }
            return true;

        case ALTCASE:  // Toggle Spongebob Mock

            if (record->event.pressed) {
                if (alt_case_toggle) {
                    alt_case_shift = false;
                }
                alt_case_toggle = !alt_case_toggle;
            }
            return false;
        // }}}

    }

    return true;  // handle it as raw input character instead of custom character
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    const uint8_t layer __attribute__((unused)) = biton32(state);

    #if defined(SCAGLE_LEDS_ENABLE)
    update_leds(layer);
    #endif  // defined(SCAGLE_LEDS_ENABLE)

    #if defined(COMBO_ENABLE)
    update_combo(layer);
    #endif  // defined(COMBO_ENABLE)

    #if defined(RGBLIGHT_ENABLE)
    update_rgb(layer);
    #endif  // defined(RGBLIGHT_ENABLE)

    return state;
};

// Called once keyboard is powered up and initialized.
void keyboard_post_init_user(void)
{
    // Customise these values to desired behaviour
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;

    transition(WAKEUP_FROM_POWER);
}

// Called when PC is suspending or sleeping.
void suspend_power_down_user(void)
{
    transition(SLEEP_FROM_HOST);
}

// Called when PC is waking up from suspension or sleep
void suspend_wakeup_init_user(void)
{
    transition(WAKEUP_FROM_HOST);
}

//}}}
