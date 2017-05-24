#ifndef _PUTTER_H_
#define _PUTTER_H_
#include "sys.h"
#include <stdbool.h>
#include "motor_usart.h"

typedef struct{
	motor_usart motor;
	int GetTimx;		//���̰���ʹ�õĶ�ʱ����
	int SP;				//����ٶ�
	
	int *position;		//λ��
	float pur_pos;		//Ԥ��λ��
	float d_last;
	int d_rate;
	int dd_rate;
	bool putter_flag;
	int cnt;
}putter;

/**
  * @brief ��ʼ��,�����̰��Ӧ�Ķ�ʱ����
  *     
  * @note	������Ҫ��ַ����Ϊ��Ҫ�����̰崫�ص����ݽ��а�
  *
  * @param  putter_struct: ���Ƹ�ʵ��ָ��  
  *          
  * @retval void
  */
void putter_init(putter *putter_struct);

/**
  * @brief main��������ѯ����
  *     
  * @note	
  *
  * @param  putter_struct: ���Ƹ�ʵ��  
  *          
  * @retval void
  */
void putter_main(putter putter_struct);

/**
  * @brief �Ƶ��Ƹ�
  *     
  * @note	
  *
  * @param  motor_struct: ���Ƹ�ʵ��ָ�룬
			floatpur_pos   ϣ�������λ��
  *          
  * @retval void
  */
void putter_moveto(putter *putter_struct,float pur_pos);
#endif
