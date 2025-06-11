#ifndef __LED_H
#define __LED_H
#include "at32f413_wk_config.h"

#define RED_1   gpio_bits_set(LED2_GPIO_PORT,LED2_PIN)
#define RED_0   gpio_bits_reset(LED2_GPIO_PORT,LED2_PIN)
#define GREEN_1  gpio_bits_set(LED1_GPIO_PORT,LED1_PIN)
#define GREEN_0  gpio_bits_reset(LED1_GPIO_PORT,LED1_PIN)

void LED_Init(void);
void R_LED(u8 data);
void G_LED(u8 data);

#endif
