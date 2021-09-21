/*****************************************************************
File name:PID������

Author:�Ի���

Version:V0.1

Description:���ݸ�����������PID

Others:

Log:2021/5/19
*****************************************************************/
#include "PID.h"


/*
*@ Description PID����
*@ param PID�ṹ��
*@ return �޷���ֵ
*/
void PID_Calculate(PID_Type *Parameter)
{
	//�������
	Parameter->Error=Parameter->Expectations-Parameter->Observations;//����-�۲�
	
	//��������
	Parameter->P_Value=Parameter->P*(Parameter->Error-Parameter->Last_Error);
	
	//���ּ���
	Parameter->I_Value=Parameter->I*Parameter->Error;
	
	//΢�ּ���
	Parameter->D_Value=Parameter->D*(Parameter->Error-2*Parameter->Last_Error+Parameter->Previous_Error);
	//��¼��������ϴ����
	Parameter->Previous_Error=Parameter->Last_Error;
	Parameter->Last_Error=Parameter->Error;
	
	//����pid���
	Parameter->PID_Out+=Parameter->P_Value+Parameter->I_Value+Parameter->D_Value;
	
	//����޷�
	if(Parameter->PID_Out<Parameter->PID_Min)
		Parameter->PID_Out=Parameter->PID_Min;
	if(Parameter->PID_Out>Parameter->PID_Max)
		Parameter->PID_Out=Parameter->PID_Max;
}










