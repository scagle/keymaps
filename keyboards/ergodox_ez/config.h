/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

//#define ORYX_CONFIGURATOR

#define FIRMWARE_VERSION u8"EW99G/EnEyb"

// Times before a "tap" becomes a "hold" (milliseconds)
#undef  TAPPING_TERM    // ergodox_ez keyboard has default of 200
#define TAPPING_TERM 150

// Times before a TT() modifier switches layers (milliseconds)
#undef  TAPPING_TOGGLE  // ergodox_ez keyboard has default of 1
#define TAPPING_TOGGLE 2

#if defined(SCAGLE_SLEEP_ENABLE)

    #define SLEEP_TIME 5  // # of idle minutes before keyboard turns off all lights (must be [0-63])

#endif  // defined(SCAGLE_SLEEP_ENABLE)

#if defined(RGBLIGHT_ENABLE)

//  #undef  RGBLIGHT_SLEEP       
    #define RGBLIGHT_SLEEP       // ~84 bytes, ~0.28%

#endif  // defined(RGBLIGHT_ENABLE)


#if defined(COMBO_ENABLE)

    #define COMBO_COUNT 1  // Must be updated when adding new combo keys. 
                           // TODO: See if this can defined alongside combo definitions, as this location is weird.

#endif  // defined(COMBO_ENABLE)
