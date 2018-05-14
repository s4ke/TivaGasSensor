#ifndef __STATE_H__
#define __STATE_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grlib/grlib.h"

#include "stdtypes.h"
#include "gassensor.h"
#include "watchdog.h"

/**
 * main struct to store the current state of the program in.
 * Has values/pointers to all the relevant information in this program
 */
typedef struct {
	/**
	 * pointer to the sensor data object on the heap.
	 */
	_sensor_data_t* sensor_data;
	/**
	 * the graphics context
	 */
	tContext context;
	/**
	 * which screen should we display. used by the display module
	 * defined by display.h to determine what do render on the LCD
	 */
	_uint32_t screen;
} _state_t;

/**
 * build a default_state object with all the values set to sensible
 * defaults and all the pointers populated with default objects
 */
_state_t* state_default(void);

/**
 * destroys/deletes all memory associated with the given _state_t.
 * cleans up if necessary.
 */
void state_free(_state_t* state);

#endif
