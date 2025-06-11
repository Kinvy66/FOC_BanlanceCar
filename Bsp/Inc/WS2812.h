#ifndef __WS2812B_H
#define __WS2812B_H	
#include "app.h"


#define RGB_1  165	//T1H	1码
#define RGB_0  85	//T0L 0码

extern uint16_t WS2812_Buffer[24*8+1];
extern uint32_t RGB_Data[8];

extern u8 WS2812_SendFlag;
void WS2812_init(void);
void send_Data(uint32_t *rgb,uint16_t len);

#endif 
