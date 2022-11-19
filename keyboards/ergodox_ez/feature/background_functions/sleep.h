#ifndef _SCAGLE_SLEEP_H_
#define _SCAGLE_SLEEP_H_
#pragma once

#if defined(SCAGLE_SLEEP_ENABLE)

void wakeup_idle(void);
void sleep_idle(void);
void caffeinate_idle(void);
void update_idle(void);

#endif  // defined(SCAGLE_SLEEP_ENABLE)

#endif  // #ifndef _SCAGLE_SLEEP_H_
