#ifndef __USART_H
#define __USART_H
#include "app.h"

#define BUFFER_SIZE   (128)

extern uint8_t Tx1_buffer[BUFFER_SIZE];
extern uint8_t Rx1_buffer[BUFFER_SIZE];
extern u8 Tx1_Flag;
extern u8 U1_IDLE_Flag;

extern uint8_t Tx2_buffer[BUFFER_SIZE];
extern uint8_t Rx2_buffer[BUFFER_SIZE];
extern u8 Tx2_Flag;
extern u8 U2_IDLE_Flag;

void USART1_init(u32 bound);
void USART2_init(u32 bound);

uint32_t UART1_SendDataDMA(uint8_t *data, uint16_t len);
uint32_t UART2_SendDataDMA(uint8_t *data, uint16_t len);
#endif
