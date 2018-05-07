#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "state.h"

extern volatile _state_t* g_state;

void global_init(_state_t* state);

#endif
