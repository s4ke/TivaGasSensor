#include "util.h"

_float_t toADCVoltage(_uint32_t addCode) {
		return addCode * addCodeMult;
}
