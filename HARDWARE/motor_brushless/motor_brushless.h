#ifndef MOTOR_BRUSHLESS_H_
#define MOTOR_BRUSHLESS_H_

#include "sys.h"
#include "TIM.h"

/* ��ˢ���
 */
  
typedef struct{
	TIM_TypeDef* TIMx;	//��ʱ��
	u8 OC;				//ͨ����
	int GetTimx;		//���̰���ʹ�õĶ�ʱ����
	int *speed;
	float init_duty;	//��ʼռ�ձ�
}Brushless;
  
/**
  * @brief ��ʼ��,ֻ��ʼ����Ӧ�Ķ�ʱ����ͨ��
  *     
  * @note	������Ҫ��ַ����Ϊ��Ҫ�����̰崫�ص����ݽ��а�
  *
  * @param  motor_struct: ���ʵ��ָ��  
  *          
  * @retval void
  */
void Brushless_init(Brushless* motor_struct);

/**
  * @brief ����ռ�ձ�
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ�� 
			float duty:   ռ�ձ�
  *          
  * @retval void
  */
#define Brushless_duty(motor_struct, duty) \
	TIM_SetDuty(motor_struct.TIMx,duty,motor_struct.OC)


/**
  * @brief �����ٶ�,��ʱ��ʵ�֣����ڵ����PWM���ƣ�����ʱ��
  *        PID�㷨Ч������
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ�� 
			float duty:   ռ�ձ�
  *          
  * @retval void
  */
void Brushless_setSpeed(Brushless motor_struct,int speed);

#endif
