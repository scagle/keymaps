#ifndef _SCAGLE_TAP_DANCE_H_
#define _SCAGLE_TAP_DANCE_H_
#pragma once

#if defined(TAP_DANCE_ENABLE)

enum tap_dance_keys {
    TD_C_P_X,  // Copy, Paste, Cut
    TD_SWAP_OS,  // Swap Linux, MacOS keys (IE: command vs ctrl)
};

#endif  // defined(TAP_DANCE_ENABLE)

#endif  // #ifndef _SCAGLE_TAP_DANCE_H_
