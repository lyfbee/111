/*
 * UART.h
 *
 *  Created on: 2021年7月26日
 *      Author: Mr.Xue
 */

#ifndef UART_H_
#define UART_H_

#include "msp430.h"
#include "stdint.h"

void UARTSendString(int num);
void InitUART(void);

#endif /* UART_H_ */

