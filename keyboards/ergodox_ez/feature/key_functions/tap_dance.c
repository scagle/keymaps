// vim: foldmethod=marker

#include "globals.h"

#include "feature/key_functions/tap_dance.h"
#include "feature/key_functions/key_swap.h"
#include "feature/ui_functions/rgb_light.h"

enum
{
    NO_SPONGE_MOCK = 0,
    SPONGE_MOCK = 1,
    SPONGE_MOCK_LEET = 2,
} spongemock_state_t;

uint8_t sponge_mock_state = NO_SPONGE_MOCK;
uint8_t sponge_mock_case = 0;

static void sponge_mock_finish(qk_tap_dance_state_t *state, void *user_data);
static void copy_paste_cut_finish(qk_tap_dance_state_t *state, void *user_data);
#if defined(SCAGLE_KEY_SWAP_ENABLE)
static void swap_os_finish(qk_tap_dance_state_t *state, void *user_data);
#endif

// Action Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SPONGE_MOCK] = ACTION_TAP_DANCE_FN(sponge_mock_finish),
    [TD_C_P_X] = ACTION_TAP_DANCE_FN(copy_paste_cut_finish),
#if defined(SCAGLE_KEY_SWAP_ENABLE)
    [TD_SWAP_OS] = ACTION_TAP_DANCE_FN(swap_os_finish),
#endif  // defined(SCAGLE_KEY_SWAP_ENABLE)
};

// Function Implementations {{{

// Spongebob Mock Modifier: {{{
// CrEaTeS aLtErNaTiNg CaSeS iN aLl KeYsTrOkEs SeNt
//   - 1 Tap  = Disable
//   - 2 Taps = SpOnGeBoB MoCk SiMpLe
//   - 3 Taps = (TODO): Sp0n6eBoB M0Ck L3Et Sp3@K
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
static void sponge_mock_finish(qk_tap_dance_state_t *state, void *user_data)
{
    sponge_mock_case = 0;
    switch (state->count)
    {
        case NO_SPONGE_MOCK: sponge_mock_state = NO_SPONGE_MOCK; break;
        case SPONGE_MOCK: sponge_mock_state = SPONGE_MOCK; break;
        default: sponge_mock_state = NO_SPONGE_MOCK;  // TODO: change to SPONGE_MOCK_LEET when implemented
    }
}

// Called from main loop
bool apply_sponge_mock(uint16_t keycode)
{
    if (sponge_mock_state == SPONGE_MOCK)
    {
        uint16_t lowercase_keycode = keycode & ~0x20;  // clear bit 5 to make it lower case
        if ((lowercase_keycode >= 65) && (lowercase_keycode <= 90))
        {
            tap_code16(lowercase_keycode | (sponge_mock_case << 5));  // set bit 5 to whatever case we're on
            return false;
        }
    }
    return true;
}

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
