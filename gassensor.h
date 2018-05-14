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
	_float_t max_val;
	/**
	 * the minimum float value read in the gas sensor
	 * as of the current time
	 */
	_float_t min_val;
	/**
	 * the current float value read in the gas sensor
	 * at	this time
	 */
	_float_t cur_val;
	/**
	 * the current raw value read in the gas sensor
	 * at this time
	 */
	_uint32_t raw_val;
} _sensor_data_t;

/**
 * read the current readings from the gas sensor into the
 * passed sensor_data struct
 */
void gassensor_read_data(_sensor_data_t* sensor_data);

void gassensor_init(void);

#endif
