#ifndef _SCAGLE_KEY_SWAP_H_
#define _SCAGLE_KEY_SWAP_H_
#pragma once

#include "globals.h"

#if defined(SCAGLE_KEY_SWAP_ENABLE)

extern uint16_t KS_COPY;
extern uint16_t KS_PASTE;
extern uint16_t KS_CUT;

#else

#define KS_COPY  KC_PC_COPY
#define KS_PASTE KC_PC_PASTE
#define KS_CUT   KC_PC_CUT

#endif  // defined(SCAGLE_KEY_SWAP_ENABLE)

#endif  // #ifndef _SCAGLE_KEY_SWAP_H_
