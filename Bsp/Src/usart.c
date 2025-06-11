#include "usart.h"

u8 U1_IDLE_Flag = 0;
u8 U2_IDLE_Flag = 0;

uint8_t Tx1_buffer[BUFFER_SIZE];
uint8_t Rx1_buffer[BUFFER_SIZE];

uint8_t Tx2_buffer[BUFFER_SIZE];
uint8_t Rx2_buffer[BUFFER_SIZE];

u8 Tx1_Flag = 0;//0:完成 1：正在发送
u8 Tx2_Flag = 0;//0:完成 1：正在发送

void Dma_rx1(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	dma_reset(DMA1_CHANNEL5);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx1_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL5, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA1, FLEX_CHANNEL5, DMA_FLEXIBLE_UART1_RX);
	dma_channel_enable(DMA1_CHANNEL5, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_tx1(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	dma_reset(DMA1_CHANNEL4);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)Tx1_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL4, &dma_init_struct);

  /* config flexible dma for usart3 tx */
  dma_flexible_config(DMA1, FLEX_CHANNEL4, DMA_FLEXIBLE_UART1_TX);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA1_Channel4_IRQn, 2, 0);
	
	dma_interrupt_enable(DMA1_CHANNEL4,DMA_FDT_INT,TRUE); // 开启发送中断
} 

void Dma_rx2(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	dma_reset(DMA1_CHANNEL6);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx2_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART2->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL6, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA1, FLEX_CHANNEL6, DMA_FLEXIBLE_UART2_RX);
	dma_channel_enable(DMA1_CHANNEL6, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_tx2(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	dma_reset(DMA1_CHANNEL7);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)Tx2_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART2->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL7, &dma_init_struct);

  /* config flexible dma for usart3 tx */
  dma_flexible_config(DMA1, FLEX_CHANNEL7, DMA_FLEXIBLE_UART2_TX);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA1_Channel7_IRQn, 3, 0);
	
	dma_interrupt_enable(DMA1_CHANNEL7,DMA_FDT_INT,TRUE); // 开启发送中断
}

void USART1_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_6;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOB, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_7;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOB, &gpio_init_struct);

	usart_init(USART1, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(USART1, TRUE);
	usart_receiver_enable(USART1, TRUE);
	
	usart_dma_transmitter_enable(USART1, TRUE);
	usart_dma_receiver_enable(USART1, TRUE);
	usart_enable(USART1, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART1_IRQn, 3, 1);
	
	usart_interrupt_enable(USART1,USART_IDLE_INT,TRUE); // 串口空闲中断
//	usart_interrupt_enable(USART3, USART_RDBF_INT, FALSE);
	
	Dma_tx1();
	Dma_rx1();
}

void USART2_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_pin_remap_config(USART1_GMUX_0001,TRUE);
	
	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_2;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA, &gpio_init_struct);

	usart_init(USART2, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(USART2, TRUE);
	usart_receiver_enable(USART2, TRUE);
	
	usart_dma_transmitter_enable(USART2, TRUE);
	usart_dma_receiver_enable(USART2, TRUE);
	usart_enable(USART2, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART2_IRQn, 3, 2);
	
	usart_interrupt_enable(USART2,USART_IDLE_INT,TRUE); // 串口空闲中断
//	usart_interrupt_enable(USART3, USART_RDBF_INT, FALSE);
	
	Dma_tx2();
	Dma_rx2();
}

uint32_t UART1_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx1_buffer,data,len);
	usart_dma_transmitter_enable(USART1, TRUE);
	dma_channel_enable(DMA1_CHANNEL4, FALSE);
	dma_data_number_set(DMA1_CHANNEL4,len);
	dma_channel_enable(DMA1_CHANNEL4, TRUE);
  return len;
}

uint32_t UART2_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx2_buffer,data,len);
	usart_dma_transmitter_enable(USART2, TRUE);
	dma_channel_enable(DMA1_CHANNEL7, FALSE);
	dma_data_number_set(DMA1_CHANNEL7,len);
	dma_channel_enable(DMA1_CHANNEL7, TRUE);
  return len;
}

void USART1_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
//	if(usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
//  {
//    usart_data_receive(USART3);
//  }
  if(usart_flag_get(USART1, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(USART1, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL5);	
		
    if(len < 128)memcpy(GET_USART1_Data,Rx1_buffer,len);
		dma_channel_enable(DMA1_CHANNEL5, FALSE);
		dma_data_number_set(DMA1_CHANNEL5,BUFFER_SIZE);
		dma_channel_enable(DMA1_CHANNEL5, TRUE);
	
		U1_IDLE_Flag = 1;					
	}     
}

void USART2_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
//	if(usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
//  {
//    usart_data_receive(USART3);
//  }
  if(usart_flag_get(USART2, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(USART2, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL6);	
		if(len < 128)memcpy(GET_USART2_Data,Rx2_buffer,len);
		dma_channel_enable(DMA1_CHANNEL6, FALSE);
		dma_data_number_set(DMA1_CHANNEL6,BUFFER_SIZE);
		dma_channel_enable(DMA1_CHANNEL6, TRUE);
	
		U2_IDLE_Flag = 1;					
	}     
}

//串口1发送完成中断处理函数
void DMA1_Channel4_IRQHandler(void)
{
	if(dma_flag_get(DMA1_FDT4_FLAG))
	{
		dma_flag_clear(DMA1_FDT4_FLAG); //清除全部中断标志
		Tx1_Flag = 0;
	}
}

//串口2发送完成中断处理函数
void DMA1_Channel7_IRQHandler(void)
{
	if(dma_flag_get(DMA1_FDT7_FLAG))
	{
		dma_flag_clear(DMA1_FDT7_FLAG); //清除全部中断标志
		Tx2_Flag = 0;
	}
}

