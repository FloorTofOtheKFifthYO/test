#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "sys.h"
#include "configuration.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int state;
	char who;
	int x,y;
}SwitchKey; 

void Switch_send(SwitchKey *switchkey);

#endif
