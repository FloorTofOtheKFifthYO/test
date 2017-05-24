#include "sys.h"
#include "usart.h"
#include "motor_usart.h"
#include <assert.h>

/**
 * ���ļ��Ǵ��ڿ��Ʋ��������һ��ģ��
 * ʹ��.h�ļ��еĽṹ����г�ʼ��
 * �ýṹ��Ӧ��Ϊʵ�������ڵ�������
*/

/**
  * @brief  ���°��սṹ���е�ֵ��λ�����������������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
  
void motor_usart_reset(motor_usart motor_struct)
{
	assert(motor_struct.AC>=0 && motor_struct.AC<=30000);
	assert(motor_struct.DEC>=0 && motor_struct.DEC<=30000);
	assert(motor_struct.MV>=0 && motor_struct.MV<=30000);
	assert(motor_struct.SP>=0 && motor_struct.SP<=30000);
	USART_SendString(motor_struct.usartx,"%dAC%d\r%dDEC%d\r%dMV\r%dSP%d\rEEPSAV\r",motor_struct.id,motor_struct.AC,
	motor_struct.id,motor_struct.DEC,motor_struct.id,motor_struct.MV,motor_struct.id,motor_struct.SP);
}


/**
  * @brief  ���ü��ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_AC(motor_usart motor_struct)
{
	assert(motor_struct.AC>=0 && motor_struct.AC<=30000);
	USART_SendString(motor_struct.usartx,"%dAC%d\rEEPSAV\r",motor_struct.id,motor_struct.AC);
}

/**
  * @brief  ���ü��ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_DEC(motor_usart motor_struct)
{
	assert(motor_struct.DEC>=0 && motor_struct.DEC<=30000);
	USART_SendString(motor_struct.usartx,"%dDEC%d\rEEPSAV\r",motor_struct.id,motor_struct.DEC);
}

/**
  * @brief  ������С�ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_MV(motor_usart motor_struct)
{
	assert(motor_struct.MV>=0 && motor_struct.MV<=30000);
	USART_SendString(motor_struct.usartx,"%dMV%d\rEEPSAV\r",motor_struct.id,motor_struct.MV);
}

/**
  * @brief  ��������ٶȣ������浽flash
  *     
  * @note	
  *
  * @param  motor_struct: ���ʵ��  
  *          
  * @retval void
  */
void motor_usart_SP(motor_usart motor_struct)
{
	assert(motor_struct.SP>=0 && motor_struct.SP<=30000);
	USART_SendString(motor_struct.usartx,"%dSP%d\rEEPSAV\r",motor_struct.id,motor_struct.SP);
}