#ifndef __GASSENSOR_H__
#define __GASSENSOR_H__

#include "stdtypes.h"

/**
 * struct to store the sensor data in. We only use
 * single precision floats to represent the sensor
 * values as we only read uint32_t raw values
 */
typedef struct {
	/**
	 * the maximum float value read in the gas sensor
	 * as of the current time
	 */
	_float_t maxVal;
	/**
	 * the minimum float value read in the gas sensor
	 * as of the current time
	 */
	_float_t minVal;
	/**
	 * the current float value read in the gas sensor
   * at	this time
	 */
	_float_t curVal;
	
	_uint32_t rawVal;
} _sensor_data_t;

void read_data(_sensor_data_t* state);

#endif
