#include "gassensor.h"

#include "util.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

void read_data(_sensor_data_t* sensor_data) {
			_uint32_t rawVal[1];
	
			// Trigger the ADC conversion.
			ADCProcessorTrigger(ADC0_BASE, 3);

			// Wait for conversion to be completed.
			while(!ADCIntStatus(ADC0_BASE, 3, false))
			{
			}

			// Clear the ADC interrupt flag.
			ADCIntClear(ADC0_BASE, 3);

			// Read ADC Value.
			ADCSequenceDataGet(ADC0_BASE, 3, rawVal);
			
			sensor_data->rawVal = rawVal[0];
			sensor_data->curVal = (_float_t) rawVal[0];
			sensor_data->maxVal = MAX(sensor_data->maxVal, sensor_data->curVal);
			sensor_data->minVal = MIN(sensor_data->minVal, sensor_data->curVal);
}
