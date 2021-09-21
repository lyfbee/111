#ifndef __Houle_Velocity_H
#define __Houle_Velocity_H

#include "gd32f10x.h"
#include "gd32f10x_gpio.h"
#include "System_time.h"
#include "My_Math.h"
//#include "H_Bridge_Control.h"


#define Houle_Pluse 7                    //霍尔一圈脉冲数
#define Decelerate_Ratio 50						 //电机减速比
#define Whell_Radius 2.2                 //车轮半径cm
#define Motor_Factor 2*Pi_Radian*Whell_Radius/(Decelerate_Ratio*Houle_Pluse)



//测速外部中断宏定义
#define EXTI_IRon_A      EXTI5_9_IRQn

#define M1_A_GPIO_Periph GPIOE
#define M1_A_GPIO_Pin    GPIO_PIN_6

#define M2_A_GPIO_Periph GPIOD
#define M2_A_GPIO_Pin    GPIO_PIN_7

#define M3_A_GPIO_Periph GPIOA
#define M3_A_GPIO_Pin    GPIO_PIN_8

#define M4_A_GPIO_Periph GPIOD
#define M4_A_GPIO_Pin    GPIO_PIN_9

#define EXTI_IRon_B      EXTI10_15_IRQn

#define M1_B_GPIO_Periph GPIOA
#define M1_B_GPIO_Pin    GPIO_PIN_11

#define M2_B_GPIO_Periph GPIOA
#define M2_B_GPIO_Pin    GPIO_PIN_12

#define M3_B_GPIO_Periph GPIOB
#define M3_B_GPIO_Pin    GPIO_PIN_13

#define M4_B_GPIO_Periph GPIOB
#define M4_B_GPIO_Pin    GPIO_PIN_14



typedef struct 
{
	uint8_t M1:1;
	uint8_t M1_Polar:1;
	uint8_t M2:1;
	uint8_t M2_Polar:1;
	uint8_t M3:1;
	uint8_t M3_Polar:1;
	uint8_t M4:1;
	uint8_t M4_Polar:1;
}Measuring_Velocity_Type;//测速标志位结构体

//霍尔测速初始化
void Houle_Velocity_init(void);
//获取电机速度
float Get_Motor_Velocity(uint8_t Motor);

#endif

