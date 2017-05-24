#include "usart.h"
#include "configuration.h"
#include "motorCtrl.h"
#include "exti.h"

extern bool debug_print;

int wait_cnt=-1;

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET){//判断某个线上的中断是否发生
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0){ 
			home_flag = !home_flag;
		}
		EXTI_ClearITPendingBit(EXTI_Line5); //清除 LINE 上的中断标志位
	}else 
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET){//判断某个线上的中断是否发生
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0){ 
			
		}
		EXTI_ClearITPendingBit(EXTI_Line6); //清除 LINE 上的中断标志位
	}else
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET){//判断某个线上的中断是否发生
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0){ 
			if(home_flag)
				RoboModule_SET_Position(PITCH_ID_RIGHT,5000,ReturnData(PITCH_ID_RIGHT)->Position+4*100,0);
			else
				RoboModule_SET_Position(PITCH_ID_RIGHT,5000,ReturnData(PITCH_ID_RIGHT)->Position-2*100,0);
		}
		EXTI_ClearITPendingBit(EXTI_Line7); //清除 LINE 上的中断标志位
	}
}


void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET){//判断某个线上的中断是否发生
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0)
		{
			
		}
		EXTI_ClearITPendingBit(EXTI_Line3); //清除 LINE 上的中断标志位
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET){//判断某个线上的中断是否发生
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)
		{
			
		}
		EXTI_ClearITPendingBit(EXTI_Line4); //清除 LINE 上的中断标志位
	}
}
