#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include "stdtypes.h"

/**
 * converts the adc voltage reading to ppm
 */
_float_t conversion_voltage_to_ppm(_float_t voltage);

/**
 * converts the adc voltage reading to percent
 */
_float_t conversion_voltage_to_pct(_float_t voltage);


#endif
