#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "stdtypes.h"

#define WATCHDOG_TIMER_DEAD 5

typedef struct {
	/**
	 * the timer the watchdog increments
	 * everytime it is called
	 * see watchdog_ping for more info
	 */
	_uint32_t _timer;
	/**
	 * determines whether the watchdog should
	 * force a reset even if the timer has
	 * not run out
	 */
	_bool_t _reset;
} _watchdog_info_t;

extern volatile _watchdog_info_t _watchdog_info;

/**
 * forces a reset even if the timer has not run out
 */
inline void watchdog_force_reset(void) {
	_watchdog_info._reset = true;
}

/**
 * pings the watchdog so that it knows
 * the program is still running
 *
 * this is called in the function that reads
 * the current gas sensor value.
 *
 * if the watchdog wakes up > WATCHDOG_TIMER_DEAD times
 * the program is assumed dead and is restarted
 *
 * we don't call this in the main loop as a user would usually
 * see that the buttons do not work and would therefore be able
 * to press the reset button him/herself
 */
inline void watchdog_ping(void) {
	_watchdog_info._timer = 0;
}

/**
 * initializes the watchdog
 */
void watchdog_init(void);


#endif
