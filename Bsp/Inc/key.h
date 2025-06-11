#ifndef __KEY_H
#define __KEY_H
#include "at32f413_wk_config.h"

#define Key1 		gpio_input_data_bit_read(GPIOC,GPIO_PINS_13)

extern u8 KeyFlag;

void Key_Init(void);	//IO初始化
void Key_Scan(void);  		//按键扫描函数
#endif

