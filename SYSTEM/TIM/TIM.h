#ifndef __TIM_H
#define __TIM_H
#include "configuration.h"
 
/**
  * @brief  ʱ�ӳ�ʼ��
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧʱ��
  *			uint16_t TIM_Prescaler 	��Ƶ��
  *			uint32_t TIM_Period 	װ��ֵ
  *         bool IT					�Ƿ��ж�
  * @retval 
  */
void TIM_Init(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period, bool IT);


/**
  * @brief  ��Ӧͨ�����PWM
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧʱ��
  *			float duty				ռ�ձ�
  *         int OC					ͨ����
  * @retval 
  */
void TIM_PWM_Init(TIM_TypeDef *TIMx, float duty, int OC);

/**
  * @brief  ��Ӧͨ������PWMռ�ձ�
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧ��ʱ��
  *			float duty				ռ�ձ�
  *         int OC					ͨ����
  * @retval 
  */
void TIM_SetDuty(TIM_TypeDef* TIMx,float duty, int OC);

void TIM13_Init();
void TIM14_Init();
void TIM2_Init();
void TIM9_Init();

#endif

