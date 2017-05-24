#ifndef _FLYWHEEL_LEFT_H_
#define _FLYWHEEL_LEFT_H_
#include "sys.h"
#include <stdbool.h>
#include "configuration.h"
#include "motorCtrl.h"
#include "client.h"

/*
��������ַ��������Ҫ��������
#define FLYWHEEL_LEFT
#define FLYWHEEL_ID_LEFT 	0x20
#define CLIENT_ID_LEFT 		0x30
#define PITCH_ID_LEFT		0x04
#define YAW_ID_LEFT			0x06
#define FLY_LEFT			2
*/

#ifndef FLYWHEEL_LEFT
#error δ���������
#endif

typedef struct
{
	//״̬
	enum {fly_ready, fly_adj, fly,fly_l_finish} state;
	
	//����
	bool fly_flag;	//�������

	float pur_duty;	
	float pur_pitch;
	float pur_yaw;
	float pur_jmp;
	u8 fly_relay;
	u8 up_relay;
	
	u8 io[3];
}Flywheel_left;

extern Flywheel_left flywheel_left;

/**
  * @brief  ��ʼ��
  *     
  * @note
  *
  * @param 
  *          
  * @retval 
  */
void flywheel_left_init();

/**
  * @brief  �ĸ�����
  *     
  * @note
  *
  * @param ������
  *          
  * @retval 
  */
void flywheel_left_setPitch(float pitch);


/**
  * @brief  ����ˢ
  *     
  * @note
  *
  * @param ռ�ձ�
  *          
  * @retval 
  */
void flywheel_left_setBrushless(float duty);

	

void flywheel_left_setJmp(float duty);	

/**
  * @brief  ����תƽ̨
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_left_setYaw(float yaw);

void flywheel_left_fly();

void flywheel_left_Set();

/**
  * @brief  tim2�е��ã�������ʱ�Ȳ���
  *     
  * @note
  *
  * @param ��תƽ̨
  *          
  * @retval 
  */
void flywheel_left_TIM();

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
void flywheel_left_flyn(int n, float duty, float pitch, float yaw);

/**
  * @brief main��ѭ���м��
  *     
  * @note
  *
  * @param
  *          
  * @retval 
  */
void flywheel_left_main();

/*
	�����̬�Ƿ������λ
	����״̬ת��
*/
bool flywheel_left_check();

/*����ͣ*/
void flywheel_left_stop();

void flywheel_left_home();

void flywheel_left_pitchZero();

void flywheel_left_yawZero();

//����һ������
void flywheel_left_fly1();

void flywheel_left_up(int i);

#endif
