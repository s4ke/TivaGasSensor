#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "state.h"

/**
 * global state so that we can change the state in interrupts
 */
extern volatile _state_t* g_state;

/**
 * initializes the global variables (currently only the state)
 */
void global_init(_state_t* state);

#endif
