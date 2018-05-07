#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "stdtypes.h"

typedef struct {
	_uint32_t _timer;
	_bool_t _reset;
} _watchdog_info_t;

extern volatile _watchdog_info_t _watchdog_info;

inline void force_reset(void) {
	_watchdog_info._reset = true;
}

inline void ping_watchdog(void) {
	_watchdog_info._timer = 0;
}

void init_watchdog(void);


#endif
