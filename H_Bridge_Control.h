#ifndef __H_Bridge_Control_H
#define __H_Bridge_Control_H

#include "gd32f10x_timer.h"

//������
#define M1 1
#define M2 2
#define M3 3
#define M4 4


//H��AB��궨��
#define M1_2TIME TIMER2 //���1�͵��2�Ķ�ʱ��
#define M1_A TIMER_CH_2
#define M1_B TIMER_CH_0

#define M2_A TIMER_CH_3
#define M2_B TIMER_CH_1

#define M3_4TIME TIMER3
#define M3_A TIMER_CH_2
#define M3_B TIMER_CH_0

#define M4_A TIMER_CH_3
#define M4_B TIMER_CH_1

//H��������ʼ��
void H_Bridge_Init(void);
//���õ��ת��
uint8_t Set_Motor_Speed(uint16_t Motor,float Speed);






#endif


