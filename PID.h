#ifndef __PID_H
#define __PID_H

//PID��������
typedef struct
{
	float Expectations;//����ֵ
	float Observations;//�۲�ֵ
	float Error;//���
	float Last_Error;//�ϴ����
	float Previous_Error;//���ϴ����
	float PID_Max;//����޷����ֵ
	float PID_Min;//����޷���Сֵ
	float P;//��������
	float I;//���ֲ���
	float D;//΢�ֲ���
	float P_Value;//����
	float I_Value;//����
	float D_Value;//΢��
	float PID_Out;//PID���
}PID_Type;




//PID����
void PID_Calculate(PID_Type *Parameter);









#endif
