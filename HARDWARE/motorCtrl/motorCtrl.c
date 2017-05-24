#include "motorCtrl.h"
#include "can.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define COUNT_NUM 5000

u8 motor_message[8];
BackDATA *Backdata = NULL;
BackDATA *TempData = NULL;
u16 CheckMotor = 0xFFFF;

void RoboModule_init()
{
	if (Backdata == NULL)
	{
		Backdata = (BackDATA *)malloc(sizeof(BackDATA));
	}
	if (TempData == NULL)
	{
		TempData = (BackDATA *)malloc(sizeof(BackDATA)*16);
	}
}

/*
*���ܣ���λ
*������ NumberΪ������
*	   
*
*/
void RoboModule_RESET(char Number , ...){
	
	u8 CANID = CANID_OFFSET_MOTORRESET;
	char buffer[MOTOR_MAX];
	int i = 0;
	va_list arg_ptr;
	char number;
	int count=5000;
	
	if (Backdata == NULL)
	{
		Backdata = (BackDATA *)malloc(sizeof(BackDATA));
	}
	if (TempData == NULL)
	{
		TempData = (BackDATA *)malloc(sizeof(BackDATA)*16);
	}
	
	if(Number > 15){
		Number = 0;
	}
	motor_message[0] = 0x55;
	motor_message[1] = 0x55;
	motor_message[2] = 0x55;
	motor_message[3] = 0x55;
	motor_message[4] = 0x55;
	motor_message[5] = 0x55;
	motor_message[6] = 0x55;
	motor_message[7] = 0x55;
	
	if(Number == 0){
		CANID = CANID_OFFSET_MOTORRESET;
		CANID |= Number<<4;
		can_send_msg(CANID , motor_message , 8);
		return ;
	}
	
	va_start(arg_ptr, Number);  
	//vsnprintf(buffer, MOTOR_MAX, &Number, arg_ptr);
	
	while(i < MOTOR_MAX){
		number  = va_arg(arg_ptr,char);
		if (number >15||number ==0){
			break;
		}
		memset(&(TempData[number]),0,sizeof(BackDATA));
		CANID = CANID_OFFSET_MOTORRESET;
		CANID |= number<<4;
		count = COUNT_NUM;
		while(count-->0);
		can_send_msg(CANID , motor_message , 8);
		
		i++;
	}
	
	memset(&(TempData[Number]),0,sizeof(BackDATA));
	CANID = CANID_OFFSET_MOTORRESET;
	CANID |= Number<<4;
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
	
	va_end(arg_ptr);
}

/*
*���ܣ�ģʽѡ��
*������NumberΪ������
*	   ModeΪ��ѡģʽ,�� CurrentMode,SpeedMode,PositionMode
*
*
*/
void RoboModule_CHOICE_mode(u8 Mode , char Number , ...){
	u8 CANID = CANID_OFFSET_MOTORMODE;
	char buffer[MOTOR_MAX];
	int i = 0;
	int count=5000;
	va_list arg_ptr;
	char number = 0;
	
	if (Number > 15){
		return ;
	}
	motor_message[0] = Mode;
	motor_message[1] = 0x55;
	motor_message[2] = 0x55;
	motor_message[3] = 0x55;
	motor_message[4] = 0x55;
	motor_message[5] = 0x55;
	motor_message[6] = 0x55;
	motor_message[7] = 0x55;
	
	
	va_start(arg_ptr, Number);  
	//vsnprintf(buffer, MOTOR_MAX, &Number, arg_ptr);
	
	while(i < MOTOR_MAX){
		number  = va_arg(arg_ptr,char);
		if (number >15||number ==0){
			break;
		}
		CANID = CANID_OFFSET_MOTORMODE;
		CANID |= number<<4;
		count = COUNT_NUM;
		while(count-->0);
		can_send_msg(CANID , motor_message , 8);
		i++;
	}
	CANID = CANID_OFFSET_MOTORMODE;
	CANID |= Number<<4;
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
	
	va_end(arg_ptr);
}

/*
*���ܣ�����
*������ Number��Ϊ������
*	   Time��Ϊ��Ϣ��������
*	   CTL1�����Ծ��� CTL1 �� CTL2 �˿�����Ϊ������λ���ܺ��ڵ�ƽ�����仯ʱ���Ƿ���ⷢ�͵�ǰ�ĵ�ƽֵ��
*ע�⣺������ֻ�ڽ������ĵ� 8 ���˶�ģʽ֮�󣬲Ż������ԵĶ��ⷢ�����������ĵ������ٶȡ�λ�õ���Ϣ��
*	   ͬ��ֻ�н������ĵ� 8 ���˶�ģʽ֮�󣬲Ż��� CTL �˿ڵ�ƽ�仯����ⷢ�����ƽֵ
*/

void  RoboModule_SETUP(u8 Time ,u8 CTL1 , char Number , ...){
	u8 CANID = CANID_OFFSET_MOTORSETUP;
	char buffer[MOTOR_MAX];
	int i = 0;
	va_list arg_ptr;
	char number;
	int count = COUNT_NUM;
	
	if (Number > 15){
		return ;
	}
	motor_message[0] = Time;
	motor_message[1] = CTL1;
	motor_message[2] = 0x55;
	motor_message[3] = 0x55;
	motor_message[4] = 0x55;
	motor_message[5] = 0x55;
	motor_message[6] = 0x55;
	motor_message[7] = 0x55;
	
	
	va_start(arg_ptr, Number);  
	
	while(i < MOTOR_MAX){
		number  = va_arg(arg_ptr,char);
		if (number >15||number <=0){
			break;
		}
		CANID = CANID_OFFSET_MOTORSETUP;
		CANID |= number<<4;
		count = COUNT_NUM;
		while(count-->0);
		can_send_msg(CANID , motor_message , 8);
		i++;
	}
	
	CANID = CANID_OFFSET_MOTORSETUP;
	CANID |= Number<<4;
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
	
	va_end(arg_ptr);
}

/*
*���ܣ������ٶ�
*������ NumberΪ������
*	   PWMΪP���޶�����Χ0~5000
*	   speedΪ�����ٶȣ���Χ0~30000+�����ǵĵ����0~8100
*
*/
void RoboModule_SET_speed(u8 Number ,u16 PWM , int speed){
	u8 CANID = CANID_OFFSET_MOTORSPEED;
	int count = COUNT_NUM;
	if(Number > 15){
		return ;
	}
	
	CANID |= Number<<4;
	
	motor_message[0] = (unsigned char)((PWM>>8)&0xff);
	motor_message[1] = (unsigned char)(PWM&0xff);
	motor_message[2] = (unsigned char)((speed>>8)&0xff);
	motor_message[3] = (unsigned char)(speed&0xff);
	motor_message[4] = 0x55;
	motor_message[5] = 0x55;
	motor_message[6] = 0x55;
	motor_message[7] = 0x55;
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
}

/*
*���ܣ�����λ��
*������ NumberΪ������
*	   PWMΪP���޶�����Χ0~5000
*	   Position����λ�ã���Χ0 ~ 2^31
*
*/
void RoboModule_SET_Positiono(u8 Number ,u16 PWM , s32 Position){
	int count = COUNT_NUM;
	u8 CANID = CANID_OFFSET_MOTORPLACE;
	if(Number > 15){
		return ;
	}
	
	CANID |= Number<<4;
	
	motor_message[0] = (unsigned char)((PWM>>8)&0xff);
	motor_message[1] = (unsigned char)((PWM)&0xff);
	motor_message[2] = 0x55;
	motor_message[3] = 0x55;
	motor_message[4] = (unsigned char)((Position>>24)&0xff);
	motor_message[5] = (unsigned char)((Position>>16)&0xff);
	motor_message[6] = (unsigned char)((Position>>8)&0xff);
	motor_message[7] = (unsigned char)(Position&0xff);
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
}

/*
*���ܣ�����λ��
*������ NumberΪ������
*	   PWMΪP���޶�����Χ0~5000
*	   Position����λ�ã���Χ0 ~ 2^31
*
*/
void RoboModule_SET_Position(u8 Number ,u16 PWM , s32 Position, int speed){
	int count = COUNT_NUM;
	u8 CANID = CANID_OFFSET_MOTORPLACE;
	if(Number > 15){
		return ;
	}
	
	CANID |= Number<<4;
	
	motor_message[0] = (unsigned char)((PWM>>8)&0xff);
	motor_message[1] = (unsigned char)((PWM)&0xff);
	motor_message[2] = (unsigned char)((speed>>8)&0xff);
	motor_message[3] = (unsigned char)(speed&0xff);
	motor_message[4] = (unsigned char)((Position>>24)&0xff);
	motor_message[5] = (unsigned char)((Position>>16)&0xff);
	motor_message[6] = (unsigned char)((Position>>8)&0xff);
	motor_message[7] = (unsigned char)(Position&0xff);
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
}

/*
*���ܣ�����λ��0
*������ NumberΪ������
*
*/
void RoboModule_SET_Zero(u8 Number){
	int count = COUNT_NUM;
	u8 CANID = CANID_OFFSET_MOTORSETZERO;
	if(Number > 15){
		return ;
	}
	
	CANID |= Number<<4;
	
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(CANID , motor_message , 8);
}

/*
*���ܣ����߼�⣬���Լ�����Ƿ�������
*������number��������
*		��Χ��1~15������ȫ�����
*

**/
void RoboModule_Check(char Number , ...){
	u8 CANID = CANID_OFFSET_MOTORSCHECK;
	char buffer[MOTOR_MAX];
	int i = 0;
	va_list arg_ptr;
	char number;
	int count = COUNT_NUM;
	
	motor_message[0] = 0x55;
	motor_message[1] = 0x55;
	motor_message[2] = 0x55;
	motor_message[3] = 0x55;
	motor_message[4] = 0x55;
	motor_message[5] = 0x55;
	motor_message[6] = 0x55;
	motor_message[7] = 0x55;
	
	if(Number >15||Number == 0){
		Number = 0;
		CANID = CANID_OFFSET_MOTORSCHECK;
		CANID |= Number<<4;
		can_send_msg(CANID , motor_message , 8);
	}else {
		
		va_start(arg_ptr, Number);  
		//vsnprintf(buffer, MOTOR_MAX, &Number, arg_ptr);
		
		while(i < MOTOR_MAX){
			number  = va_arg(arg_ptr,char);
			if (number >15||number <=0){
				break;
			}
			CANID = CANID_OFFSET_MOTORSCHECK;
			CANID |= number<<4;
			CheckMotor &= ~(0x01<<(number-1));
			count = COUNT_NUM;
			while(count-->0);
			can_send_msg(CANID , motor_message , 8);
			i++;
		}
		
		CANID = CANID_OFFSET_MOTORSCHECK;
		CANID |= Number<<4;
		CheckMotor &= ~(0x01<<(Number-1));
		count = COUNT_NUM;
		while(count-->0);
		can_send_msg(CANID , motor_message , 8);
		va_end(arg_ptr);
	}
	
}

/*
*���� ����ӻص�����
*������Number��������
*      msg_rcv_callback_func�����պ���ָ��
*	  Backmode :������Ϣ���ͣ�databackΪ�������� ,onlinebackΪ���߼�ⷵ��
*/
void RoboModule_Add_Callback(u8 BackMode ,void *msg_rcv_callback_func,char Number, ...){
	
	u8 CANID = BackMode;
	char buffer[MOTOR_MAX];
	int i = 0;
	va_list arg_ptr;
	char number;
	
	va_start(arg_ptr, Number);  
	
	while(i < MOTOR_MAX){
		number  = va_arg(arg_ptr,char);
		if (number >15||number <=0){
			break;
		}
		CANID = BackMode;
		CANID |= number<<4;
		can_add_callback(CANID , msg_rcv_callback_func);
		i++;
	}
	
	CANID = BackMode;
	CANID |= Number<<4;
	can_add_callback(CANID , msg_rcv_callback_func);
	
	va_end(arg_ptr);
}

/*
*���ܣ��ص�����
*
*
*
***/
void RoboModule_Feedback_Callback(CanRxMsg *can_rx_msg){
	u8 Tell_ApartOFFSET = (can_rx_msg->StdId)&0x0F;
	u8 Tell_ApartNumber = (can_rx_msg->StdId)>>4;
	u8 i = 0;
	u8 j = 0;
	
	if(Tell_ApartNumber == 0x08)
		i = i;
	
	switch(Tell_ApartOFFSET){
		case databack:
			Backdata->Current = can_rx_msg->Data[0];
			Backdata->Current = ((Backdata->Current)<<8)|can_rx_msg->Data[1];
			Backdata->Speed = can_rx_msg->Data[2];
			Backdata->Speed = ((Backdata->Speed)<<8)|can_rx_msg->Data[3];
			Backdata->Position = can_rx_msg->Data[4];
			Backdata->Position = ((Backdata->Position)<<8)| can_rx_msg->Data[5];
			Backdata->Position = ((Backdata->Position)<<8)|can_rx_msg->Data[6];
			Backdata->Position = ((Backdata->Position)<<8)| can_rx_msg->Data[7];

			TempData[Tell_ApartNumber].Current = Backdata->Current;//��������浽�����ֻ�������һ�εĽ��
			TempData[Tell_ApartNumber].Speed = Backdata->Speed;
			TempData[Tell_ApartNumber].Position = Backdata->Position;
			break;
		case onlineback:
			CheckMotor |= 0x01<<(Tell_ApartNumber-1);//������������쳣����Ѿ��ָ�
			break;
		default :break;
	}
}

/*
*���� �����ص�������������ָ��
*���� ��������
*ʹ�÷��������� BackDATA ����ָ�룬ָ����ڸú�������ֵ
*
*
*/
BackDATA* ReturnData(u8 Number){
	return &TempData[Number];
}

/*
*���� �����ص�������
*���� ����
*ʹ�÷���������ȫ�������򷵻�0xFF������˵��������쳣���쳣�����ż�Ϊ��0����Ӧλ�����緵��ֵΪ0xF8,˵�����Ϊ4�ĵ���쳣
*
*
*/
u16 CheckMOTOR(){
	return CheckMotor;
}