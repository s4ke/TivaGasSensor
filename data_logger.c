#include "data_logger.h"

#include <stdio.h>
#include <string.h>

#include "stdtypes.h"
#include "uart_io.h"

void data_logger_log_data(_sensor_data_t* sensor_data) {
	char buffer[32];
	sprintf(buffer, "raw_val = %d\n\r", sensor_data->raw_val);
	_uint32_t len = strlen(buffer);
	uart_io_send((_uint8_t*) buffer, len);
}
