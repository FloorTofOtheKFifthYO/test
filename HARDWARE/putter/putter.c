#include "putter.h"
#include "encoder.h"
#include <math.h>

extern SwitchTIM * Which;

static void putter_move(putter putter_struct, int v)
{
	if (v - putter_struct.SP*1.0 > 0.0000001)
		v = putter_struct.SP;
	else if (v + putter_struct.SP*1.0 < 0.0000001)
		v=-putter_struct.SP;
	motor_usart_setspeed(putter_struct.motor,v);
}

/**
  * @brief ��ʼ��,�����̰��Ӧ�Ķ�ʱ����
  *     
  * @note	������Ҫ��ַ����Ϊ��Ҫ�����̰崫�ص����ݽ��а�
  *
  * @param  putter_struct: ���Ƹ�ʵ��ָ��  
  *          
  * @retval void
  */
void putter_init(putter *putter_struct)
{
	SetUsed(putter_struct->GetTimx,1);
	switch(putter_struct->GetTimx)
	{
		case 1:
			putter_struct->position = &(Which->GetTim1);
			break;
		case 3:
			putter_struct->position = &(Which->GetTim3);
			break;
		case 4:
			putter_struct->position = &(Which->GetTim4);
			break;
		case 5:
			putter_struct->position = &(Which->GetTim5);
			break;
		case 8:
			putter_struct->position = &(Which->GetTim8);
			break;
		defult:
			break;
	}
	putter_struct->d_last = 0;
	putter_struct->cnt = 0;
	putter_struct->putter_flag = false;
}

/**
  * @brief main��������ѯ����
  *     
  * @note	
  *
  * @param  putter_struct: ���Ƹ�ʵ��  
  *          
  * @retval void
  */
void putter_main(putter putter_struct)
{
	float d,dd;
	
	if (putter_struct.putter_flag)
	{
		d = putter_struct.pur_pos - (*(putter_struct.position) / 10000.f);
		dd = d - putter_struct.d_last;
		putter_struct.d_last = d;
		if (fabs(d) < 0.01)
		{
			if (putter_struct.cnt > 10)
			{
				putter_move(putter_struct,0);
				putter_struct.cnt = 0;
				putter_struct.putter_flag=false;
			}
			else
			{
				putter_struct.cnt++;
				putter_move(putter_struct,d * putter_struct.d_rate + dd * putter_struct.dd_rate);
			}
		}
		else
		{
			putter_struct.cnt = 0;
			putter_move(putter_struct,d * putter_struct.d_rate + dd * putter_struct.dd_rate);
		}
	}
}

/**
  * @brief �Ƶ��Ƹ�
  *     
  * @note	
  *
  * @param  motor_struct: ���Ƹ�ʵ��ָ�룬
			floatpur_pos   ϣ�������λ��
  *          
  * @retval void
  */
void putter_moveto(putter *putter_struct,float pur_pos)
{
	putter_struct->pur_pos = pur_pos;
	putter_struct->putter_flag = true;
}

