#ifndef __Encoder_H
#define __Encoder_H
#include "app.h"

#define SPI_TX_ON()               {GPIOB->cfglr |= 0x00900000;}
#define SPI_TX_OFF()              {GPIOB->cfglr &= 0xFF4FFFFF;}


#define SPI_CS1_ENABLE()  gpio_bits_reset(GPIOB,GPIO_PINS_5)
#define SPI_CS1_DISABLE() gpio_bits_set(GPIOB,GPIO_PINS_5)
#define SPI_CS2_ENABLE()  gpio_bits_reset(GPIOB,GPIO_PINS_12);
#define SPI_CS2_DISABLE() gpio_bits_set(GPIOB,GPIO_PINS_12);

#define OFFX_WRIT    ((0x0A << 4)	| 0x01)
#define OFFX_READ    ((0x8000) | OFFX_WRIT)

#define MOD1_WRIT    ((0x06 << 4)	| 0x01)
#define MOD1_READ    ((0x8000) | MOD1_WRIT) 

#define MOD2_WRIT    ((0x08 << 4)| 0x01)	
#define MOD2_READ    ((0x8000) | MOD2_WRIT)  

#define MOD3_WRIT    ((0x09 << 4)| 0x01)
#define MOD3_READ    ((0x8000) | MOD3_WRIT) 

#define MOD4_WRIT    ((0x0E << 4)| 0x01)
#define MOD4_READ    ((0x8000) | MOD4_WRIT) 

#define IFAB_WRIT    ((0x0D << 4)| 0x01)
#define IFAB_READ    ((0x8000) | IFAB_WRIT) 


void TLE5012B_Init(void);
void MT6701_Init(void);

u16 Read_M1_Encoder(void);
u16 Read_M2_Encoder(void);
u16 Read_MT6701(void);

#endif
