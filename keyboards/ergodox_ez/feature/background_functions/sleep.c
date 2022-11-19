//// Sleep Module
//
// Track sleep time using a single byte:
//     bits  type  description
//     --------------------------
//     [0:6] [int] How long to wait before going into sleep mode
//     [7]   [bool] Current sleep state (sleeping/not sleeping)

#include "feature/background_functions/sleep.h"

#include "globals.h"

#include "include/background_functions/transitions.h"

#define SLEEP_BIT  0x80
#define SLEEP_TIME_HALF_MINUTES (SLEEP_TIME * 2)
#if (SLEEP_TIME_HALF_MINUTES & SLEEP_BIT)
    #error "SLEEP_TIME has to be [0-63] [0x0 - 0x3F]!"
#endif

static uint16_t last_key_stroke_in_ms;  // [15:0] millisecond counter
static uint8_t  last_key_stroke_in_half_minute;  //  [6:0] half_minute (30 sec) counter + [7] sleep state bit

void wakeup_idle()
{
    transition(WAKEUP_FROM_IDLE);
    last_key_stroke_in_ms = timer_read();
    last_key_stroke_in_half_minute = 0;
}

void sleep_idle()
{
    transition(SLEEP_FROM_IDLE);
    last_key_stroke_in_half_minute |= SLEEP_BIT;
}

void caffeinate_idle()
{
    if (last_key_stroke_in_half_minute & SLEEP_BIT)
    {
        wakeup_idle();

    } else {

        last_key_stroke_in_ms = timer_read();
    }
}

void update_idle()
{
    if (last_key_stroke_in_half_minute & SLEEP_BIT) return;

    if (last_key_stroke_in_half_minute >= SLEEP_TIME_HALF_MINUTES)
    {
        sleep_idle();
        return;
    }

    // If 30 seconds has elapsed since last key press
    if (timer_elapsed(last_key_stroke_in_ms) > 30000)
    {
        last_key_stroke_in_half_minute++;
        last_key_stroke_in_ms = timer_read();
    }
}
