#ifndef _SCAGLE_COMBO_H_
#define _SCAGLE_COMBO_H_
#pragma once

#if defined(COMBO_ENABLE)

enum combos {
    CO_QWERTY_ART,
};


void update_combo(const uint8_t layer);

#endif  // defined(COMBO_ENABLE)

#endif  // #ifndef _SCAGLE_COMBO_H_
