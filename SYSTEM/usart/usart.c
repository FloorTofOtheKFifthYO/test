#include "usart.h"	
#include "math.h"


#define X_mid 125
#define Y_mid 125

u8  UART5_RX_BUF[USART_REC_LEN];
u16 UART5_RX_STA;         		
u8  USART3_RX_BUF[USART_REC_LEN];    
u16 USART3_RX_STA;


void usart_init(USART_TypeDef *USARTx, uint32_t USART_BaudRate,bool RX)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = USART_BaudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	if(RX){
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		USART_Init(USARTx, &USART_InitStructure); //��ʼ������x
		USART_Cmd(USARTx, ENABLE);  //ʹ�ܴ���x
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);//��������ж�
	}
	else{
		USART_InitStructure.USART_Mode = USART_Mode_Tx;
		USART_Init(USARTx, &USART_InitStructure); //��ʼ������x
		USART_Cmd(USARTx, ENABLE);  //ʹ�ܴ���x
	}
	
	
}

//��ʼ��IO ����1 
//bound:������
/*void usart_init(int *Hx,int *Hy){
   //GPIO�˿�����
	USART_InitTypeDef USART_InitStructure;
	
//////////////////////////////////////////////////////////////////////////////////////////	
	
	USART_InitStructure.USART_BaudRate = 115200;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
   
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
    USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
	USART_Init(UART5, &USART_InitStructure); //��ʼ������5
    USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���5
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3
		
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_InitStructure.USART_BaudRate = 115200;//����������
	USART_Init(UART4, &USART_InitStructure); //��ʼ������4
    USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���4
	x=Hx;y=Hy;
	ptrB=-1;
	ptrS=0;
}*/

void USART3_IRQHandler(void)                	
{
	u8 Res;	u8 tmp;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		Res =USART_ReceiveData(USART3);
	
	}
}



//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if _printf
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
_ttywrch(int ch)
{
ch = ch;
}
//�ض���fputc���� 

#endif




void USART_SendString(USART_TypeDef* USARTx, char *fmt, ...)
 {
	char buffer[STR_BUFFER_LEN+1];  // CMD_BUFFER_LEN�����Լ������
	u8 i = 0;
	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, STR_BUFFER_LEN+1, fmt, arg_ptr);
	USART_ClearFlag(USARTx,USART_FLAG_TXE);
	while ((i < STR_BUFFER_LEN) && buffer[i])
	{
		if(buffer[i] == '\n'){
			
			USART_SendData(USARTx,(u8)'\r');
			while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
			USART_SendData(USARTx,(u8)buffer[i++]);
		}else{
	    USART_SendData(USARTx, (u8) buffer[i++]);
		}
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
	}
	va_end(arg_ptr);
 } 


 
