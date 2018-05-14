#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "state.h"

#define DISPLAY_SCREEN 1
#define DISPLAY_PPM_SCREEN 2
#define DISPLAY_PCT_SCREEN 3
#define FIRST_DISPLAY DISPLAY_SCREEN
#define LAST_DISPLAY DISPLAY_PCT_SCREEN


/**
 * displays the _state_t on the LCD of the Tiva board.
 * the "screen" value in the passed _state_t determines
 * what exactly is rendered
 */
void display_render(_state_t* state);

void display_init(_state_t* state);

#endif
