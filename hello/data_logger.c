#include "data_logger.h"

#include <stdio.h>
#include <string.h>

#include "stdtypes.h"
#include "uart_io.h"

void log_data(_sensor_data_t* sensor_data) {
	char buffer[32];
	sprintf(buffer, "rawVal = %d\n\r", sensor_data->rawVal);
  _uint32_t len = strlen(buffer);
	uart_send((_uint8_t*) buffer, len);
}
