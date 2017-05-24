#include "configuration.h"

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef exti_init_structure;

u8 LEFT_RIGHT = 0;//�쳡Ϊ0������Ϊ1
u8 OPEN_Hander = 0;

/*
 *��������void GPIO_Configuration(uint16_t GPIO_Pin,
                        GPIOMode_TypeDef  GPIO_Mode,
                        GPIOSpeed_TypeDef GPIO_Speed,
                        GPIOOType_TypeDef GPIO_OType,
                        GPIOPuPd_TypeDef GPIO_PuPd,
                        GPIO_TypeDef* GPIOx)
 * ���ܣ�IO�ڳ�ʼ��
 * ������uint16_t GPIO_Pin, 			�ܽź�
        GPIOMode_TypeDef  GPIO_Mode,	���ģʽ
        GPIOSpeed_TypeDef GPIO_Speed,	�ٶ�
        GPIOOType_TypeDef GPIO_OType,	407   GPIO_OType_PP Ϊ����   GPIO_OType_OD Ϊ��©
        GPIOPuPd_TypeDef GPIO_PuPd,		GPIO_PuPd_DOWN GPIO_PuPd_UP GPIO_PuPd_NOPULL
        GPIO_TypeDef* GPIOx				�ܽ����
 * ����ֵ��
 */
void GPIO_Configuration(uint16_t GPIO_Pin,GPIOMode_TypeDef  GPIO_Mode,GPIOOType_TypeDef GPIO_OType,
	GPIOSpeed_TypeDef GPIO_Speed,GPIOPuPd_TypeDef GPIO_PuPd,GPIO_TypeDef* GPIOx)
{
 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;                       //�ܽź� 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;                     //ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;                  
  	GPIO_Init(GPIOx, &GPIO_InitStructure);                        //�ܽ���� 
}


/*
 *��������void NVIC_Configuration(uint8_t NVIC_IRQChannel,
				uint8_t NVIC_IRQChannelPreemptionPriority,
				uint8_t NVIC_IRQChannelSubPriority,
                FunctionalState NVIC_IRQChannelCmd)
 * ���ܣ��жϷ����ʼ��
 * ������uint8_t NVIC_IRQChannel, 					 	ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
   		uint8_t NVIC_IRQChannelPreemptionPriority,		��ռ���ȼ�
		uint8_t NVIC_IRQChannelSubPriority				�����ȼ�
        FunctionalState NVIC_IRQChannelCmd              ENABLE DISABLE
 * ����ֵ��
 */
void NVIC_Configuration(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,
	uint8_t NVIC_IRQChannelSubPriority,FunctionalState NVIC_IRQChannelCmd)
{	
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =NVIC_IRQChannelSubPriority;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;			
	NVIC_Init(&NVIC_InitStructure);
}



void system_clk_set(void){ 
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
 
    RCC_HSEConfig(RCC_HSE_ON );   //���ⲿʱ��
 
    HSEStartUpStatus = RCC_WaitForHSEStartUp();  //�ȴ��ⲿʱ�Ӵ����ȶ�
 
  if(HSEStartUpStatus == SUCCESS)     
  {
    FLASH_SetLatency(FLASH_Latency_5);   
    FLASH_PrefetchBufferCmd(ENABLE);       //flashʱ�ӵ��������  
    RCC_PLLCmd(DISABLE);  //����PLL֮ǰ��Ҫ�ر�PLL
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   //HCLK��Ƶ
    RCC_PCLK2Config(RCC_HCLK_Div1);   //PCLK2��Ƶ
    RCC_PCLK1Config(RCC_HCLK_Div4);    //PCLK1��Ƶ
    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);    //sysclk = 168MHZ  ,,���㹫ʽ�μ������ֲ�
    RCC_PLLCmd(ENABLE); //ʹ��PLL
 
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){      //�ȴ�����ֱ��PLLʹ�����
    
    }
 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //ѡ��PLLʱ��Ϊϵͳʱ��
 
    while(RCC_GetSYSCLKSource() != 0x08)       //�ȴ�����PLLʱ�����ó�ϵͳʱ�����
       { 
       }
     }
    #if(__FPU_PRESENT == 1)&&(__FPU_USED == 1)
			SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  //����FPU
		#endif

}
 
 void rcc_config(){
	//RCC_DeInit();			//��ʼ��Ϊȱʡֵ
	
	//system_clk_set();
	//RCC_GetClocksFreq(&RCC_ClockFreq);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
                                                            
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	 //ʹ��USART1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//ʹ��USART3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);	//ʹ��USART3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);   //ʹ��UART5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);   //ʹ��syscfgʱ�ӣ������ⲿ�ж�
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
}

void gpio_config(void)
{
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);   //?
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);   //?
	//GPIO_PinRemapConfig(GPIO_Remap_USART3,ENABLE);   //?
//	GPIO_Configuration(GPIO_Pin_9 | GPIO_Pin_10,GPIO_Mode_AF,
//	                   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOA);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
//	
//	GPIO_Configuration(GPIO_Pin_5 | GPIO_Pin_6,GPIO_Mode_AF,
//	                   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOD);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); 
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); 
//	
//	GPIO_Configuration(GPIO_Pin_10 | GPIO_Pin_11 ,
//					   GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOB);
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOD8����ΪUSART3
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOD9����ΪUSART3
//	
//	GPIO_Configuration(GPIO_Pin_10 | GPIO_Pin_11,GPIO_Mode_AF,
//	                   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOC);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOB6����ΪUSART4
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOB7����ΪUSART4
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOC12����ΪUSART5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOD2����ΪUSART5
	GPIO_Configuration(GPIO_Pin_12,GPIO_Mode_AF,
					   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOC);
	GPIO_Configuration(GPIO_Pin_2,GPIO_Mode_AF,
					   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOD);
	
//	GPIO_Configuration(GPIO_Pin_6 | GPIO_Pin_7,GPIO_Mode_AF,
//	                   GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOC);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOC6����ΪUSART6
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOC7����ΪUSART6
//----------------------------USART---------------------------------------------------------------------------------------------	

//	GPIO_Configuration(GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,
//	                   GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_100MHz,GPIO_PuPd_UP,GPIOB);
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI2); 
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_SPI2); 
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_SPI2);
//----------------------------SPI2---------------------------------------------------------------------------------------------
	
//	GPIO_Configuration(GPIO_Pin_12 | GPIO_Pin_13,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOD);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); 	
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
//	GPIO_Configuration(GPIO_Pin_6 | GPIO_Pin_7,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOA);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); 	
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3); 
/*	GPIO_Configuration(GPIO_Pin_0 | GPIO_Pin_1,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOA);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5); 	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5); */
//----------------------------��������---------------------------------------------------------------------------------------------

	GPIO_Configuration(GPIO_Pin_3,GPIO_Mode_IN,GPIO_OType_OD,GPIO_Speed_100MHz,GPIO_PuPd_UP,GPIOB);
	GPIO_Configuration(GPIO_Pin_5,GPIO_Mode_IN,GPIO_OType_OD,GPIO_Speed_100MHz,GPIO_PuPd_UP,GPIOB);
	GPIO_Configuration(GPIO_Pin_7 | GPIO_Pin_6 |GPIO_Pin_4,GPIO_Mode_IN,GPIO_OType_OD,GPIO_Speed_100MHz,GPIO_PuPd_UP,GPIOB);
//----------------------------����---------------------------------------------------------------------------------------------
	
//	GPIO_Configuration(GPIO_Pin_5, GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOE);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
//	GPIO_Configuration(GPIO_Pin_1|GPIO_Pin_0, GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOF);
//	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
//	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
//----------------------------PWM---------------------------------------------------------------------------------------------

//	GPIO_Configuration(GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_DOWN,GPIOG);
//----------------------------�̵���-----------------------------------------------------------------------------	

//	GPIO_Configuration(GPIO_Pin_1|GPIO_Pin_4, GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_UP,GPIOD);
//----------------------------LED-----------------------------------------------------------------------------	

	GPIO_Configuration(GPIO_Pin_10 | GPIO_Pin_11,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_100MHz,GPIO_PuPd_NOPULL,GPIOC);
	GPIO_Configuration(GPIO_Pin_15 | GPIO_Pin_15,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_100MHz,GPIO_PuPd_NOPULL,GPIOA);
	GPIO_Configuration(GPIO_Pin_1 | GPIO_Pin_0,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_100MHz,GPIO_PuPd_NOPULL,GPIOE);
	GPIO_Configuration(GPIO_Pin_8 | GPIO_Pin_9,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_Speed_100MHz,GPIO_PuPd_NOPULL,GPIOB);
//----------------------------�����-----------------------------------------------------------------------------	

	GPIO_Configuration(GPIO_Pin_13 | GPIO_Pin_12 |GPIO_Pin_15 | GPIO_Pin_14,GPIO_Mode_IN,GPIO_OType_OD,GPIO_Speed_100MHz,GPIO_PuPd_UP,GPIOB);
//----------------------------���뿪��-----------------------------------------------------------------------------	

}

/*
 * ��������void EXTI_Configuration(uint32_t EXTI_Line,
                EXTIMode_TypeDef EXTI_Mode,
                EXTITrigger_TypeDef EXTI_Trigger,
                FunctionalState EXTI_LineCmd)
 * ���ܣ��ⲿ�жϳ�ʼ��
 * ������uint32_t EXTI_Line,               �ж��ߣ�EXTI_Line0~EXTI_Line15
        EXTIMode_TypeDef EXTI_Mode,         EXTI_Mode_Interrupt,EXTI_Mode_Event
        EXTITrigger_TypeDef EXTI_Trigger,   EXTI_Trigger_Rising,EXTI_Trigger_Falling, EXTI_Trigger_Rising_Falling
        FunctionalState EXTI_LineCmd        ENABLE DISABLE
 * ���أ�
 */
void EXTI_Configuration(uint32_t EXTI_Line,
                EXTIMode_TypeDef EXTI_Mode,
                EXTITrigger_TypeDef EXTI_Trigger,
                FunctionalState EXTI_LineCmd)
{
    exti_init_structure.EXTI_Line = EXTI_Line;
    exti_init_structure.EXTI_Mode = EXTI_Mode;
    exti_init_structure.EXTI_Trigger = EXTI_Trigger;
    exti_init_structure.EXTI_LineCmd = EXTI_LineCmd;
    EXTI_Init(&exti_init_structure);
}

void EXTI_config()
{
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
	EXTI_Configuration(EXTI_Line3,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_Configuration(EXTI_Line4,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_Configuration(EXTI_Line5,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_Configuration(EXTI_Line6,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_Configuration(EXTI_Line7,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_ClearITPendingBit(EXTI_Line3); 
	EXTI_ClearITPendingBit(EXTI_Line4); 
	EXTI_ClearITPendingBit(EXTI_Line5); 
	EXTI_ClearITPendingBit(EXTI_Line6); 
	EXTI_ClearITPendingBit(EXTI_Line7); 
}

void nvic_config()
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2 2:2   ��ռ����Ӧ    �� 3��:3��
	
	NVIC_Configuration(UART5_IRQn,2,3,ENABLE);
//	NVIC_Configuration(USART1_IRQn,2,3,ENABLE);
	NVIC_Configuration(USART6_IRQn,2,3,ENABLE);
//	NVIC_Configuration(USART3_IRQn,2,3,ENABLE);
	NVIC_Configuration(TIM2_IRQn,0,2,ENABLE);
	NVIC_Configuration(TIM8_UP_TIM13_IRQn,1,1,ENABLE);
//	NVIC_Configuration(TIM8_TRG_COM_TIM14_IRQn,1,1,ENABLE);
//	NVIC_Configuration(TIM5_IRQn,1,1,ENABLE);
	
	NVIC_Configuration(EXTI3_IRQn, 0, 0, ENABLE);
	NVIC_Configuration(EXTI4_IRQn, 0, 0, ENABLE);
	NVIC_Configuration(EXTI9_5_IRQn, 0, 0, ENABLE);
	

	
}



