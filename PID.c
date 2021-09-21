/*****************************************************************
File name:PID控制器

Author:赵华磊

Version:V0.1

Description:根据给定参数计算PID

Others:

Log:2021/5/19
*****************************************************************/
#include "PID.h"


/*
*@ Description PID计算
*@ param PID结构体
*@ return 无返回值
*/
void PID_Calculate(PID_Type *Parameter)
{
	//计算误差
	Parameter->Error=Parameter->Expectations-Parameter->Observations;//期望-观测
	
	//比例计算
	Parameter->P_Value=Parameter->P*(Parameter->Error-Parameter->Last_Error);
	
	//积分计算
	Parameter->I_Value=Parameter->I*Parameter->Error;
	
	//微分计算
	Parameter->D_Value=Parameter->D*(Parameter->Error-2*Parameter->Last_Error+Parameter->Previous_Error);
	//记录这次误差和上次误差
	Parameter->Previous_Error=Parameter->Last_Error;
	Parameter->Last_Error=Parameter->Error;
	
	//计算pid输出
	Parameter->PID_Out+=Parameter->P_Value+Parameter->I_Value+Parameter->D_Value;
	
	//输出限幅
	if(Parameter->PID_Out<Parameter->PID_Min)
		Parameter->PID_Out=Parameter->PID_Min;
	if(Parameter->PID_Out>Parameter->PID_Max)
		Parameter->PID_Out=Parameter->PID_Max;
}










