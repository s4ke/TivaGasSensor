#include "conversion.h"

#include <math.h>

#include "util.h"

_float_t conversion_voltage_to_ppm(_float_t voltage) {
	return voltage;
}

_float_t conversion_voltage_to_pct(_float_t voltage) {
	_float_t result = 0;
	if(voltage < 350) {
		_float_t m = 0.11525f;
		_float_t C = -35.40378f;
		result = m * voltage + C;
	} else if (voltage < 668) {
		_float_t a = 0.52556f;
		_float_t b = 0.00630f;
		result = a * exp(b * voltage);
	} else {
		result = 100;
	}
	return MAX(result, 0.0f);
	// Gerade:_float_t pct = (_float_t) ((((_double_t) voltage) - 313.533) / 8.03);
	//
	//_float_t A = 0.362f;
	//_float_t B = 0.79f;
	//_float_t C = 343.7f;
	//_float_t eps = 15.7f;
	//_float_t pct = (_float_t) ((-B + sqrt(A*A - (B*B) * (C - (_double_t) voltage) + eps)) / 2*A);
	//return MAX(pct, 0.0f);
}
