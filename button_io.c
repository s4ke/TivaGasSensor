#include "button_io.h"
#include "driverlib/gpio.h"
#include "drivers/buttons.h"
#include "display.h"
#include "stdtypes.h"

// 00010100
// &
// 00010000
// =
// 00010000


// 00000100
// &
// 00010000
// =
// 00000000

void button_io_handle(_state_t* state) {
	//
	// Poll for the select button pressed
	//
	_uint8_t buttons_changed;
	_uint8_t buttons_state = ButtonsPoll(&buttons_changed, 0);

	_bool_t changed = false;

	if(buttons_state & UP_BUTTON && buttons_changed & UP_BUTTON) {
		state->screen = state->screen + 1;
		if(state->screen > LAST_DISPLAY) {
			state->screen = FIRST_DISPLAY;
		}
		changed = true;
	}

	if(buttons_state & DOWN_BUTTON && buttons_changed & DOWN_BUTTON) {
		state->screen = state->screen - 1;
		if(state->screen < FIRST_DISPLAY) {
			state->screen = LAST_DISPLAY;
		}
		changed = true;
	}

	if(buttons_state & SELECT_BUTTON && buttons_changed & SELECT_BUTTON) {
		state->sensor_data->cur_val = 0.0f;
		state->sensor_data->min_val = 0.0f;
		state->sensor_data->max_val = 0.0f;
		changed = true;
	}

	if(changed) {
		display_render(state);
	}
}


void button_io_init() {
	ButtonsInit();
}
