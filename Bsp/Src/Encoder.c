#include "app.h"

void MT6701_Init(void)
{
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);		
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_INPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_14;
  gpio_initstructure.gpio_pull = GPIO_PULL_DOWN;
  gpio_init(GPIOB, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_5 | GPIO_PINS_12 | GPIO_PINS_13;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOB, &gpio_initstructure);

	gpio_bits_set(GPIOB,GPIO_PINS_5 | GPIO_PINS_12 | GPIO_PINS_13 | GPIO_PINS_14);
}

void TLE5012B_Init(void)
{
	spi_init_type spi_init_struct;
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
//	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);	
	
//	gpio_pin_remap_config(SPI1_GMUX_0001,TRUE);
//	gpio_pin_remap_config(SWJTAG_GMUX_010,TRUE);
	
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
  gpio_init(GPIOB, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_5 | GPIO_PINS_12;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOB, &gpio_initstructure);
	
//	gpio_bits_reset(GPIOC,GPIO_PINS_13);
	gpio_bits_set(GPIOB,GPIO_PINS_5 | GPIO_PINS_12);
	
	spi_enable(SPI2, FALSE);
	
	crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
  spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_16BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW; // SPI_CLOCK_POLARITY_LOW SPI_CLOCK_POLARITY_HIGH
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;      // SPI_CLOCK_PHASE_1EDGE SPI_CLOCK_PHASE_2EDGE
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI2, &spi_init_struct);
	
  spi_enable(SPI2, TRUE);
	delay_ms(10);
}

u16 SPI2_ReadWriteByte(u16 byte)
{
	u16 retry=0;				 	
	while(spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET) //等待SPI发送标志位空
	{
		retry++;
		if(retry>200)return 0;
	}
	SPI2->dt = byte; //发送数据
	retry=0;

	while(spi_i2s_flag_get(SPI2, SPI_I2S_RDBF_FLAG) == RESET) //等待SPI接收标志位空
	{
		retry++;
		if(retry>200)return 0;
	}
	return SPI2->dt; //接收数据
}

u16 Read_M1_Encoder(void)//2.25us
{
	u16 Data;
 
	SPI_CS1_ENABLE();
	SPI2_ReadWriteByte(0x8020);
  GPIOB->cfghr &= 0x4FFFFFFF;
	Data = SPI2_ReadWriteByte(0xFF)&0x7fff;
	SPI_CS1_DISABLE();
  GPIOB->cfghr |= 0x90000000;
	
	return Data;
}

u16 Read_M2_Encoder(void)//2.25us
{
	u16 Data;
 
	SPI_CS2_ENABLE();
	SPI2_ReadWriteByte(0x8020);
  GPIOB->cfghr &= 0x4FFFFFFF;
	Data = SPI2_ReadWriteByte(0xFF)&0x7fff;
	SPI_CS2_DISABLE();
  GPIOB->cfghr |= 0x90000000;
	
	return Data;
}

u16 Read_MT6701(void)//2.25us
{
	u16 data;
  u8 i;
	SPI_CS1_ENABLE();
	GPIOB->clr = GPIO_PINS_13;
			GPIOB->scr = GPIO_PINS_13;
			for(i = 0;i < 14; i++)
			{
				GPIOB->clr = GPIO_PINS_13;
				data<<=1;
				if((GPIO_PINS_14 & GPIOB->idt) == GPIO_PINS_14)
					data++;  
				GPIOB->scr = GPIO_PINS_13;
			}
			data = data << 1;
	SPI_CS1_DISABLE();
	
	return data;
}

