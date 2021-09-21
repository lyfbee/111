#ifndef __PID_H
#define __PID_H

//PID数据类型
typedef struct
{
	float Expectations;//期望值
	float Observations;//观测值
	float Error;//误差
	float Last_Error;//上次误差
	float Previous_Error;//上上次误差
	float PID_Max;//输出限幅最大值
	float PID_Min;//输出限幅最小值
	float P;//比例参数
	float I;//积分参数
	float D;//微分参数
	float P_Value;//比例
	float I_Value;//积分
	float D_Value;//微分
	float PID_Out;//PID输出
}PID_Type;




//PID计算
void PID_Calculate(PID_Type *Parameter);









#endif
