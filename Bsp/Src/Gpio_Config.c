#include "app.h"


void Gpio_config(void)
{
	gpio_init_type gpio_init_struct;
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_init_struct);

	/* configure the led gpio */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);
	gpio_bits_reset(GPIOA,GPIO_PINS_3);// 测试预留

	/* configure the led gpio */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_2;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOB, &gpio_init_struct);
	gpio_bits_reset(GPIOB,GPIO_PINS_2);// 关闭电机驱动
	//	gpio_bits_set(GPIOB,GPIO_PINS_2);

	/* configure the led gpio */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_14;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOC, &gpio_init_struct);

	//	gpio_bits_set(GPIOC,GPIO_PINS_14); // 电源使能
	gpio_bits_reset(GPIOC,GPIO_PINS_14); // 电源失能
}


