#ifndef _MOTORCTRL_H_
#define _MOTORCTRL_H_


#include "sys.h"


#define MOTOR_MAX 16

//���can����ID����
#define MOTOR10_CANID_BASE 0x0A0//0��10�ŵ��
#define MOTOR11_CANID_BASE 0x0B0
#define MOTOR12_CANID_BASE 0x0C0

//ָ��ѡ��ƫ����
#define CANID_OFFSET_MOTORRESET 0x000//��λ
#define CANID_OFFSET_MOTORMODE 0x001//ģʽѡ��
#define CANID_OFFSET_MOTORELEC 0x003//����ģʽ
#define CANID_OFFSET_MOTORSPEED 0x004//�ٶ�ģʽ
#define CANID_OFFSET_MOTORPLACE 0x005//λ��ģʽ
#define CANID_OFFSET_MOTORSETUP 0X00A//����ģʽ
#define CANID_OFFSET_MOTORSETZERO 0X00E//���
#define CANID_OFFSET_MOTORSCHECK 0x00F//���߼��

#define CANID_OFFSET_FEEDBACK 0x00B //��ȡ��������
#define CANID_OFFEST_CHECKONLINE 0x00F //�������߼����Ϣ

#define CurrentMode 0x02
#define SpeedMode 0x03
#define PositionMode 0x04

#define databack CANID_OFFSET_FEEDBACK
#define onlineback CANID_OFFEST_CHECKONLINE

typedef struct {
	int Current;
	int Speed;
	s32 Position;
}BackDATA ;

void RoboModule_init();
void RoboModule_RESET(char Number , ...);
void RoboModule_CHOICE_mode(u8 Mode , char Number , ...);
void RoboModule_SETUP(u8 Time ,u8 CTL1 , char Number , ...);
void RoboModule_SET_speed(u8 Number ,u16 PWM , int speed);;
void RoboModule_SET_Position(u8 Number ,u16 PWM , s32 Position,int speed);
void RoboModule_Check(char Number , ...);
void RoboModule_Add_Callback(u8 BackMode ,void *msg_rcv_callback_func,char Number, ...);
void RoboModule_Feedback_Callback(CanRxMsg *can_rx_msg);
BackDATA* ReturnData(u8 Number);
u16 CheckMOTOR();
void RoboModule_SET_Positiono(u8 Number ,u16 PWM , s32 Position);
void RoboModule_SET_Zero(u8 Number);

#endif
