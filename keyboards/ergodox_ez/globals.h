// All global constants used across multiple files

#ifndef _SCAGLE_GLOBALS_H_
#define _SCAGLE_GLOBALS_H_
#pragma once

#include QMK_KEYBOARD_H

#define GLOBAL_LAYER_STATE layer_state
#define KC_MAC_UNDO  LGUI(KC_Z)
#define KC_MAC_CUT   LGUI(KC_X)
#define KC_MAC_COPY  LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO   LCTL(KC_Z)
#define KC_PC_CUT    LCTL(KC_X)
#define KC_PC_COPY   LCTL(KC_C)
#define KC_PC_PASTE  LCTL(KC_V)
#define NUM_LEDS     3

#define DISABLED 0
#define ENABLED  1

enum mapped_key_codes {

    // Layer Mappings
    ______________ = _______,  // Transparent Key (Uses key from lower layer)
    XXXXXXXXXXXXXX = XXXXXXX,  // NoOp Block Key (Does nothing + Blocks keys on layers beneath)
    ___CRITICAL___ = _______,  // Transparent Key (Key beneath this one is critically important)

    // TODO: Make these mappings dynamic and loadable, for multiple programs?
    // TODO: Make this a macro instead of static key
    CYCLE_APP_LAYOUT = _______,   // Reserved for potential implementation in future

    TRI_LEFT,   // Tri-Layer transition, AKA: LOWER
    TRI_RIGHT,  // Tri-Layer transition, AKA: UPPER
};

enum custom_key_codes {
    CKC_SHOW_VERSION = EZ_SAFE_RANGE,   // Type out version/compilation info
    CKC_DOCS,                           // Type out URL to keymaps.c file for easy reference
    ALTCASE,                            // ToGgLe SpOnGeBoB mOcK tExT oUtPuT
};

// Alias enums for layers
// Must start at zero:
// https://docs.qmk.fm/#/configurator_default_keymaps?id=layer-references
enum layers {
    HUB = 0, // QWERTY Layer
    QWERTY,  // QWERTY Layer
    SYMBOLS, // Symbols Layer
    NUMPAD,  // Numpad layer
    EXTRA,   // Misc Layer (IE: Function Keys, Numpad)
    UI,      // User Interface Layer (IE: Mouse functions, RGB, Media, EEPROM Flash)
};

#endif // #ifndef _SCAGLE_GLOBALS_H_
