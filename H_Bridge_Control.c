/*****************************************************************
File name:H桥驱动

Author:赵华磊

Version:V0.1

Description:AB相PWM驱动电机正反转

Others:

Log:2021/5/19
*****************************************************************/
#include "H_Bridge_Control.h"

static void H_Bridge_GPIO_Init(void);
static void H_Bridge_Time_PWM_Init(void);
static void RCU_TIME_ENABLE(uint32_t TIME);

/*
*@ Description H桥驱动初始化
*@ param 无参数
*@ return无返回值
*/
void H_Bridge_Init(void)
{
	H_Bridge_GPIO_Init();
	H_Bridge_Time_PWM_Init();
}


/*
*@ Description H桥驱动GPIO初始化
*@ prarm 无参数
*@ return 无返回值
*/
static void H_Bridge_GPIO_Init(void)
{
	rcu_periph_clock_enable(RCU_AF);
	
	gpio_init(GPIOC,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_6);//T2_CH0
	gpio_init(GPIOC,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);//T2_CH1
	gpio_init(GPIOC,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_8);//T2_CH2
	gpio_init(GPIOC,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);//T2_CH3
	
	gpio_init(GPIOD,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_12);//T3_CH0
	gpio_init(GPIOD,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_13);//T3_CH1
	gpio_init(GPIOD,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_14);//T3_CH2
	gpio_init(GPIOD,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_15);//T3_CH3
}
/*
*@ Description H桥驱动定时器PWM初始化
*@ param 无参数
*@ return 无返回值
*/
static void H_Bridge_Time_PWM_Init(void)
{
	RCU_TIME_ENABLE(M1_2TIME);
	RCU_TIME_ENABLE(M3_4TIME);
	timer_parameter_struct timer_initparam;
	timer_oc_parameter_struct timer_ocinitparam;
	
	gpio_pin_remap_config(GPIO_TIMER2_FULL_REMAP,ENABLE);
	gpio_pin_remap_config(GPIO_TIMER3_REMAP,ENABLE);
	
	timer_deinit(M1_2TIME);
	timer_deinit(M3_4TIME);
	
	timer_initparam.prescaler=0;                                  //分频系数
	timer_initparam.alignedmode=TIMER_COUNTER_EDGE;               //边沿对齐
	timer_initparam.counterdirection=TIMER_COUNTER_UP;            //向上计数模式
	timer_initparam.period=5400;                                  //设置周期20kHZ PWM输出
	timer_initparam.clockdivision=TIMER_CKDIV_DIV1;               //时钟分频值
	timer_initparam.repetitioncounter=0;                          //
	
	timer_init(M1_2TIME,&timer_initparam);
	timer_init(M3_4TIME,&timer_initparam);
	
	timer_ocinitparam.outputstate = TIMER_CCX_ENABLE;          //使能比较输出
	timer_ocinitparam.ocpolarity = TIMER_OC_POLARITY_LOW;      //输出极性低
	timer_ocinitparam.ocnidlestate = TIMER_OC_IDLE_STATE_HIGH;   //空闲状态电平
	
	timer_channel_output_config(M1_2TIME,M1_A,&timer_ocinitparam);
	timer_channel_output_config(M1_2TIME,M1_B,&timer_ocinitparam);	
	timer_channel_output_config(M1_2TIME,M2_A,&timer_ocinitparam);	
	timer_channel_output_config(M1_2TIME,M2_B,&timer_ocinitparam);		
	timer_channel_output_config(M3_4TIME,M3_A,&timer_ocinitparam);
	timer_channel_output_config(M3_4TIME,M3_B,&timer_ocinitparam);	
	timer_channel_output_config(M3_4TIME,M4_A,&timer_ocinitparam);	
	timer_channel_output_config(M3_4TIME,M4_B,&timer_ocinitparam);
	
	timer_channel_output_pulse_value_config(M1_2TIME,M1_A,0);//输出占空比0/1600
	timer_channel_output_pulse_value_config(M1_2TIME,M1_B,0);//输出占空比0/1600	
	timer_channel_output_pulse_value_config(M1_2TIME,M2_A,0);//输出占空比0/1600
	timer_channel_output_pulse_value_config(M1_2TIME,M2_B,0);//输出占空比0/1600	
	timer_channel_output_pulse_value_config(M3_4TIME,M3_A,0);//输出占空比0/1600
	timer_channel_output_pulse_value_config(M3_4TIME,M3_B,0);//输出占空比0/1600
	timer_channel_output_pulse_value_config(M3_4TIME,M4_A,0);//输出占空比0/1600
	timer_channel_output_pulse_value_config(M3_4TIME,M4_B,0);//输出占空比100/1600

	timer_channel_output_mode_config(M1_2TIME,M1_A,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M1_2TIME,M1_B,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M1_2TIME,M2_A,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M1_2TIME,M2_B,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M3_4TIME,M3_A,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M3_4TIME,M3_B,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M3_4TIME,M4_A,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(M3_4TIME,M4_B,TIMER_OC_MODE_PWM0);
	
	timer_channel_output_shadow_config(M1_2TIME,M1_A,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M1_2TIME,M1_B,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M1_2TIME,M2_A,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M1_2TIME,M2_B,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M3_4TIME,M3_A,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M3_4TIME,M3_B,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M3_4TIME,M4_A,TIMER_OC_SHADOW_ENABLE);
	timer_channel_output_shadow_config(M3_4TIME,M4_B,TIMER_OC_SHADOW_ENABLE);
	
	timer_primary_output_config(M1_2TIME,ENABLE);
	timer_primary_output_config(M3_4TIME,ENABLE);
	timer_enable(M1_2TIME);
	timer_enable(M3_4TIME);
}


/*
*@ Description 使能定时器时钟
*@ param 定时器
*@ return 无返回值
*/ 
static void RCU_TIME_ENABLE(uint32_t TIME)
{
	switch(TIME)
	{
		case TIMER0:
			rcu_periph_clock_enable(RCU_TIMER0);
		break;
		case TIMER1:
			rcu_periph_clock_enable(RCU_TIMER1);
		break;
		case TIMER2:
			rcu_periph_clock_enable(RCU_TIMER2);
		break;
		case TIMER3:
			rcu_periph_clock_enable(RCU_TIMER3);
		break;
		case TIMER4:
			rcu_periph_clock_enable(RCU_TIMER4);
		break;		
		case TIMER5:
			rcu_periph_clock_enable(RCU_TIMER5);
		break;
		case TIMER6:
			rcu_periph_clock_enable(RCU_TIMER6);
		break;
		case TIMER7:
			rcu_periph_clock_enable(RCU_TIMER7);
		break;
	}
}
/*
*@ Description 设置电机转速
*@ param 电机序号
*@ param 速度 大于0正转 小于0反转
*@ return 0输入错误
*/


uint8_t Set_Motor_Speed(uint16_t Motor,float Speed)
{
	uint16_t Num;
	if((Speed>100)&&(Speed<-100))
		return 0;
	
	if(Speed>=0)
	{
		Num=(uint16_t)(Speed*54);
	}else
	{
		Num=(uint16_t)(-Speed*54);
	}
	
	if((5.0f>Speed)&&(-5.0f<Speed))
	{
		switch(Motor)
		{
			case M1:
				timer_channel_output_pulse_value_config(M1_2TIME,M1_A,0);
				timer_channel_output_pulse_value_config(M1_2TIME,M1_B,0);
			break;
			case M2:
				timer_channel_output_pulse_value_config(M1_2TIME,M2_A,0);
				timer_channel_output_pulse_value_config(M1_2TIME,M2_B,0);
			break;
			case M3:
				timer_channel_output_pulse_value_config(M3_4TIME,M3_A,0);
				timer_channel_output_pulse_value_config(M3_4TIME,M3_B,0);
			break;
			case M4:
				timer_channel_output_pulse_value_config(M3_4TIME,M4_A,0);
				timer_channel_output_pulse_value_config(M3_4TIME,M4_B,0);
			break;
		}
	}else
	{
		switch(Motor)
		{
			case M1:
				if(Speed>=0)//正转
				{
					timer_channel_output_pulse_value_config(M1_2TIME,M1_A,0);
					timer_channel_output_pulse_value_config(M1_2TIME,M1_B,Num);
				}else       //反转
				{
					timer_channel_output_pulse_value_config(M1_2TIME,M1_A,Num);
					timer_channel_output_pulse_value_config(M1_2TIME,M1_B,0);
				}
			break;
			case M2:
				if(Speed>=0)//正转
				{
					timer_channel_output_pulse_value_config(M1_2TIME,M2_A,0);
					timer_channel_output_pulse_value_config(M1_2TIME,M2_B,Num);
				}else       //反转
				{
					timer_channel_output_pulse_value_config(M1_2TIME,M2_A,Num);
					timer_channel_output_pulse_value_config(M1_2TIME,M2_B,0);
				}
			break;
			case M3:
				if(Speed>=0)//正转
				{
					timer_channel_output_pulse_value_config(M3_4TIME,M3_A,Num);
					timer_channel_output_pulse_value_config(M3_4TIME,M3_B,0);
				}else       //反转
				{
					timer_channel_output_pulse_value_config(M3_4TIME,M3_A,0);
					timer_channel_output_pulse_value_config(M3_4TIME,M3_B,Num);
				}
			break;
			case M4:
				if(Speed>=0)//正转
				{
					timer_channel_output_pulse_value_config(M3_4TIME,M4_A,Num);
					timer_channel_output_pulse_value_config(M3_4TIME,M4_B,0);
				}else       //反转
				{
					timer_channel_output_pulse_value_config(M3_4TIME,M4_A,0);
					timer_channel_output_pulse_value_config(M3_4TIME,M4_B,Num);
				}
			break;
		}
	}
	return 1;
}






