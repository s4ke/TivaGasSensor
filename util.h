#ifndef __UTIL_H__
#define __UTIL_H__

#include "stdtypes.h"

// some utils...
#define MIN(a,b) (((a)<(b)) ? (a) : (b))
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

// magic number as determined by the Tiva board documentation
#define addCodeMult 0.7326f;

/**
 * converts the read add_code from the sensor
 * into a adc voltage. See the documentation for
 * the Tiva board
 */
inline _float_t util_to_adc_voltage(_uint32_t add_code) {
	return add_code * addCodeMult;
}

#endif
