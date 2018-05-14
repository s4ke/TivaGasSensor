#ifndef __UART_IO_H__
#define __UART_IO_H__

#include "stdtypes.h"

/**
 * initializes UART for communication
 */
void uart_io_init(void);

/**
 * sends the given buffer over UART
 */
void uart_io_send(const _uint8_t* buffer, _uint32_t count);

#endif
