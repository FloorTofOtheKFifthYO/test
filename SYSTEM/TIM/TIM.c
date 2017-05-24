#include "TIM.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_ICInitTypeDef   TIM_ICInitStructure;

/**
  * @brief  ʱ�ӳ�ʼ��
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧʱ��
  *			uint16_t TIM_Prescaler 	��Ƶ��
  *			uint32_t TIM_Period 	װ��ֵ
  *         bool IT					�Ƿ��ж�
  * @retval 
  */
void TIM_Init(TIM_TypeDef *TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period, bool IT)
{
	TIM_DeInit(TIMx);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler;  //    
	TIM_TimeBaseStructure.TIM_Period = TIM_Period;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //������ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// ����  
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	if(IT){
		TIM_ClearFlag(TIMx, TIM_FLAG_Update);
		TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
	}
	TIM_Cmd(TIMx, ENABLE);
}

/**
  * @brief  ��Ӧͨ�����PWM
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧʱ��
  *			float duty				ռ�ձ�
  *         int OC					ͨ����
  * @retval 
  */
void TIM_PWM_Init(TIM_TypeDef *TIMx, float duty, int OC)
{
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = (int)(duty*(TIMx->ARR+1)) - 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
	
	switch(OC)
	{
		case 1:
			TIM_OC1Init(TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������OC1
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
			break;
		case 2:
			TIM_OC2Init(TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������OC2
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
			break;
		case 3:
			TIM_OC3Init(TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������OC3
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���
			break;
		case 4:
			TIM_OC4Init(TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������OC4
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���
			break;
		default:
			break;
	}
	TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPEʹ�� 
	TIM_Cmd(TIMx, ENABLE);
}

/**
  * @brief  ��Ӧͨ������PWMռ�ձ�
  *
  * @param 	TIM_TypeDef *TIMx 		��Ӧ��ʱ��
  *			float duty				ռ�ձ�
  *         int OC					ͨ����
  * @retval 
  */
void TIM_SetDuty(TIM_TypeDef* TIMx,float duty, int OC)
{
	switch(OC)
	{
		case 1:
			TIM_SetCompare1(TIMx, (int)((TIMx->ARR + 1) * duty)-1);
			break;
		case 2:
			TIM_SetCompare2(TIMx, (int)((TIMx->ARR + 1) * duty)-1);
			break;
		case 3:
			TIM_SetCompare3(TIMx, (int)((TIMx->ARR + 1) * duty)-1);
			break;
		case 4:
			TIM_SetCompare4(TIMx, (int)((TIMx->ARR + 1) * duty)-1);
			break;
		default:
			break;
	}
}

void TIM2_Init()        //1ms	��ʱ
{
	/*TIM2*/
	TIM_Init(TIM2,42000-1,1,true);
}

void TIM9_Init()  //��ˢ���PWM���
{	
	TIM_Init(TIM9,168-1,20000-1,false);
	TIM_PWM_Init(TIM9,0.077,1);
	//TIM_PWM_Init(TIM9,0.052,2);
}

void TIM13_Init(void)
{
	TIM_Init(TIM13,84-1,500-1,true);
	TIM_PWM_Init(TIM13,0.5,1);
	TIM_ClearFlag(TIM13, TIM_FLAG_Update);
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM13, ENABLE);	
	TIM13->CCER &= ~TIM_CCER_CC1E;
}

void TIM14_Init(void)
{
	TIM_Init(TIM14,84-1,1000-1,true);
	TIM_PWM_Init(TIM14,0.5,1);
	TIM14->CCER &= ~TIM_CCER_CC1E;
}

