#ifndef MOTOR_USART_H_
#define MOTOR_USART_H_

#include "usart.h"

/**
 * ���ļ��Ǵ��ڿ��Ʋ��������һ��ģ��
 * ʹ�ø��ļ��еĽṹ����г�ʼ��
 * �ýṹ��Ӧ��Ϊʵ�������ڵ�������
*/

typedef struct
{
	USART_TypeDef* usartx;
	int id;		//�ڵ��
	float rate;	//���ڲ���
	
	int AC; 	//���ٶ� 0~30000
	int DEC; 	//���ٶ� 0~30000
	int SP; 	//����ٶ� 0~30000
	int MV;		//��С�ٶ� 0~30000
}motor_usart;

/**
  * @brief  ���°��սṹ���е�ֵ��λ�����������������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_reset(motor_usart motor_struct);

/**
  * @brief  ���ü��ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_AC(motor_usart motor_struct);

/**
  * @brief  ���ü��ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_DEC(motor_usart motor_struct);

/**
  * @brief  ������С�ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_MV(motor_usart motor_struct);

/**
  * @brief  ��������ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_SP(motor_usart motor_struct);

/*
 * ���һ��ʹ���ٶ�ģʽ��λ��ģʽ
 * ������Ҫ�����ӿڣ������ٶȺ�����λ�õĽӿ�
 * λ���ַ�Ϊ���λ�ú;���λ��
 *
**/

//�ٶ�
#define motor_usart_setspeed(motor_struct, speed) \
	USART_SendString(motor_struct.usartx,"%dv%d\r%dv%d\r%dv%d\r", \
	motor_struct.id, motor_struct.rate * (speed),motor_struct.id, motor_struct.rate * (speed),motor_struct.id, motor_struct.rate * (speed));
	
	
//���λ��
#define motor_usart_relpos(motor_struct, relpos) \
	USART_SendString(motor_struct.usartx,"%dLR%d\r", motor_struct.id, relpos); \
	USART_SendString(MOTOR_USARTx,"%dM\r%dM\r%dM\r",motor_struct.id,motor_struct.id,motor_struct.id);


//����λ��
#define motor_usart_abspos(motor_struct, abspos) \
	USART_SendString(motor_struct.usartx,"%dLA%d\r", motor_struct.id, abspos); \
	USART_SendString(motor_struct.usartx,"%dM\r%dM\r%dM\r",motor_struct.id,motor_struct.id,motor_struct.id);

#endif

