#include "state.h"

_state_t* default_state() {
	_state_t* state;
	_sensor_data_t* sensor_data;
	bool err = true;
	
	state = (_state_t*) (malloc(sizeof(_state_t)));
	if(state) {
		sensor_data = (_sensor_data_t*) malloc(sizeof(_sensor_data_t));
		if(!sensor_data) {
			err = true;
		} else {
			state->sensor_data = sensor_data;
			err = false;
		}
	}
	
	if(err) {
		if(state) {
			free(state);
		}
		if(sensor_data) {
			free(sensor_data);
		}
		state = NULL;
	}
	
	return state;
}

void free_state(_state_t* state) {
	if(state) {
		if(state->sensor_data) {
			free(state->sensor_data);
		}
		free(state);
	}
}
