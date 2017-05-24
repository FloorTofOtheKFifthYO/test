#include "encoder.h"
#include "string.h"

SwitchTIM * Which;
int * Value;




void encoder_init(SwitchTIM * W){
	Which = W;
	
	can_add_callback(encoder_canID1,encoder_callback);
	can_add_callback(encoder_canID5,encoder_callback);
	can_add_callback(encoder_canID3,encoder_callback);
	can_add_callback(encoder_canID4,encoder_callback);
	can_add_callback(encoder_canID8,encoder_callback);
	
}

void encoder_callback(CanRxMsg *can_rx_msg){
	data_convert_readTIM temp;
	switch (can_rx_msg->StdId){
		case encoder_canID1:
			temp.u8_form[0] = can_rx_msg->Data[0];
            temp.u8_form[1] = can_rx_msg->Data[1];
            temp.u8_form[2] = can_rx_msg->Data[2];
            temp.u8_form[3] = can_rx_msg->Data[3];
            memcpy((void*)&Which->GetTim1,&temp.s32_form,4);
			break;
		case encoder_canID3:
			temp.u8_form[0] = can_rx_msg->Data[0];
            temp.u8_form[1] = can_rx_msg->Data[1];
            temp.u8_form[2] = can_rx_msg->Data[2];
            temp.u8_form[3] = can_rx_msg->Data[3];
            memcpy((void*)&Which->GetTim3,&temp.s32_form,4);
			break;
		case encoder_canID4:
			temp.u8_form[0] = can_rx_msg->Data[0];
            temp.u8_form[1] = can_rx_msg->Data[1];
            temp.u8_form[2] = can_rx_msg->Data[2];
            temp.u8_form[3] = can_rx_msg->Data[3];
            memcpy((void*)&Which->GetTim4,&temp.s32_form,4);
			break;
		case encoder_canID5:
			temp.u8_form[0] = can_rx_msg->Data[0];
            temp.u8_form[1] = can_rx_msg->Data[1];
            temp.u8_form[2] = can_rx_msg->Data[2];
            temp.u8_form[3] = can_rx_msg->Data[3];
            memcpy((void*)&Which->GetTim5,&temp.s32_form,4);
			break;
		case encoder_canID8:
			temp.u8_form[0] = can_rx_msg->Data[0];
            temp.u8_form[1] = can_rx_msg->Data[1];
            temp.u8_form[2] = can_rx_msg->Data[2];
            temp.u8_form[3] = can_rx_msg->Data[3];
            memcpy((void*)&Which->GetTim8,&temp.s32_form,4);
			break;
		default :break;
		
	}
}
/**
*����ʹ���ĸ���ʱ��
* ����TIM1��TIM3��TIM4��TIM5,TIM8
* SΪ1ʱΪ�ٶ�ģʽ��2Ϊλ��ģʽ
*��������1,3,5,4,5,8.������Ч
*/
void SetUsed(u8 N, u8 S){
	u8 a[2];
	a[0] = N;
	a[1] = S;
	can_send_msg(INUSE_CANID,a,2);
}

/*
*���ܣ����òɼ�ʱ��
*������ʱ������λms
*ע�⣺�������ã����������ʧ��
*/

void SetTime(u8 T){
	can_send_msg(SETTIME_CANID,&T,1);
}


/*
*���ܣ�����
*������
*ע�⣺�������ã����������ʧ��
*/
void encoder_reset()
{
	u8 a[1];
	a[0] = 1;
	can_send_msg(RESET_CANID,a,1);
}
