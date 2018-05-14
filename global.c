#include "global.h"

volatile _state_t* g_state;

void global_init(_state_t* state) {
	g_state = state;
}
