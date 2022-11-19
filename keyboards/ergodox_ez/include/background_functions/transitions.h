#ifndef _SCAGLE_TRANSITIONS_H_
#define _SCAGLE_TRANSITIONS_H_
#pragma once

typedef enum transitions {

    WAKEUP_FROM_POWER,  // Keyboard initiated, after power-on + initialization.
    WAKEUP_FROM_HOST,   // Host initiated, after waking up from sleep or suspension.
    SLEEP_FROM_HOST,    // Host initiated, before sleeping or suspending.

    // Sleep Feature
    WAKEUP_FROM_IDLE,   // FW initiated, when waking up after being idle.
    SLEEP_FROM_IDLE,    // FW initiated, when idle for too long.

} transition_t;


void transition(transition_t state);

#endif  // #ifndef _SCAGLE_TRANSITIONS_H_
