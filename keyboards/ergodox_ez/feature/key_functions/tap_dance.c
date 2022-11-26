// vim: foldmethod=marker


#include "globals.h"

#include "feature/key_functions/tap_dance.h"
#include "feature/key_functions/key_swap.h"
#include "feature/ui_functions/rgb_light.h"

static void copy_paste_cut_finish(qk_tap_dance_state_t *state, void *user_data);
#if defined(SCAGLE_KEY_SWAP_ENABLE)
static void swap_os_finish(qk_tap_dance_state_t *state, void *user_data);
#endif

// Action Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_C_P_X] = ACTION_TAP_DANCE_FN(copy_paste_cut_finish),
#if defined(SCAGLE_KEY_SWAP_ENABLE)
    [TD_SWAP_OS] = ACTION_TAP_DANCE_FN(swap_os_finish),
#endif  // defined(SCAGLE_KEY_SWAP_ENABLE)
};

// Function Implementations {{{

// Copy Paste Cut: {{{
//   - 1 Tap  = Copy
//   - 2 Taps = Paste
//   - 3 Taps = Cut
static void copy_paste_cut_finish(qk_tap_dance_state_t *state, void *user_data)
{
    switch (state->count)
    {
        case 1:  tap_code16(KS_COPY); break;
        case 2:  tap_code16(KS_PASTE); break;
        default: tap_code16(KS_CUT);
    }
}

// }}} Copy Paste Cut

// Operating System Modifier Swap: {{{
//   - 1 Tap  = Red  Flashes = use Linux (and Windows) modifiers for certain operations
//   - 2 Taps = Blue Flashes = use MacOS modifiers for certain operations

#if defined(SCAGLE_KEY_SWAP_ENABLE)

static void swap_os_finish(qk_tap_dance_state_t *state, void *user_data)
{
    switch (state->count)
    {
        case 1:
        {
            KS_COPY  = KC_PC_COPY;
            KS_PASTE = KC_PC_PASTE;
            KS_CUT   = KC_PC_CUT;

            #if defined(RGBLIGHT_ENABLE) && defined(SCAGLE_RGBLIGHT_ANIMATIONS)
            flash_rgb(HSV_RED);
            #endif  // defined(RGBLIGHT_ENABLE) && defined(SCAGLE_RGBLIGHT_ANIMATIONS)

            break;
        }
        default:
        {
            KS_COPY  = KC_MAC_COPY;
            KS_PASTE = KC_MAC_PASTE;
            KS_CUT   = KC_MAC_CUT;

            #if defined(RGBLIGHT_ENABLE) && defined(SCAGLE_RGBLIGHT_ANIMATIONS)
            flash_rgb(HSV_BLUE);
            #endif  // defined(RGBLIGHT_ENABLE) && defined(SCAGLE_RGBLIGHT_ANIMATIONS)
        }
    }
}

#endif  // defined(SCAGLE_KEY_SWAP_ENABLE)

// }}} OS Modifier Swap

// }}} Function Implementations
