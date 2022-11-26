#ifndef _SCAGLE_TAP_DANCE_H_
#define _SCAGLE_TAP_DANCE_H_
#pragma once

#if defined(TAP_DANCE_ENABLE)

extern uint16_t KS_COPY;

enum tap_dance_keys {
    TD_SPONGE_MOCK,  // SpOnGeBoB MoCk Speak
    TD_C_P_X,  // Copy, Paste, Cut
    TD_SWAP_OS,  // Swap Linux, MacOS keys (IE: command vs ctrl)
};

bool apply_sponge_mock(uint16_t keycode);

#endif  // defined(TAP_DANCE_ENABLE)

#endif  // #ifndef _SCAGLE_TAP_DANCE_H_
