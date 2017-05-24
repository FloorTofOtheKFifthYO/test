#ifndef _STEP_H
#define _STEP_H

#include <stdbool.h>

/**
  * @brief  ��ʼ���������1
  *     
  * @note  �ڲ���ʼ����TIM13 ʹ�ܶ�0ʹ�� ����1
  *
  * @param 
  *          
  * @retval 
  */
void Step1_Init(void);

/**
  * @brief  �������1��ǰλ��
  *     
  * @note  
  *
  * @param 
  *          
  * @retval int λ��
  */
int Step1_get_count(void);

/**
  * @brief  ���ò������1Ԥ��λ��
  *     
  * @note  
  *
  * @param int λ��
  *          
  * @retval 
  */
void Step1_moveto(int count);

/**
  * @brief  ���ò������1�ٶ�
  *     
  * @note  ���ö�ʱ��Ƶ��
  *
  * @param int speed Ƶ��
  *          
  * @retval 
  */
void Step1_set_speed(int speed);

/**
  * @brief  ��ѭ���е���
  *     
  * @note  
  *
  * @param 
  *          
  * @retval 
  */
void Step_check(void);

void Step1_stop();

/**
  * @brief  ��ʼ���������2
  *     
  * @note  �ڲ���ʼ����TIM14 ʹ�ܶ�0ʹ�� ����1
  *
  * @param 
  *          
  * @retval 
  */
void Step2_Init(void);

/**
  * @brief  �������1��ǰλ��
  *     
  * @note  
  *
  * @param 
  *          
  * @retval int λ��
  */
int Step2_get_count(void);

/**
  * @brief  ���ò������2Ԥ��λ��
  *     
  * @note  
  *
  * @param int λ��
  *          
  * @retval 
  */
void Step2_moveto(int count);

/**
  * @brief  ���ò������2�ٶ�
  *     
  * @note  ���ö�ʱ��Ƶ��
  *
  * @param int speed Ƶ��
  *          
  * @retval 
  */
void Step2_set_speed(int speed);

void Step2_stop();

/**
  * @brief  ���ò������1״̬
  *     
  * @note
  *
  * @param
  *          
  * @retval true��ʾ����Ԥ��λ��
  */
bool Step1_state();


/**
  * @brief  ���ò������2״̬
  *     
  * @note
  *
  * @param
  *          
  * @retval true��ʾ����Ԥ��λ��
  */
bool Step2_state();

#endif
