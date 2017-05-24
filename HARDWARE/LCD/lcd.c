/****************************************
2016/2/27  ������ILI9341��ʾ���Ĵ���
****************************************/


#include "lcd.h"
#include "FONT.H"
#include "configuration.h"
#include "delay.h"


u16 g_lcd_height,g_lcd_width;
u16 g_lcd_dir;
u16 lcd_id;



//LCD�Ĵ���ֵ������
u16 lcd_reg_read(u16 lcd_reg_addr){
    LCD->LCD_REG = lcd_reg_addr;

    return (LCD->LCD_RAM);
}
//LCD�Ĵ��ֵд����
void lcd_reg_write(u16 lcd_reg_addr,u16 lcd_reg_data){
    LCD->LCD_REG = lcd_reg_addr;
    LCD->LCD_RAM = lcd_reg_data;

}

void lcd_wr_reg(vu16 regval){   
		regval=regval;		//ʹ��-O2�Ż���ʱ��,����������ʱ
		LCD->LCD_REG=regval;//д��Ҫд�ļĴ������	 
}
//дLCD����
//data:Ҫд���ֵ
void lcd_wr_data(vu16 data){	  
		data=data;			//ʹ��-O2�Ż���ʱ��,����������ʱ
		LCD->LCD_RAM=data;		 
}

u16 lcd_rd_data(void){
		vu16 ram;  //��ֹ���Ż�
		ram = LCD->LCD_RAM;
		return ram;
}

void lcd_init(){
	u32 gpio_temp;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	//������������D0 D1:PD14 PD15    D2  D3:PD0  PD1   D4 ~ D12 :PE7 ~ PE15 
    //D13 D14 D15:PD12  PD13  PD11
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);   //D0
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);    //D1
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);     //D2
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);     //D3
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);     //D4
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);     //D5
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);     //D6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);     //D7
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);     //D8
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);     //D9
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);      //D10
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);      //D11
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);      //D12
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);      //D13
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);       //D14
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);      //D15

    gpio_temp = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_11|
                GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Configuration(gpio_temp,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOD);
    gpio_temp = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Configuration(gpio_temp,GPIO_Mode_AF, GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOE);

    //LCD_CS(FSMC_NE4):PG12 RD(FSMC_NOE):PD4 WR(FSMC_NWE):PD5   RS(FSMC_A6):PF12
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FSMC);  
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);  
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);  
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);  


  GPIO_Configuration(GPIO_Pin_12,GPIO_Mode_AF, GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOG);
  GPIO_Configuration(GPIO_Pin_4|GPIO_Pin_5,GPIO_Mode_AF, GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOD);
  GPIO_Configuration(GPIO_Pin_12,GPIO_Mode_AF, GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOF);
	//LCD��������  PD10
	GPIO_Configuration(GPIO_Pin_10,GPIO_Mode_OUT, GPIO_OType_PP,GPIO_Speed_50MHz,GPIO_PuPd_NOPULL,GPIOD);
	
	
    lcd_id = lcd_reg_read(0x0000);  //��ȡLCD��ID�ţ�������Ӧ�ĳ�ʼ��
	
	if(lcd_id==0X9300 || lcd_id == 0){//��Ϊ9341��δ����λ������»ᱻ����9300	
 		//����9341 ID�Ķ�ȡ		
		lcd_wr_reg(0XD3);				   
		lcd_id=lcd_rd_data();	//dummy read 	
 		lcd_id=lcd_rd_data();	//����0X00
  	lcd_id=lcd_rd_data();   	//��ȡ93								   
 		lcd_id<<=8;
		lcd_id|=lcd_rd_data();  	//��ȡ41 	   			   

	} 
	
		if(lcd_id == 0X9341||lcd_id == 0X5310||lcd_id == 0X5510||lcd_id == 0X1963){//������⼸��IC,������WRʱ��Ϊ���
		
				//��������дʱ����ƼĴ�����ʱ��   	 							    
				FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
				FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//���ݱ���ʱ������
				FSMC_Bank1E->BWTR[6]|=3<<0;		//��ַ����ʱ��(ADDSET)Ϊ3��HCLK =18ns  	 
				FSMC_Bank1E->BWTR[6]|=2<<8; 	//���ݱ���ʱ��(DATAST)Ϊ6ns*3��HCLK=18ns
		}
		else if(lcd_id == 0X6804||lcd_id == 0XC505){	//6804/C505�ٶ��ϲ�ȥ,�ý���
		
				//��������дʱ����ƼĴ�����ʱ��   	 							    
				FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
				FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//���ݱ���ʱ������
				FSMC_Bank1E->BWTR[6]|=10<<0;	//��ַ����ʱ��(ADDSET)Ϊ10��HCLK =60ns  	 
				FSMC_Bank1E->BWTR[6]|=12<<8; 	//���ݱ���ʱ��(DATAST)Ϊ6ns*13��HCLK=78ns
		}

    if(lcd_id == 0x9325){
						lcd_reg_write(0x00E5,0x78F0); 
						lcd_reg_write(0x0001,0x0100); 
						lcd_reg_write(0x0002,0x0700); 
						lcd_reg_write(0x0003,0x1020);   //��Ⱦ����0x1018
						lcd_reg_write(0x0004,0x0000); 
						lcd_reg_write(0x0008,0x0202);  
						lcd_reg_write(0x0009,0x0000);
						lcd_reg_write(0x000A,0x0000); 
						lcd_reg_write(0x000C,0x0000); 
						lcd_reg_write(0x000D,0x0000);
						lcd_reg_write(0x000F,0x0000);
						//power on sequence VGHVGL
						lcd_reg_write(0x0010,0x0000);   
						lcd_reg_write(0x0011,0x0007);  
						lcd_reg_write(0x0012,0x0000);  
						lcd_reg_write(0x0013,0x0000); 
						lcd_reg_write(0x0007,0x0000); 
						//vgh 
						lcd_reg_write(0x0010,0x1690);   
						lcd_reg_write(0x0011,0x0227);
						//delayms(100);
						//vregiout 
						lcd_reg_write(0x0012,0x009D); //0x001b
						//delayms(100); 
						//vom amplitude
						lcd_reg_write(0x0013,0x1900);
						//delayms(100); 
						//vom H
						lcd_reg_write(0x0029,0x0025); 
						lcd_reg_write(0x002B,0x000D); 
						//gamma
						lcd_reg_write(0x0030,0x0007);
						lcd_reg_write(0x0031,0x0303);
						lcd_reg_write(0x0032,0x0003);// 0006
						lcd_reg_write(0x0035,0x0206);
						lcd_reg_write(0x0036,0x0008);
						lcd_reg_write(0x0037,0x0406); 
						lcd_reg_write(0x0038,0x0304);//0200
						lcd_reg_write(0x0039,0x0007); 
						lcd_reg_write(0x003C,0x0602);// 0504
						lcd_reg_write(0x003D,0x0008); 
						//ram
						lcd_reg_write(0x0050,0x0000); 
						lcd_reg_write(0x0051,0x00EF);
						lcd_reg_write(0x0052,0x0000); 
						lcd_reg_write(0x0053,0x013F);  
						lcd_reg_write(0x0060,0xA700); 
						lcd_reg_write(0x0061,0x0001); 
						lcd_reg_write(0x006A,0x0000); 
						//
						lcd_reg_write(0x0080,0x0000); 
						lcd_reg_write(0x0081,0x0000); 
						lcd_reg_write(0x0082,0x0000); 
						lcd_reg_write(0x0083,0x0000); 
						lcd_reg_write(0x0084,0x0000); 
						lcd_reg_write(0x0085,0x0000); 
						//
						lcd_reg_write(0x0090,0x0010); 
						lcd_reg_write(0x0092,0x0600); 
						
						lcd_reg_write(0x0007,0x0133);
						lcd_reg_write(0x00,0x0022);//
    }
	else if(lcd_id == 0x9320){
	     /* Start Initial Sequence ------------------------------------------------*/
          lcd_reg_write(LCD_REG_229,0x8000); /* Set the internal vcore voltage */
          lcd_reg_write(LCD_REG_0,  0x0001); /* Start internal OSC. */
          lcd_reg_write(LCD_REG_1,  0x0100); /* set SS and SM bit */
          lcd_reg_write(LCD_REG_2,  0x0700); /* set 1 line inversion */
          lcd_reg_write(LCD_REG_3,  0x1030); /* set GRAM write direction and BGR=1. */
          lcd_reg_write(LCD_REG_4,  0x0000); /* Resize register */
          lcd_reg_write(LCD_REG_8,  0x0202); /* set the back porch and front porch */
          lcd_reg_write(LCD_REG_9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
          lcd_reg_write(LCD_REG_10, 0x0000); /* FMARK function */
          lcd_reg_write(LCD_REG_12, 0x0000); /* RGB interface setting */
          lcd_reg_write(LCD_REG_13, 0x0000); /* Frame marker Position */
          lcd_reg_write(LCD_REG_15, 0x0000); /* RGB interface polarity */

          /* Power On sequence -----------------------------------------------------*/
          lcd_reg_write(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
          lcd_reg_write(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
          lcd_reg_write(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
          lcd_reg_write(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
          delay_ms(2000);                 /* Dis-charge capacitor power voltage (200ms) */
          lcd_reg_write(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
          lcd_reg_write(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
          delay_ms(500);                  /* Delay 50 ms */
          lcd_reg_write(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
          delay_ms(500);                  /* Delay 50 ms */
          lcd_reg_write(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
          lcd_reg_write(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
          delay_ms(500);                  /* Delay 50 ms */
          lcd_reg_write(LCD_REG_32, 0x0000); /* GRAM horizontal Address */
          lcd_reg_write(LCD_REG_33, 0x0000); /* GRAM Vertical Address */

          /* Adjust the Gamma Curve ------------------------------------------------*/
          lcd_reg_write(LCD_REG_48, 0x0007);
          lcd_reg_write(LCD_REG_49, 0x0007);
          lcd_reg_write(LCD_REG_50, 0x0007);
          lcd_reg_write(LCD_REG_53, 0x0007);
          lcd_reg_write(LCD_REG_54, 0x0007);
          lcd_reg_write(LCD_REG_55, 0x0700);
          lcd_reg_write(LCD_REG_56, 0x0700);
          lcd_reg_write(LCD_REG_57, 0x0700);
          lcd_reg_write(LCD_REG_60, 0x0700);
          lcd_reg_write(LCD_REG_61, 0x1F00);
        
          /* Set GRAM area ---------------------------------------------------------*/
          lcd_reg_write(LCD_REG_80, 0x0000); /* Horizontal GRAM Start Address */
          lcd_reg_write(LCD_REG_81, 0x00EF); /* Horizontal GRAM End Address */
          lcd_reg_write(LCD_REG_82, 0x0000); /* Vertical GRAM Start Address */
          lcd_reg_write(LCD_REG_83, 0x013F); /* Vertical GRAM End Address */
          lcd_reg_write(LCD_REG_96,  0x2700); /* Gate Scan Line */
          lcd_reg_write(LCD_REG_97,  0x0001); /* NDL,VLE, REV */
          lcd_reg_write(LCD_REG_106, 0x0000); /* set scrolling line */

          /* Partial Display Control -----------------------------------------------*/
          lcd_reg_write(LCD_REG_128, 0x0000);
          lcd_reg_write(LCD_REG_129, 0x0000);
          lcd_reg_write(LCD_REG_130, 0x0000);
          lcd_reg_write(LCD_REG_131, 0x0000);
          lcd_reg_write(LCD_REG_132, 0x0000);
          lcd_reg_write(LCD_REG_133, 0x0000);

          /* Panel Control ---------------------------------------------------------*/
          lcd_reg_write(LCD_REG_144, 0x0010);
          lcd_reg_write(LCD_REG_146, 0x0000);
          lcd_reg_write(LCD_REG_147, 0x0003);
          lcd_reg_write(LCD_REG_149, 0x0110);
          lcd_reg_write(LCD_REG_151, 0x0000);
          lcd_reg_write(LCD_REG_152, 0x0000);

          /* Set GRAM write direction and BGR = 1 */
          /* I/D=01 (Horizontal : increment, Vertical : decrement) */
          /* AM=1 (address is updated in vertical writing direction) */
          lcd_reg_write(LCD_REG_3, 0x1018);

          lcd_reg_write(LCD_REG_7, 0x0173); /* 262K color and display ON */ 	
		}
		else if(lcd_id == 0x9341){
					lcd_wr_reg(0xCF);  
					lcd_wr_data(0x00); 
					lcd_wr_data(0xC1); 
					lcd_wr_data(0X30); 
					lcd_wr_reg(0xED);  
					lcd_wr_data(0x64); 
					lcd_wr_data(0x03); 
					lcd_wr_data(0X12); 
					lcd_wr_data(0X81); 
					lcd_wr_reg(0xE8);  
					lcd_wr_data(0x85); 
					lcd_wr_data(0x10); 
					lcd_wr_data(0x7A); 
					lcd_wr_reg(0xCB);  
					lcd_wr_data(0x39); 
					lcd_wr_data(0x2C); 
					lcd_wr_data(0x00); 
					lcd_wr_data(0x34); 
					lcd_wr_data(0x02); 
					lcd_wr_reg(0xF7);  
					lcd_wr_data(0x20); 
					lcd_wr_reg(0xEA);  
					lcd_wr_data(0x00); 
					lcd_wr_data(0x00); 
					lcd_wr_reg(0xC0);    //Power control 
					lcd_wr_data(0x1B);   //VRH[5:0] 
					lcd_wr_reg(0xC1);    //Power control 
					lcd_wr_data(0x01);   //SAP[2:0];BT[3:0] 
					lcd_wr_reg(0xC5);    //VCM control 
					lcd_wr_data(0x30); 	 //3F
					lcd_wr_data(0x30); 	 //3C
					lcd_wr_reg(0xC7);    //VCM control2 
					lcd_wr_data(0XB7); 
					lcd_wr_reg(0x36);    // Memory Access Control 
					lcd_wr_data(0x48); 
					lcd_wr_reg(0x3A);   
					lcd_wr_data(0x55); 
					lcd_wr_reg(0xB1);   
					lcd_wr_data(0x00);   
					lcd_wr_data(0x1A); 
					lcd_wr_reg(0xB6);    // Display Function Control 
					lcd_wr_data(0x0A); 
					lcd_wr_data(0xA2); 
					lcd_wr_reg(0xF2);    // 3Gamma Function Disable 
					lcd_wr_data(0x00); 
					lcd_wr_reg(0x26);    //Gamma curve selected 
					lcd_wr_data(0x01); 
					lcd_wr_reg(0xE0);    //Set Gamma 
					lcd_wr_data(0x0F); 
					lcd_wr_data(0x2A); 
					lcd_wr_data(0x28); 
					lcd_wr_data(0x08); 
					lcd_wr_data(0x0E); 
					lcd_wr_data(0x08); 
					lcd_wr_data(0x54); 
					lcd_wr_data(0XA9); 
					lcd_wr_data(0x43); 
					lcd_wr_data(0x0A); 
					lcd_wr_data(0x0F); 
					lcd_wr_data(0x00); 
					lcd_wr_data(0x00); 
					lcd_wr_data(0x00); 
					lcd_wr_data(0x00); 		 
					lcd_wr_reg(0XE1);    //Set Gamma 
					lcd_wr_data(0x00); 
					lcd_wr_data(0x15); 
					lcd_wr_data(0x17); 
					lcd_wr_data(0x07); 
					lcd_wr_data(0x11); 
					lcd_wr_data(0x06); 
					lcd_wr_data(0x2B); 
					lcd_wr_data(0x56); 
					lcd_wr_data(0x3C); 
					lcd_wr_data(0x05); 
					lcd_wr_data(0x10); 
					lcd_wr_data(0x0F); 
					lcd_wr_data(0x3F); 
					lcd_wr_data(0x3F); 
					lcd_wr_data(0x0F); 
					lcd_wr_reg(0x2B); 
					lcd_wr_data(0x00);
					lcd_wr_data(0x00);
					lcd_wr_data(0x01);
					lcd_wr_data(0x3f);
					lcd_wr_reg(0x2A); 
					lcd_wr_data(0x00);
					lcd_wr_data(0x00);
					lcd_wr_data(0x00);
					lcd_wr_data(0xef);	 
					lcd_wr_reg(0x11); //Exit Sleep
					delay_ms(120);
					lcd_wr_reg(0x29); //display on	
		}
		GPIO_SetBits(GPIOD,GPIO_Pin_10);  //��������
		g_lcd_dir = LCD_DIR;
		lcd_clear(BACK_COLOR);  //���ñ�����ɫ
		if(g_lcd_dir == 1){  //����
			g_lcd_height = 320;
			g_lcd_width = 240;
			
		}
}

//��GRAMд������
void lcd_ram_write(u16 ram_data){
    LCD->LCD_RAM = ram_data;
}

//���û�������
void lcd_set_cursor(u16 x_pos,u16 y_pos){
	if(lcd_id==0X9341||lcd_id==0X5310)
	{		    
		lcd_wr_reg(0X2A); 
		lcd_wr_data(x_pos>>8);
		lcd_wr_data(x_pos&0XFF); 			 
		lcd_wr_reg(0X2B); 
		lcd_wr_data(y_pos>>8);
		lcd_wr_data(y_pos&0XFF); 		
	}
	else{
			lcd_reg_write(LCD_REG_32,x_pos);
			lcd_reg_write(LCD_REG_33,y_pos);
	}

}
//GRAM��ַ��������
void lcd_ram_write_prepare(){
	if(lcd_id == 0x9325){
    LCD->LCD_REG = LCD_REG_34;
	}else if(lcd_id == 0x9341){
		LCD->LCD_REG = 0X2C;
	}
}
//����
void lcd_draw_point(u16 x,u16 y,u16 color){

    if(lcd_id == 0x9341){
        lcd_set_cursor(240 - x,y);
    }else{
        lcd_set_cursor(x,y);
    }
    lcd_ram_write_prepare();
    lcd_ram_write(color);
}

//����
void lcd_draw_line(u16 x,u16 y,u16 lenth,u8 dir){
    u32 i = 0;

    lcd_set_cursor(x,y);
    if(dir == 1){
       lcd_ram_write_prepare();  //���ó�GRAM����
			 for(i = 0;i < lenth;i++){
					lcd_ram_write(0x0000);
				}
	}
}

//��������colorΪ������ɫ
void lcd_clear(u16 color){
    u32 i;
    lcd_set_cursor(0,0);
    lcd_ram_write_prepare();
    for(i = 0;i < 76800;i++){
        lcd_ram_write(color);
    }

}



//void lcd_show_char(u16 x,u16 y,u8 num,u8 size,u8 mode)
//{  							  
//  u8 temp,t1,t;
//	u16 y0 = y;
//	u8 csize=(size/8+((size%8)?1:0))*(size/2);		
// 	num=num-' ';
//	for(t=0;t<csize;t++)
//	{   
//		if(size==12)temp=asc2_1206[num][t]; 	 	
//		else if(size==16)temp=asc2_1608[num][t];	
//		else if(size==24)temp=asc2_2412[num][t];	
//		else return;								
//		for(t1=0;t1<8;t1++)
//		{			    
//			if(temp&0x80)lcd_draw_point(x,y,POINT_COLOR);
//			else if(mode==0)lcd_draw_point(x,y,BACK_COLOR);
//			temp<<=1;
//			y++;
//			if(y > 320)return;		//
//			if((y0-y)==size)
//			{
//				y=y0;
//				x++;
//				if(x >= 240)return;	//
//				break;
//			}
//		}  	 
//	}  	    	   	 	  
//}   

void lcd_show_char(u16 x,u16 y,char num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)lcd_draw_point(x,y,POINT_COLOR);
			else if(mode==0)lcd_draw_point(x,y,BACK_COLOR);
			temp<<=1;
#if DIR == 0
			y++;
			if(y>=320)return;		//��������
			if((y-y0)==size)
			{
#else
			y--;
			if(y<0)return;		//��������
			if((y0-y)==size)
			{
#endif
			
				y=y0;
#if DIR == 0
				x++;
				if(x>=240)return;	//��������
#else
				x--;
				if(x<0)return;	//��������
#endif
				break;
			}
		}  	 
	}  	    	   	 	  
}   
	   	 	  



void lcd_show_string(u16 x,u16 y,u16 width,u16 height,u8 size,char *p)
{         
#if DIR == 0
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       

		if(x>=width){x=x0;y+=size;}
		if(y>=height)break;//�˳�
        lcd_show_char(x,y,*p,size,0);
        x+=size/2;
#else
	u8 x0=239-x;
	x = 239-x;
	y = 320-y;
	width=x-width;
	height=y-height;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x<width){x=x0;y-=size;}
		if(y<height)break;//�˳�
        lcd_show_char(x,y,*p,size,0);
        x-=size/2;
#endif
        
        p++;
		}
}

void fsmc_config(){
    FSMC_NORSRAMInitTypeDef fsmc_init_stru;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming,writeTiming;

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);   //ʹ��FMCʱ��

/**********************TFTLCD��FSMC����***********************/
   /* FMC_Bank1_NORSRAM4 configuration */
  readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  readWriteTiming.FSMC_DataSetupTime = 60;			//���ݱ���ʱ��Ϊ60��HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	writeTiming.FSMC_AddressSetupTime =9;	      //��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
  writeTiming.FSMC_DataSetupTime = 8;		 //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
   /* Color LCD configuration ------------------------------------
      LCD configured as follow:
         - Data/Address MUX = Disable
         - Memory Type = SRAM
         - Data Width = 16bit
         - Write Operation = Enable
         - Extended Mode = Enable
         - Asynchronous Wait = Disable */
 
  fsmc_init_stru.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  fsmc_init_stru.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
  fsmc_init_stru.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  fsmc_init_stru.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
  fsmc_init_stru.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  fsmc_init_stru.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	fsmc_init_stru.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  fsmc_init_stru.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  fsmc_init_stru.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  fsmc_init_stru.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
  fsmc_init_stru.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  fsmc_init_stru.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
  fsmc_init_stru.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  fsmc_init_stru.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
  fsmc_init_stru.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��;
 
   FSMC_NORSRAMInit(&fsmc_init_stru);   
 
   /* Enable FMC NOR/SRAM Bank3 */
   FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

}
