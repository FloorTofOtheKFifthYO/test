#ifndef _UNDERPAN_H_
#define _UNDERPAN_H_
#include "sys.h"
#include <stdbool.h>
#include "configuration.h"

#define CHASSIS_FIRST_RUN 0
#define CHASSIS_FLASH_SETOR FLASH_Sector_6 //  ����6
#define CHASSIS_FLASH_ADDR_START ((uint32_t)0x08040000)
#define CHASSIS_FLASH_ADDR_END ((uint32_t)0x0805FFFF)

/*Ӧ�����
	#ifndef CHASSIS
	#define CHASSIS

	#define MOTOR0_ID 0x0A
	#define MOTOR1_ID 0x0B
	#define MOTOR2_ID 0x0C

	#endif
*/
#ifndef CHASSIS
#error δ�������
#endif

typedef struct 
{
	float X;
	float Y;
	float ANG;
}POSITION;

typedef struct
{
	//ȫ����λ���ص�����
	int g_vega_pos_x; 
	int g_vega_pos_y;   
	float g_vega_angle;
	
	float radar_theta;
	float radar_distance;
	
	float pos_x,pos_y;
	float angle;
	
	//״̬
	enum {car_stop, car_running, car_ready} car_state;//�����˶�״̬
	
	//����
	POSITION END, START;
	
	//����
	float Angle_radium;//ͣ�Ƕȷ�Χ
	int Angle_speed;
	float factor;
	float Move_radium;
	int Move_speed;
	int Speed_max;
	int Speed_min;
	float Start_distance;
	float xfactor;
} Chassis;

extern Chassis chassis;

/** ���̳�ʼ��
  * ����ȫ����λ�ĳ�ʼ��
  *
  */
void chassis_init(void);

/**�������
�ɹ�����1��������-1��-2
  */
int chassis_save();

//��ѭ����ѯ����
void chassis_update();

/**��ѭ�����ֱ�����
  *������float directoion 	�����
  *		int speed			�ٶ�
  *�����ٶ��Ƿ�Ϊ0����Ϊ0����ֻ��һ��
  */
void chassis_handle(float directoion, int speed);

/** ��ѭ�����Զ��ܵ��״̬ת�ƺ���
  * ͨ����chassis.END������Ŀ�ĵ�
  */
void chassis_auto();

//stop
void chassis_stop();


void chassis_param_print();


#endif
