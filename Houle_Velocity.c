/*****************************************************************
File name:霍尔测速

Author:赵华磊

Version:V0.2

Description:磁编码计算脉冲数计算速度

Others:

Log:2021/7/13
*****************************************************************/
#include "Houle_Velocity.h"


static struct
{
	uint16_t M1_Count;
	uint16_t M2_Count;
	uint16_t M3_Count;
	uint16_t M4_Count;
}Motor_Pulse;//脉冲计数器

static exti_line_enum M1_A_EXTI,M2_A_EXTI,M3_A_EXTI,M4_A_EXTI,
								M1_B_EXTI,M2_B_EXTI,M3_B_EXTI,M4_B_EXTI;//霍尔外部中断线
static struct
{
	Time M1_T;
	Time M2_T;
	Time M3_T;
	Time M4_T;
}Pulse_Time;//测量时间

//测速标志位
Measuring_Velocity_Type Measuring_Velocity={0,0,0,0,0,0,0,0};


static void Houle_gpio_init(void);
static void Houle_EXTI_init(void);

static uint32_t GPIO_Pin_Change_Source(uint32_t GPIO_Pin);
static uint8_t GPIO_Periph_Change_GPIO_PORT_SOURCE(uint32_t GPIO_Periph);
static exti_line_enum GPIO_Pin_Change_EXTI_Line(uint32_t GPIO_Pin);

/*
*@ Description 霍尔测速系统初始化
*@ param 无参数
*@ return 无返回值
*/
void Houle_Velocity_init(void)
{
	Houle_gpio_init();
	Houle_EXTI_init();
}

/*
*@ Description: 初始化霍尔传感器要使用的GPIO
*@ param 无参数
*@ return 无返回值
*/
static void Houle_gpio_init(void)
{
	
	gpio_init(M1_A_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M1_A_GPIO_Pin);
	gpio_init(M1_B_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M1_B_GPIO_Pin);
	
	gpio_init(M2_A_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M2_A_GPIO_Pin);
	gpio_init(M2_B_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M2_B_GPIO_Pin);
	
	gpio_init(M3_A_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M3_A_GPIO_Pin);
	gpio_init(M3_B_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M3_B_GPIO_Pin);
	
	gpio_init(M4_A_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M4_A_GPIO_Pin);
	gpio_init(M4_B_GPIO_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,M4_B_GPIO_Pin);
	
}

/*
*@ Description:初始化霍尔传感器的外部中断
*@ param 无参数
*@ return 无返回值
*/
static void Houle_EXTI_init(void)
{
	//使能外部中断
	nvic_irq_enable(EXTI_IRon_A, 2, 0);
	nvic_irq_enable(EXTI_IRon_B, 1, 0);
	
	M1_A_EXTI=GPIO_Pin_Change_EXTI_Line(M1_A_GPIO_Pin);
	M1_B_EXTI=GPIO_Pin_Change_EXTI_Line(M1_B_GPIO_Pin);
	
	M2_A_EXTI=GPIO_Pin_Change_EXTI_Line(M2_A_GPIO_Pin);
	M2_B_EXTI=GPIO_Pin_Change_EXTI_Line(M2_B_GPIO_Pin);

	M3_A_EXTI=GPIO_Pin_Change_EXTI_Line(M3_A_GPIO_Pin);
	M3_B_EXTI=GPIO_Pin_Change_EXTI_Line(M3_B_GPIO_Pin);

	M4_A_EXTI=GPIO_Pin_Change_EXTI_Line(M4_A_GPIO_Pin);
	M4_B_EXTI=GPIO_Pin_Change_EXTI_Line(M4_B_GPIO_Pin);	
	
	//M1
	//M1_A初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M1_A_GPIO_Periph),GPIO_Pin_Change_Source(M1_A_GPIO_Pin));
	exti_init(M1_A_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M1_A_EXTI);
	//M1_B初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M1_B_GPIO_Periph),GPIO_Pin_Change_Source(M1_B_GPIO_Pin));
	exti_init(M1_B_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M1_B_EXTI);
	
	//M2
	//M2_A初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M2_A_GPIO_Periph),GPIO_Pin_Change_Source(M2_A_GPIO_Pin));
	exti_init(M2_A_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M2_A_EXTI);
	//M2_B初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M2_B_GPIO_Periph),GPIO_Pin_Change_Source(M2_B_GPIO_Pin));
	exti_init(M2_B_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M2_B_EXTI);
	
	//M3
	//M3_A初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M3_A_GPIO_Periph),GPIO_Pin_Change_Source(M3_A_GPIO_Pin));
	exti_init(M3_A_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M3_A_EXTI);
	//M3_B初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M3_B_GPIO_Periph),GPIO_Pin_Change_Source(M3_B_GPIO_Pin));
	exti_init(M3_B_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M3_B_EXTI);
	
	//M4
	//M4_A初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M4_A_GPIO_Periph),GPIO_Pin_Change_Source(M4_A_GPIO_Pin));
	exti_init(M4_A_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M4_A_EXTI);
	//M4_B初始化
	gpio_exti_source_select(GPIO_Periph_Change_GPIO_PORT_SOURCE(M4_B_GPIO_Periph),GPIO_Pin_Change_Source(M4_B_GPIO_Pin));
	exti_init(M4_B_EXTI,EXTI_INTERRUPT,EXTI_TRIG_RISING);//上升延触发
	exti_interrupt_flag_clear(M4_B_EXTI);
}



/*
*@ Description 获取中断霍尔测速数据
*@ param 电机编号
*@ return 返回电机线速度（mm每秒） -1000;不存在此电机
*/
float Get_Motor_Velocity(uint8_t Motor)
{
	float temp;
	switch(Motor)
	{
		case 1:
			temp=Motor_Pulse.M1_Count*Motor_Factor/Get_deta_T(Pulse_Time.M1_T);
			Pulse_Time.M1_T=Get_System_T();
			Motor_Pulse.M1_Count=0;
			if(Measuring_Velocity.M1_Polar)
				return -temp;
			else 
				return temp;
		case 2:
			temp=Motor_Pulse.M2_Count*Motor_Factor/Get_deta_T(Pulse_Time.M2_T);
			Pulse_Time.M2_T=Get_System_T();
			Motor_Pulse.M2_Count=0;
			if(Measuring_Velocity.M2_Polar)
				return -temp;
			else 
				return temp;
		case 3:
			temp=Motor_Pulse.M3_Count*Motor_Factor/Get_deta_T(Pulse_Time.M3_T);
			Pulse_Time.M3_T=Get_System_T();
			Motor_Pulse.M3_Count=0;
			if(Measuring_Velocity.M3_Polar)
				return -temp;
			else 
				return temp;
		case 4:
			temp=Motor_Pulse.M4_Count*Motor_Factor/Get_deta_T(Pulse_Time.M4_T);
			Pulse_Time.M4_T=Get_System_T();
			Motor_Pulse.M4_Count=0;
			if(Measuring_Velocity.M4_Polar)
				return -temp;
			else 
				return temp;
	}
	return -1000;
}

/*
*@ Description:霍尔A相外部中断服务函数
*@ param 无参数
*@ return 无返回值
*/
void EXTI5_9_IRQHandler(void)
{
	float temp;
	/*************************************************///M1一号电机
	if(exti_interrupt_flag_get(M1_A_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M1==1)//下降沿是否产生
		{
			Measuring_Velocity.M1=0;//清除下降沿产生标志位
			if(Motor_Pulse.M1_Count++>=65535)//脉冲计数
				Motor_Pulse.M1_Count=0;
			//设置下降沿触发
			EXTI_RTEN &= ~(uint32_t)M1_A_EXTI;
            EXTI_FTEN |= (uint32_t)M1_A_EXTI;
		}else
		{
			Measuring_Velocity.M1=1;//下降沿产生
			//设置上升沿触发
			EXTI_RTEN |= (uint32_t)M1_A_EXTI;
			EXTI_FTEN &= ~(uint32_t)M1_A_EXTI;
		}
		exti_interrupt_flag_clear(M1_A_EXTI);
	}
	/*************************************************///M2二号电机
	if(exti_interrupt_flag_get(M2_A_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M2==1)//下降沿是否产生
		{
			Measuring_Velocity.M2=0;//清除下降沿产生标志位
			if(Motor_Pulse.M2_Count++>=65535)//脉冲计数
				Motor_Pulse.M2_Count=0;
			//设置下降沿触发
			EXTI_RTEN &= ~(uint32_t)M2_A_EXTI;
      EXTI_FTEN |= (uint32_t)M2_A_EXTI;
		}else
		{
			Measuring_Velocity.M2=1;//下降沿产生
			//设置上升沿触发
			EXTI_RTEN |= (uint32_t)M2_A_EXTI;
			EXTI_FTEN &= ~(uint32_t)M2_A_EXTI;
		}
		exti_interrupt_flag_clear(M2_A_EXTI);
	}
	/*************************************************///M3三号电机
	if(exti_interrupt_flag_get(M3_A_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M3==1)//下降沿是否产生
		{
			Measuring_Velocity.M3=0;//清除下降沿产生标志位
			if(Motor_Pulse.M3_Count++>=65535)//脉冲计数
				Motor_Pulse.M3_Count=0;
			//设置下降沿触发
			EXTI_RTEN &= ~(uint32_t)M3_A_EXTI;
      EXTI_FTEN |= (uint32_t)M3_A_EXTI;
		}else
		{
			Measuring_Velocity.M3=1;//下降沿产生
			//设置上升沿触发
			EXTI_RTEN |= (uint32_t)M3_A_EXTI;
			EXTI_FTEN &= ~(uint32_t)M3_A_EXTI;
		}
		exti_interrupt_flag_clear(M3_A_EXTI);
	}
	/*************************************************///M4四号电机
	if(exti_interrupt_flag_get(M4_A_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M4==1)//下降沿是否产生
		{
			Measuring_Velocity.M4=0;//清除下降沿产生标志位
			if(Motor_Pulse.M4_Count++>=65535)//脉冲计数
				Motor_Pulse.M4_Count=0;
			//设置下降沿触发
			EXTI_RTEN &= ~(uint32_t)M4_A_EXTI;
      EXTI_FTEN |= (uint32_t)M4_A_EXTI;
		}else
		{
			Measuring_Velocity.M4=1;//下降沿产生
			//设置上升沿触发
			EXTI_RTEN |= (uint32_t)M4_A_EXTI;
			EXTI_FTEN &= ~(uint32_t)M4_A_EXTI;
		}
		exti_interrupt_flag_clear(M4_A_EXTI);
	}
}



/*
*@ Description 霍尔B相外部中断服务函数
*@ param 无参数
*@ return 无返回值
*/
void EXTI10_15_IRQHandler(void)
{
	/*************************************************///M1一号电机
	if(exti_interrupt_flag_get(M1_B_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M1)
		{
			Measuring_Velocity.M1_Polar=0;
		}else
		{
			Measuring_Velocity.M1_Polar=1;
		}
		exti_interrupt_flag_clear(M1_B_EXTI);
	}

	/*************************************************///M2一号电机
	if(exti_interrupt_flag_get(M2_B_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M2)
		{
			Measuring_Velocity.M2_Polar=0;
		}else
		{
			Measuring_Velocity.M2_Polar=1;
		}
		exti_interrupt_flag_clear(M2_B_EXTI);
	}
	/*************************************************///M3一号电机
	if(exti_interrupt_flag_get(M3_B_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M3)
		{
			Measuring_Velocity.M3_Polar=0;
		}else
		{
			Measuring_Velocity.M3_Polar=1;
		}
		exti_interrupt_flag_clear(M3_B_EXTI);
	}
	/*************************************************///M4一号电机
	if(exti_interrupt_flag_get(M4_B_EXTI)!=RESET)
	{
		if(Measuring_Velocity.M4)
		{
			Measuring_Velocity.M4_Polar=0;
		}else
		{
			Measuring_Velocity.M4_Polar=1;
		}
		exti_interrupt_flag_clear(M4_B_EXTI);
	}

}



/*
*@ Description 输入GPIO_Pin返回外部中断中断源
*@ param GPIO_Pin
*@ return 中断源
*/
static uint32_t GPIO_Pin_Change_Source(uint32_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
			return GPIO_PIN_SOURCE_0;
		case GPIO_PIN_1:
			return GPIO_PIN_SOURCE_1;
		case GPIO_PIN_2:
			return GPIO_PIN_SOURCE_2;
		case GPIO_PIN_3:
			return GPIO_PIN_SOURCE_3;
		case GPIO_PIN_4:
			return GPIO_PIN_SOURCE_4;
		case GPIO_PIN_5:
			return GPIO_PIN_SOURCE_5;
		case GPIO_PIN_6:
			return GPIO_PIN_SOURCE_6;
		case GPIO_PIN_7:
			return GPIO_PIN_SOURCE_7;
		case GPIO_PIN_8:
			return GPIO_PIN_SOURCE_8;
		case GPIO_PIN_9:
			return GPIO_PIN_SOURCE_9;
		case GPIO_PIN_10:
			return GPIO_PIN_SOURCE_10;
		case GPIO_PIN_11:
			return GPIO_PIN_SOURCE_11;
		case GPIO_PIN_12:
			return GPIO_PIN_SOURCE_12;
		case GPIO_PIN_13:
			return GPIO_PIN_SOURCE_13;
		case GPIO_PIN_14:
			return GPIO_PIN_SOURCE_14;
		case GPIO_PIN_15:
			return GPIO_PIN_SOURCE_15;
	}
	return 0;
}



/*
*@ Description 输入GPIO_Pin返回外部中断线
*@ param GPIO_Pin
*@ return 中断源
*/
static exti_line_enum GPIO_Pin_Change_EXTI_Line(uint32_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
			return EXTI_0;
		case GPIO_PIN_1:
			return EXTI_1;
		case GPIO_PIN_2:
			return EXTI_2;
		case GPIO_PIN_3:
			return EXTI_3;
		case GPIO_PIN_4:
			return EXTI_4;
		case GPIO_PIN_5:
			return EXTI_5;
		case GPIO_PIN_6:
			return EXTI_6;
		case GPIO_PIN_7:
			return EXTI_7;
		case GPIO_PIN_8:
			return EXTI_8;
		case GPIO_PIN_9:
			return EXTI_9;
		case GPIO_PIN_10:
			return EXTI_10;
		case GPIO_PIN_11:
			return EXTI_11;
		case GPIO_PIN_12:
			return EXTI_12;
		case GPIO_PIN_13:
			return EXTI_13;
		case GPIO_PIN_14:
			return EXTI_14;
		case GPIO_PIN_15:
			return EXTI_15;
	}
	return 0;
}



/*
*@ Description 输入GPIO_Periph端口返回GPIO_PORT_SOURCE
*@ param GPIO_Periph
*@ return GPIO_PORT_SOURCE
*/
static uint8_t GPIO_Periph_Change_GPIO_PORT_SOURCE(uint32_t GPIO_Periph)
{
	switch(GPIO_Periph)
	{
		case GPIOA:
			return GPIO_PORT_SOURCE_GPIOA;
		case GPIOB:
			return GPIO_PORT_SOURCE_GPIOB;
		case GPIOC:
			return GPIO_PORT_SOURCE_GPIOC;
		case GPIOD:
			return GPIO_PORT_SOURCE_GPIOD;
		case GPIOE:
			return GPIO_PORT_SOURCE_GPIOE;
		case GPIOF:
			return GPIO_PORT_SOURCE_GPIOF;
		case GPIOG:
			return GPIO_PORT_SOURCE_GPIOG;
	}
	return 0;
} 


