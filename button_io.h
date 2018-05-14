#ifndef __BUTTON_IO_H__
#define __BUTTON_IO_H__

#include "state.h"

/**
 * initializes the buttons for usage
 */
void button_io_init(void);

/**
 * handles the button logic and changes the state
 * accordingly
 */
void button_io_handle(_state_t* state);

#endif
