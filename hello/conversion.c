#include "conversion.h"

_float_t voltage_to_ppm(_float_t voltage) {
	return voltage;
}

_float_t voltage_to_pct(_float_t voltage) {
	return (voltage - 17.09f) / 370.0f * 10;
}
