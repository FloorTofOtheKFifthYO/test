//��������
//��λ��
//	cmd[0] = 0x00, cmd[1] = 0x00 , cmd[2] = 0x00 , cmd[3] = 0x00 , cmd[4] = 0x00;
//���ã�
//	cmd[0] ,ʹ����ˢ�ջ��������̷�������һλΪ��ˢ���ڶ�λ���̷���
//		���磬cmd[0] |= (1<<1) ,��Ϊʹ�������̷���
//	cmd[1] ,PWM���ͨ������Ϊ6 ��7 ��8 ��9����Ӧ���ӵ�C6��C7��A8,A9����û��ʹ����ˢ�ջ�ʱ��
//		Ҳ����ʹ��PWM�������,ʹ�÷����ǣ���ѡ����ˢ�ջ����ܣ�������PWM���Ƶ�ʣ����������ͨ��
//	cmd[2] ,����PWM��Ƶ�ʣ���Ÿ�λ��
//	cmd[3] ,����PWM��Ƶ�ʣ���ŵ�λ���������֧�ֵ�65535HZ��P�����
//	cmd[4] ,����ʹ���ĸ���ʱ��������ˢ�ķ���������2 3 4����ӦTIM2,TIM3,TIM4
//	cmd[5] ,���÷�����ʱ������ʱ����ʹ�õĹ���
//	cmd[6] ,���÷������ڣ���ʱ����ʹ��
//���ƣ�
//	�����̵���ģʽ
//		cmd[0] , ��һλ--B12 , �ڶ�λ--B13 �� ����λ--B14
//		���磬cmd[0] |=1<<2 ,��B14�ø�
//	�ٶȻ�P��Ƶ������
//		����ģʽ
//		һ������һ·���ã���3����Ա���һ����Ϣ�飬��һ����ԱΪ��ѡ��������Ϊ����ֵ
//		cmd[0] ,��4λ��Ϊ����Ϊ�ٶ����ã�����λ��Ϊ����ΪP��Ƶ������
//			���磬cmd[0] |= 7<<4,�򱾴�Ϊ����7ͨ����p��Ƶ��
//		cmd[1] ,����ֵ�ĸ�8λ
//		cmd[2] ,����ֵ�õͰ�λ
//		������·ͬʱ���ã��������һ��ָ������������Ϣ�飬����һ��������cmd[0]��cmd[3]λ��ѡ

#include "client.h"
#include "can.h"
#include "delay.h"

#define COUNT_NUM 5000

#include "can.h"
u8 setSpeed_1[3] = {0};
u8 setSpeed_2[6] = {0};
u8 setIO[1] = {0};

void init_subsector(u8 ID , u8 EN_unbrush,u8 channel ,u16 frep, u8 feedback_tim){
	int count = 0;
	u8 init_buf[7] = {0};
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(ID,init_buf,7);
	delay_ms(200);
	init_buf[0] |= EN_unbrush;//ʹ�ܱջ�
	init_buf[1] = channel;
	init_buf[2] =(u8)(frep>>8);
	init_buf[3] = (u8)frep;
	init_buf[4] = feedback_tim;
	init_buf[5] = 0;//��ʱδʹ��
	init_buf[6] = 0;
	
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(ID,init_buf,7);
	delay_ms(200);
}
//�����ٶ�
void setUnbrushSpeed_1(u8 ID,u8 channel , int speed){
	int count;
	setSpeed_1[0] = channel;
	setSpeed_1[1] = (u8)(speed>>8);
	setSpeed_1[2] = (u8)(speed>>0);
	count = COUNT_NUM;
	while(count-->0);
	can_send_msg(ID,setSpeed_1,3);
}

void setUnbrushSpeed_2(u8 channel_1 , int speed_1,u8 channel_2 , int speed_2){
	
}


void set_IO(u8 ID, u8 io[]){
	setIO[0] = 0;
	setIO[0] |= io[0]<<0;
	setIO[0] |= io[1]<<1;
	setIO[0] |= io[2]<<2;
	can_send_msg(ID,setIO,1);
}
