#ifndef _AUTO_H_
#define _AUTO_H_

/*
	�������������̣�ע��Ҫ�����صĵ㣬
	���ֶ�ȷ��pos�㣬����flash���ټ����Զ�������Ῠ����ĳ״̬
	�����״̬�£�Ҫ�뵽��һ����ʱ�����flash��û�е��ˣ�ֻ��ȥװ����������������
*/

#include "sys.h"
#include "configuration.h"
#include "link_list.h"
#include "param.h"

#define AUTO_FIRST_RUN 0
#define AUTO_FLASH_SETOR FLASH_Sector_7 //  ����7
#define AUTO_FLASH_ADDR_START ((uint32_t)0x08060000)
#define AUTO_FLASH_ADDR_END ((uint32_t)0x0807FFFF)

typedef struct {
	POSITION start_area;
	POSITION load_area;
	list_node * now_pos_ptr;
	enum {start,load_running,load_arrived,pos_running,pos_arrived,/*handle_control,*/start_running} state;
	
	//������
	bool load_run_flag;
	bool pos_run_flag;
	bool start_run_flag;
	bool launch_l_continute;
	bool launch_r_continute;
	
	int target_l;
	int target_r;

} AutoStrategy;

extern AutoStrategy autorun;

/**
  * @brief  ��ʼ��
  *     
  * @note
  *
  * @param  
  *          
  * @retval 
  */
void auto_init();

/**
  * @brief  ��ѭ��״̬ת��
  *     
  * @note
  *
  * @param 
  *          
  * @retval 
  */
void auto_main();

/**
  * @brief  �������
  *     
  * @note
  *
  * @param 
  *          
  * @retval �ɹ�����1��������-1��-2
  */
int auto_save();

void auto_select_l(int target);

void auto_select_r(int target);

#endif
