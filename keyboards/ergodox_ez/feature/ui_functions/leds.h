#ifndef _SCAGLE_LEDS_H_
#define _SCAGLE_LEDS_H_
#pragma once

#if defined(SCAGLE_LEDS_ENABLE)

void update_leds(uint8_t layer);
void set_led_enabled(uint8_t enable);

#endif  // defined(SCAGLE_LEDS_ENABLE)

#endif  // #ifndef _SCAGLE_LEDS_H_
