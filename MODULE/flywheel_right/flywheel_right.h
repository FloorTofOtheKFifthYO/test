#ifndef _FLYWHEEL_RIGHT_H_
#define _FLYWHEEL_RIGHT_H_
#include "sys.h"
#include <stdbool.h>
#include "configuration.h"
#include "motorCtrl.h"
#include "client.h"

/*
��������ַ��������Ҫ��������,ʵ�����ÿ�configuration.h
#define FLYWHEEL_RIGHT
#define CLIENT_ID_RIGHT 	0x31
#define TURN_ID_RIGHT		0x08
#define PITCH_ID_RIGHT		0x09
#define YAW_ID_RIGHT		0x05
#define FLY_RIGHT			2
#define UP_RIGHT			3
*/

#ifndef FLYWHEEL_RIGHT
#error δ�����ҷ���
#endif

typedef struct
{
	//��Ա
	
	//״̬
	enum {fly_r_ready, fly_r_adj, r_fly, fly_r_finish} state;
	
	//����
	bool fly_flag;	//�������
	float pur_duty;	
	float pur_turn;
	float pur_pitch;
	float pur_yaw;
	float pur_jmp;
	u8 io[3];
}Flywheel_right;

extern Flywheel_right flywheel_right;

/**
  * @brief  ��ʼ��
  *     
  * @note
  *
  * @param 
  *          
  * @retval 
  */
void flywheel_right_init();

/**
  * @brief  �ĸ�����
  *     
  * @note
  *
  * @param ������
  *          
  * @retval 
  */
void flywheel_right_setPitch(float pitch);


/**
  * @brief  ����ˢ
  *     
  * @note
  *
  * @param ռ�ձ�
  *          
  * @retval 
  */
void flywheel_right_setBrushless(float duty);

	

void flywheel_right_setJmp(float duty);	

/**
  * @brief  ����תƽ̨
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_right_setYaw(float yaw);

void flywheel_right_fly();

/**
  * @brief  tim2�е��ã�������ʱ�Ȳ���
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_right_TIM();

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
void flywheel_right_flyn(int n, float duty, float pitch, float yaw);
/**
  * @brief main��ѭ���м��
  *     
  * @note
  *
  * @param
  *          
  * @retval 
  */
void flywheel_right_main();

/*
	�����̬�Ƿ������λ
	����״̬ת��
*/
bool flywheel_right_check();

/*����ͣ*/
void flywheel_right_stop();

void flywheel_right_home();

void flywheel_right_pitchZero();

void flywheel_right_yawZero();

//����һ������
void flywheel_right_fly1();

void flywheel_right_up(int i);

void flywheel_right_Set()

#endif
