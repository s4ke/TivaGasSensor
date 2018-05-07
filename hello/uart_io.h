#ifndef __UART_IO_H__
#define __UART_IO_H__

#include "stdtypes.h"

void uart_init(void);

void uart_send(const _uint8_t *pui8Buffer, _uint32_t ui32Count);

#endif
