#include "cmd_func.h"
#include "cmd.h"
#include <stdlib.h>
#include "global.h"
#include "configuration.h"
#include <string.h>
#include "delay.h"
#include "radar.h"
#include "math.h"

extern bool g_stop_flag;
extern bool switch_side;
extern bool debug_print;
extern bool debug;

u8 target=0;       				//Ä¿±ê0-6

void cmd_reboot_func(int argc,char *argv[]){
    NVIC_SystemReset();
}

void cmd_stop_func(int argc,char *argv[]){
    if(argc == 1){
        g_stop_flag = true;
    }else if(argc == 2){
        g_stop_flag = atoi(argv[1]);
    }
}

void cmd_hello_func(int argc,char *argv[]){
    USART_SendString(CMD_USARTx, "msg: Hello World\n");
}

void cmd_test_func(int argc,char *argv[]){
	
}


void cmd_switch_func(int argc,char *argv[])
{
	if(strcmp(argv[1],"left") == 0)
	{
		LEFT_RIGHT = 0;
		switch_side = true;
	}else if(strcmp(argv[1],"right") == 0)
	{
		LEFT_RIGHT = 1;
		switch_side = true;
	}
	USART_SendString(bluetooth,"msg:left(0) or right(1):%d\n",LEFT_RIGHT);
}

