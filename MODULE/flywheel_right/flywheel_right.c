#include "flywheel_right.h"
#include <string.h>
#include "auto.h"
#include <math.h>
#include "usart.h"
#include "flywheel_close.h"

#define PITCH_MAXSPEED 0
#define YAW_MAXSPEED 0

Flywheel_right flywheel_right;

extern struct {
	int left[7];
	int right[7];
}strategy;

extern bool debug_print;

extern bool handle_r;

static int right_ms = 0;

static int fly_count = 0;
static int fly_n = 0;//��¼����ĸ���

/**
  * @brief  ��ʼ��
  *     
  * @note
  *
  * @param 
  *          
  * @retval 
  */
void flywheel_right_init()
{
	int i;
	//�Ƕȵ���ĳ�ʼ��
	RoboModule_RESET(YAW_ID_RIGHT,PITCH_ID_RIGHT,0);
	delay_ms(5);
	RoboModule_CHOICE_mode(PositionMode ,PITCH_ID_RIGHT,YAW_ID_RIGHT ,0);
	RoboModule_Add_Callback(databack,RoboModule_Feedback_Callback,PITCH_ID_RIGHT,YAW_ID_RIGHT,0);
	RoboModule_SETUP(19,0,PITCH_ID_RIGHT,YAW_ID_RIGHT,0);
	

	flywheel_right.io[0] = 0;
	flywheel_right.io[1] = 0;
	flywheel_right.io[2] = 0;
	
	init_subsector(CLIENT_ID_RIGHT,1,FLYWHEEL_CHANNEL_RIGHT,50,FLYWHEEL_FEEDBACK_RIGHT);
	setUnbrushSpeed_1(CLIENT_ID_RIGHT,FLYWHEEL_CHANNEL_RIGHT,0);
	set_IO(CLIENT_ID_RIGHT,flywheel_right.io);
	flywheel_right.pur_duty = 7.7;
	flywheel_right.pur_jmp = 6;
	flywheel_right.pur_pitch = 0;
	flywheel_right.pur_yaw = 0;
	flywheel_right.state = fly_r_finish;
	flywheel_right.fly_flag = false;
}

/**
  * @brief  �ĸ�����
  *     
  * @note
  *
  * @param ������
  *          
  * @retval 
  */
void flywheel_right_setPitch(float pitch)
{
	flywheel_right.pur_pitch = pitch;
	RoboModule_SET_Position(PITCH_ID_RIGHT,5000,pitch*100,PITCH_MAXSPEED);
	//RoboModule_SET_Position(PITCH_ID_RIGHT,5000,pitch*100,PITCH_MAXSPEED);
}

void flywheel_right_fly()
{
	flywheel_right.io[FLY_RIGHT] = 1 - flywheel_right.io[FLY_RIGHT];
	set_IO(CLIENT_ID_RIGHT,flywheel_right.io);
}

/**
  * @brief  ����ˢ
  *     
  * @note
  *
  * @param ռ�ձȻ��һ���ٶ�
  *          
  * @retval 
  */
void flywheel_right_setBrushless(float duty)
{
	flywheel_right.pur_duty = duty;
	//setUnbrushSpeed(FLYWHEEL_ID_RIGHT,(duty-7.7)/(10-7.7)*8*100);
	setUnbrushSpeed_1(CLIENT_ID_RIGHT,FLYWHEEL_CHANNEL_RIGHT,(duty-7.7)/(10-7.7)*8*100);
	//setUnbrushSpeed_1(CLIENT_ID_RIGHT,FLYWHEEL_CHANNEL_RIGHT,(duty-7.7)/(10-7.7)*8*100);
}


void flywheel_right_setJmp(float duty)
{
/*	flywheel_right.pur_jmp = duty;
	flywheel_right.right.pwm2 = duty*100;
	Client_SET(flywheel_right.right);*/
}

/**
  * @brief  ����תƽ̨
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_right_setYaw(float yaw)
{
	flywheel_right.pur_yaw = yaw;
	RoboModule_SET_Position(YAW_ID_RIGHT,5000,yaw*100,YAW_MAXSPEED);
	//RoboModule_SET_Position(YAW_ID_RIGHT,5000,yaw*100,YAW_MAXSPEED);
}

/**
  * @brief  tim2�е��ã�������ʱ�Ȳ���
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_right_TIM()
{
	right_ms++;
	if(fly_count != 0)
		fly_count--;
}

/**
  * @brief ���n�η�
  *     
  * @note int n,	����
		float duty, ��ˢռ�ձ�
		float roll,	������
		float turn  ת��
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_right_flyn(int n, float duty, float pitch, float yaw)
{
	fly_n = n*2;
	
	flywheel_right.pur_duty = duty;
	flywheel_right.pur_pitch = pitch;
	flywheel_right.pur_yaw = yaw;
	flywheel_right.state = fly_r_finish;
	flywheel_right.fly_flag = true;
	right_ms = 0;
}

/*
	�����̬�Ƿ������λ
	����״̬ת��
*/
bool flywheel_right_check()
{
	static int flag = 1;
	if( fabs(ReturnData(PITCH_ID_RIGHT)->Position -flywheel_right.pur_pitch*100)<=30 && 
		fabs(ReturnData(YAW_ID_RIGHT)->Position -flywheel_right.pur_yaw*100)<=40)
		{
			if(flag == 1)
			{
				flag = 0;
				fly_count = 700;
				if(strategy.right[autorun.target_r] == 3)
					fly_count = 2000;
			}
			return true;
		}
	else{
		flag = 1;
		return false;
	}
}

void flywheel_right_fly1(){
	if(flywheel_right.state != r_fly ){
		fly_n = 2;
		flywheel_right_fly();
		flywheel_right_up(1);
		fly_count = 300;
		fly_n--;
		flywheel_right.state = r_fly;
	}
}

//̧����
void flywheel_right_up(int i)
{
	if(i == -1)
		flywheel_right.io[UP_RIGHT] = 1 - flywheel_right.io[UP_RIGHT];
	else if(flywheel_right.io[UP_RIGHT] != i){
		flywheel_right.io[UP_RIGHT] = i;
		set_IO(CLIENT_ID_RIGHT,flywheel_right.io);
	}
}

void flywheel_right_stop()
{
	flywheel_right_setBrushless(7.7);
	flywheel_right_setPitch(ReturnData(PITCH_ID_RIGHT)->Position/100.f);
	flywheel_right_setYaw(ReturnData(YAW_ID_RIGHT)->Position/100.f);
	//flywheel_right_setJmp(6);
}


void flywheel_right_yawZero()
{
	RoboModule_SET_Zero(YAW_ID_RIGHT);
	flywheel_right.pur_yaw = 0;
}

//pitch ͣ
void flywheel_right_pitchZero()
{
	RoboModule_SET_Zero(PITCH_ID_RIGHT);
	flywheel_right.pur_pitch = 0;
}

/**
  * @brief ���ṹ�ص���ʼλ��
  *     
  * @note
  *
  * @param
  *          
  * @retval 
  */
void flywheel_right_home()
{
	flywheel_right_setBrushless(7.7);
	flywheel_right_setPitch(0);
	flywheel_right_setYaw(0);
	//flywheel_right_setJmp(6);
	flywheel_right_up(0);
}

void flywheel_right_Set(){
	if(flywheel_right.state == fly_r_adj){
	flywheel_right_setPitch(flywheel_right.pur_pitch);
	flywheel_right_setYaw(flywheel_right.pur_yaw);
	flywheel_right_setBrushless(flywheel_right.pur_duty);}
}

/**
  * @brief main��ѭ���м��
  *     
  * @note
  *
  * @param
  *          
  * @retval 
  */
void flywheel_right_main()
{
	static int flag = 0;
	switch(flywheel_right.state)
	{
		case fly_r_ready:
			flywheel_right_setPitch(flywheel_right.pur_pitch);
			flywheel_right_setYaw(flywheel_right.pur_yaw);
			flywheel_right_setBrushless(flywheel_right.pur_duty);
			flywheel_right.state = fly_r_adj;
			flywheel_right.io[FLY_RIGHT] = 0;
			fly_count = 0;
			flywheel_right.io[UP_RIGHT] = 1;
			set_IO(CLIENT_ID_RIGHT,flywheel_right.io);
		case fly_r_adj:
			if(flywheel_right_check() && fly_count == 0 && autorun.state == pos_arrived)
			{
				if(handle_r == false && autorun.target_r == 0 && flag == 0)
				{
					fly_count = 300;
					flag = 1;
				}
				if(fly_count == 0)
				{
					if(debug_print)
					{
						USART_SendString(bluetooth,"msg: right switch:%d\n",right_ms);
						right_ms = 0;
					}
					flywheel_right.state = r_fly;
					flag = 0;
					if(fly_n == 0)
					{
						fly_count = 0;
						flywheel_right.state = fly_r_finish;
						flywheel_right.fly_flag = false;
						flag = 0;
					}else{
						USART_SendString(bluetooth,"msg:right fly!!\n");
						flywheel_right_fly();
						fly_count = 300;
						fly_n--;
					}
				}
			}
			break;
		case r_fly:
			if(fly_n%2 == 0)
			{
				if(fly_count <= 300)
					flywheel_right_up(1);
			}
			
			if(fly_count == 0)
			{
				if(fly_n == 0)
				{
					fly_count = 0;
					flywheel_right.state = fly_r_finish;
					flywheel_right.fly_flag = false;
				}else{
					flywheel_right_fly();
					if(fly_n%2 == 1){
						flywheel_right_up(0);
						fly_count = 700;
					}else
						fly_count = 300;
					fly_n--;
				}
			}
			break;
		case fly_r_finish:
			if(flywheel_right.fly_flag)
			{
				flywheel_right.state = fly_r_ready;
			}
			break;
	}
}
