#include "feature/ui_functions/rgb_light.h"
#include "timer.h"

#define UPDATE_CONSUMED 1
#define UPDATE_NOT_CONSUMED 0

// TODO: Make this more robust, maybe with PROGMEM and switch statements
//       To avoid sizeof checks
const static uint8_t layer_colors[][3] = {
//      Hue , Sat , Val
/*0*/  {0   , 0   , 255},  // Neutral for base layer
/*1*/  {0   , 200 , 255},  // 1 and 2 need highly distinguishable colors
/*2*/  {127 , 255 , 255},
/*3*/  {63  , 200 , 255},  // 3 and 4 need highly distinguishable colors
/*4*/  {190 , 255 , 255},
/*5*/  {225 , 200 , 255},
/*6*/  {225 , 255 , 255},  // SPIZZAZY for the fun UI layer
};

#if defined(SCAGLE_RGBLIGHT_ANIMATIONS)
static uint8_t update_rgb_animation(void);
#endif  // defined(SCAGLE_RGBLIGHT_ANIMATIONS)

void update_rgb(uint8_t layer) 
{
    // Write to Glow LEDs (TODO: Figure out why this needs to be written every time)
    if (rgblight_is_enabled())
    {
        #if defined(SCAGLE_RGBLIGHT_ANIMATIONS)
        if (update_rgb_animation() == UPDATE_CONSUMED)
            return;
        #endif  // defined(SCAGLE_RGBLIGHT_ANIMATIONS)
        
        // Quick check to see if within valid boundaries
        if (layer < sizeof(layer_colors)/sizeof(layer_colors[0])) 
        {
            rgblight_sethsv_noeeprom(layer_colors[layer][0], layer_colors[layer][1], layer_colors[layer][2]);

        } else {

            rgblight_sethsv_noeeprom(0, 0, 0);
        }
    }
}

#if defined(SCAGLE_RGBLIGHT_ANIMATIONS)

void flash_rgb(uint8_t hue, uint8_t sat, uint8_t val) {

}

static uint8_t update_rgb_animation() {
    return UPDATE_NOT_CONSUMED;
}

//TODO: Implement if/when necessary

//static uint8_t counter = 0;
//void begin_startup_rgb_animation() {
//
//}
//
//static void update_startup_rgb_animation() {
//
//}

#endif  // defined(SCAGLE_RGBLIGHT_ANIMATIONS)
