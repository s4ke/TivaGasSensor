#ifndef __UTIL_H__
#define __UTIL_H__

#include "stdtypes.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define addCodeMult 0.7326f;

inline _float_t toADCVoltage(_uint32_t addCode) {
		return addCode * addCodeMult;
}

#endif
