#ifndef __H_Bridge_Control_H
#define __H_Bridge_Control_H

#include "gd32f10x_timer.h"

//电机编号
#define M1 1
#define M2 2
#define M3 3
#define M4 4


//H桥AB相宏定义
#define M1_2TIME TIMER2 //电机1和电机2的定时器
#define M1_A TIMER_CH_2
#define M1_B TIMER_CH_0

#define M2_A TIMER_CH_3
#define M2_B TIMER_CH_1

#define M3_4TIME TIMER3
#define M3_A TIMER_CH_2
#define M3_B TIMER_CH_0

#define M4_A TIMER_CH_3
#define M4_B TIMER_CH_1

//H桥驱动初始化
void H_Bridge_Init(void);
//设置电机转速
uint8_t Set_Motor_Speed(uint16_t Motor,float Speed);






#endif


