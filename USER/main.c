#include "main.h" 
#include "sys.h"
#include "usart.h"
#include "switch.h"
#include "motorCtrl.h"
#include "digit.h"
#include "lcd.h"

int g_pos_x;
int g_pos_y;
float g_pos_ang;

bool g_stop_flag = false;

bool debug_print = false;

bool debug = false;

bool switch_side = false;

int ms = 0;

SwitchKey Sswitch;
SwitchKey Sdebug;

void TIM2_IRQHandler(void){
	if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) 
	{
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);//必须清除中断标志位否则一直中断
	}	
}


//-----------------草稿结束------------------------

int main(void)
{   
	u8 x=0;
	u16 lcd_id;		//存放LCD ID字符串
	char buff[50];
	
	SwitchKey switch13,switch12,switch15,switch14;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	
	rcc_config();
	gpio_config();
	delay_init(168);  //初始化延时函数
	nvic_config();
	usart_init(bluetooth,115200,true);
	cmd_init();
	EXTI_config();
	
	can_init();
	
	vega_init(&g_pos_x,&g_pos_y, &g_pos_ang);
	vega_reset();
	delay_ms(1000);
	
	TIM2_Init();
	
	fsmc_config();
	delay_ms(50);
 	lcd_init();
	delay_ms(50);
    lcd_id = lcd_reg_read(LCD_REG_0);
	
    lcd_clear(0x0000);
	sprintf(buff,"x     : %f",g_pos_x*0.0001 * 0.81);
	lcd_show_string(5,0,200,30,24,buff);
	sprintf(buff,"y     : %f",g_pos_y*0.0001 * 0.81);
	lcd_show_string(5,25,200,30,24,buff);
	sprintf(buff,"angle : %f",(g_pos_ang/180.f)*PI);
	lcd_show_string(5,50,200,30,24,buff);
	Digit_left_show(0);
	Digit_right_show(5);
	
	switch13.state = PBin(13);
	switch13.who = 's';
	switch12.state = PBin(12);
	switch15.state = PBin(15);
	switch14.state = PBin(14);
	switch14.who = 'd';
	if(PBin(13))
		lcd_show_string(5,75,200,30,24,"switch: blue");
	else
		lcd_show_string(5,75,200,30,24,"switch: red ");
	lcd_show_string(5,100,200,30,24,"home:true");
	
	if(PBin(14))
		lcd_show_string(5,125,200,30,24,"debug : true       ");
	else
		lcd_show_string(5,125,200,30,24,"debug : false      ");
	
	RoboModule_init();
	RoboModule_Add_Callback(databack,RoboModule_Feedback_Callback,PITCH_ID_LEFT,YAW_ID_LEFT,0);
	RoboModule_Add_Callback(databack,RoboModule_Feedback_Callback,PITCH_ID_RIGHT,YAW_ID_RIGHT,0);
	
	while(1){
		sprintf(buff,"x     : %f",g_pos_x*0.0001 * 0.81);
		lcd_show_string(5,0,200,30,24,buff);
		sprintf(buff,"y     : %f",g_pos_y*0.0001 * 0.81);
		lcd_show_string(5,25,200,30,24,buff);
		sprintf(buff,"angle : %f",(g_pos_ang/180.f)*PI);
		lcd_show_string(5,50,200,30,24,buff);
		if(home_flag)
			lcd_show_string(5,100,200,30,24,"home  : true ");
		else
			lcd_show_string(5,100,200,30,24,"home  : false");
		
		if(PBin(13) != switch13.state || PBin(14) != switch14.state)
		{
			delay_ms(10);
			if(PBin(13) != switch13.state)
			{
				switch_side = PBin(13);
				if(switch_side)
					lcd_show_string(5,75,200,30,24,"switch: blue     ");
				else
					lcd_show_string(5,75,200,30,24,"switch: red      ");
				switch13.state=PBin(13);
			}
			if(PBin(14) != switch14.state)
			{
				debug = PBin(14);
				if(debug)
					lcd_show_string(5,125,200,30,24,"debug : true       ");
				else
					lcd_show_string(5,125,200,30,24,"debug : false      ");
				switch14.state=PBin(14);
			}
			
		}
		
		sprintf(buff,"l:pitch:%6d yaw:%6d\n",ReturnData(PITCH_ID_LEFT)->Position,ReturnData(YAW_ID_LEFT)->Position);
		lcd_show_string(5,150,200,40,16,buff);
		sprintf(buff,"r:pitch:%6d yaw:%6d\n",ReturnData(PITCH_ID_RIGHT)->Position,ReturnData(YAW_ID_RIGHT)->Position);
		lcd_show_string(5,170,200,40,16,buff);	
		delay_ms(100);
	}
}
