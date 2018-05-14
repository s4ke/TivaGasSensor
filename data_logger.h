#ifndef __DATA_LOGGER_H__
#define __DATA_LOGGER_H__

#include "gassensor.h"

/**
 * logs the given sensor_data
 *
 * (currently only logging to UART)
 *
 * TODO: log to SD Card
 */
void data_logger_log_data(_sensor_data_t* sensor_data);

#endif
