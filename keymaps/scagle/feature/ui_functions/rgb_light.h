#ifndef _SCAGLE_RGB_LIGHT_H_
#define _SCAGLE_RGB_LIGHT_H_
#pragma once

#if defined(RGBLIGHT_ENABLE)

#include QMK_KEYBOARD_H

void update_rgb(uint8_t layer);

#if defined(SCAGLE_RGBLIGHT_ANIMATIONS)

void flash_rgb(uint8_t hue, uint8_t sat, uint8_t val);

#endif  // defined(SCAGLE_RGBLIGHT_ANIMATIONS)

#endif  // defined(RGBLIGHT_ENABLE)

#endif  // #ifndef _SCAGLE_RGB_LIGHT_H_
