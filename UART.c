/*
 * UART.c
 *
 *  Created on: 2021年7月26日
 *      Author: Mr.Xue
 */

#include "UART.h"
void InitUART(void)
{
    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;

    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*配置波特率为9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*使能端口复用*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;
}

/*
 * @fn:     void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:  通过串口发送字符串
 * @para:   pbuff:指向要发送字符串的指针
 *          num:要发送的字符个数
 * @return: none
 * @comment:通过串口发送字符串
 */
void UARTSendString(int num)
{
    while(UCA0STAT & UCBUSY);
    UCA0TXBUF = num;
}
