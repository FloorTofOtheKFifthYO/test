#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h" 	 

//LCD寄存器
#define LCD_REG_0             0x00
#define LCD_REG_1             0x01
#define LCD_REG_2             0x02
#define LCD_REG_3             0x03
#define LCD_REG_4             0x04
#define LCD_REG_5             0x05
#define LCD_REG_6             0x06
#define LCD_REG_7             0x07
#define LCD_REG_8             0x08
#define LCD_REG_9             0x09
#define LCD_REG_10            0x0A
#define LCD_REG_12            0x0C
#define LCD_REG_13            0x0D
#define LCD_REG_14            0x0E
#define LCD_REG_15            0x0F
#define LCD_REG_16            0x10
#define LCD_REG_17            0x11
#define LCD_REG_18            0x12
#define LCD_REG_19            0x13
#define LCD_REG_20            0x14
#define LCD_REG_21            0x15
#define LCD_REG_22            0x16
#define LCD_REG_23            0x17
#define LCD_REG_24            0x18
#define LCD_REG_25            0x19
#define LCD_REG_26            0x1A
#define LCD_REG_27            0x1B
#define LCD_REG_28            0x1C
#define LCD_REG_29            0x1D
#define LCD_REG_30            0x1E
#define LCD_REG_31            0x1F
#define LCD_REG_32            0x20
#define LCD_REG_33            0x21
#define LCD_REG_34            0x22
#define LCD_REG_36            0x24
#define LCD_REG_37            0x25
#define LCD_REG_40            0x28
#define LCD_REG_41            0x29
#define LCD_REG_43            0x2B
#define LCD_REG_45            0x2D
#define LCD_REG_48            0x30
#define LCD_REG_49            0x31
#define LCD_REG_50            0x32
#define LCD_REG_51            0x33
#define LCD_REG_52            0x34
#define LCD_REG_53            0x35
#define LCD_REG_54            0x36
#define LCD_REG_55            0x37
#define LCD_REG_56            0x38
#define LCD_REG_57            0x39
#define LCD_REG_58            0x3A
#define LCD_REG_59            0x3B
#define LCD_REG_60            0x3C
#define LCD_REG_61            0x3D
#define LCD_REG_62            0x3E
#define LCD_REG_63            0x3F
#define LCD_REG_64            0x40
#define LCD_REG_65            0x41
#define LCD_REG_66            0x42
#define LCD_REG_67            0x43
#define LCD_REG_68            0x44
#define LCD_REG_69            0x45
#define LCD_REG_70            0x46
#define LCD_REG_71            0x47
#define LCD_REG_72            0x48
#define LCD_REG_73            0x49
#define LCD_REG_74            0x4A
#define LCD_REG_75            0x4B
#define LCD_REG_76            0x4C
#define LCD_REG_77            0x4D
#define LCD_REG_78            0x4E
#define LCD_REG_79            0x4F
#define LCD_REG_80            0x50
#define LCD_REG_81            0x51
#define LCD_REG_82            0x52
#define LCD_REG_83            0x53
#define LCD_REG_96            0x60
#define LCD_REG_97            0x61
#define LCD_REG_106           0x6A
#define LCD_REG_118           0x76
#define LCD_REG_128           0x80
#define LCD_REG_129           0x81
#define LCD_REG_130           0x82
#define LCD_REG_131           0x83
#define LCD_REG_132           0x84
#define LCD_REG_133           0x85
#define LCD_REG_134           0x86
#define LCD_REG_135           0x87
#define LCD_REG_136           0x88
#define LCD_REG_137           0x89
#define LCD_REG_139           0x8B
#define LCD_REG_140           0x8C
#define LCD_REG_141           0x8D
#define LCD_REG_143           0x8F
#define LCD_REG_144           0x90
#define LCD_REG_145           0x91
#define LCD_REG_146           0x92
#define LCD_REG_147           0x93
#define LCD_REG_148           0x94
#define LCD_REG_149           0x95
#define LCD_REG_150           0x96
#define LCD_REG_151           0x97
#define LCD_REG_152           0x98
#define LCD_REG_153           0x99
#define LCD_REG_154           0x9A
#define LCD_REG_157           0x9D
#define LCD_REG_192           0xC0
#define LCD_REG_193           0xC1
#define LCD_REG_229           0xE5



typedef struct{
    u16 LCD_REG;
    u16 LCD_RAM;
}lcd_typedef;

//使用FSMC第一存储快(BANK1：0x60000000)的第四分区(0x0C000000),使用地址A6(0x0000007E)
//0x0000007E 的二进制为01111110 因为LCD屏是16位的，所以AHB地址1位应对应LCD地址A0位，所以
//二进制的bit[7]应该对应LCD的A6位。
//在lcd_typedef结构体中：
//LCD_REG对应0x6C00007E(二进制后8位是 01111110)此刻A6 = 0 即 RS = 0，命令模式
//LCD_RAM对应&LCD_REG+2 = 0x6C000080(二进制后8位是 10000000)此刻A6 = 1 即 RS = 1，数据模式
#define LCD_BASE ((u32)(0x60000000|0x0C000000|0x0000007E))
#define LCD ((lcd_typedef *)LCD_BASE) 
#define LCD_DIR 1;			//横屏或竖屏
#define POINT_COLOR 0xFFFF   //画笔颜色
#define BACK_COLOR 0x0000    //背景色

#define DIR 1			//0为原始方向，1为反方向

u16 lcd_reg_read(u16 lcd_reg_addr);
u16 lcd_rd_data(void);
void lcd_reg_write(u16 lcd_reg_addr,u16 reg_data);
void lcd_wr_reg(vu16 regval);
void lcd_wr_data(vu16 data);
void lcd_init(void);
void lcd_set_cursor(u16 x_pos,u16 y_pos);
void lcd_draw_line(u16 x,u16 y,u16 lenth,u8 dir);
void lcd_draw_point(u16 x,u16 y,u16 color);
void lcd_ram_write_prepare();
void lcd_ram_write(u16 ram_data);
void lcd_clear(u16 color);
void lcd_show_char(u16 x,u16 y,char num,u8 size,u8 mode);
void lcd_show_string(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);
void lcd_set_cursor(u16 x_pos,u16 y_pos);
void fsmc_config();

#endif  
	 
	 



