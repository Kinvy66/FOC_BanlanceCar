#include "app.h"

u8 TIM_Flag = 0;

crm_clocks_freq_type crm_clocks_freq_struct = {0};

void TIM1_Init(void)  
{
	gpio_init_type gpio_initstructure;
	tmr_output_config_type tmr_output_struct;
	tmr_brkdt_config_type tmr_brkdt_config_struct;
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	
	crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	
	/* timer2 output pin Configuration */
  gpio_initstructure.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
  gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
  gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOA, &gpio_initstructure);

	/* tmr1 configuration */
  /* time base configuration */
  tmr_base_init(TMR1, 5000 , 0); // 100.000.000M/20.000Khz
  tmr_cnt_dir_set(TMR1, TMR_COUNT_TWO_WAY_1);

  /* channel 1, 2, 3 and 4 Configuration in output mode */
  tmr_output_default_para_init(&tmr_output_struct);
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B; //????????
  tmr_output_struct.oc_output_state = TRUE; //??????????
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH; //??????????
  
  /* channel 1 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, TMR1->pr/2);

  /* channel 2 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_2, TMR1->pr/2);

  /* channel 3 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_3, TMR1->pr/2);
  
	/* channel 4 */
  tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_4, &tmr_output_struct);
  tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_4,1);
	
/* automatic output enable, stop, dead time and lock configuration */
  tmr_brkdt_default_para_init(&tmr_brkdt_config_struct);
  tmr_brkdt_config_struct.brk_enable = FALSE;
  tmr_brkdt_config_struct.auto_output_enable = TRUE;
  tmr_brkdt_config_struct.deadtime = 20;
  tmr_brkdt_config_struct.fcsodis_state = TRUE;
  tmr_brkdt_config_struct.fcsoen_state = TRUE;
  tmr_brkdt_config_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_HIGH;
  tmr_brkdt_config_struct.wp_level = TMR_WP_LEVEL_3;
  tmr_brkdt_config(TMR1, &tmr_brkdt_config_struct);
//  /* hall interrupt enable */
//  tmr_interrupt_enable(TMR1, TMR_HALL_INT, TRUE);

//  /* tmr1 hall interrupt nvic init */
//  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
//  nvic_irq_enable(TMR1_TRG_HALL_TMR11_IRQn, 0, 0);

  /* tmr1 output enable */
  tmr_output_enable(TMR1, TRUE);

  /* enable tmr1 */
  tmr_counter_enable(TMR1, TRUE);
}

void TIM8_Init(void)  
{
	gpio_init_type gpio_initstructure;
	tmr_output_config_type tmr_output_struct;
	tmr_brkdt_config_type tmr_brkdt_config_struct;
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	
	crm_periph_clock_enable(CRM_TMR8_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	
	/* timer2 output pin Configuration */
  gpio_initstructure.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8;
  gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
  gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOC, &gpio_initstructure);
	
	/* tmr1 configuration */
  /* time base configuration */
  tmr_base_init(TMR8, 5000 , 0); // 100.000.000M/20.000Khz
  tmr_cnt_dir_set(TMR8, TMR_COUNT_TWO_WAY_1);

  /* channel 1, 2 and 3 configuration in output mode */
  tmr_output_default_para_init(&tmr_output_struct);
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;

  /* channel 1 */
  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_1, TMR8->pr/2);

  /* channel 2 */
  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_2, TMR8->pr/2);

  /* channel 3 */
  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_3, TMR8->pr/2);
  
	/* channel 4 */
  tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_4, &tmr_output_struct);
  tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_4, 1);
	
  /* automatic output enable, break, dead time and lock configuration */
  tmr_brkdt_default_para_init(&tmr_brkdt_config_struct);
  tmr_brkdt_config_struct.brk_enable = FALSE;
  tmr_brkdt_config_struct.auto_output_enable = TRUE;
  tmr_brkdt_config_struct.deadtime = 20;
  tmr_brkdt_config_struct.fcsodis_state = TRUE;
  tmr_brkdt_config_struct.fcsoen_state = TRUE;
  tmr_brkdt_config_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_HIGH;
  tmr_brkdt_config_struct.wp_level = TMR_WP_LEVEL_3;
  tmr_brkdt_config(TMR8, &tmr_brkdt_config_struct);
	
//  tmr_channel_buffer_enable(TMR1, TRUE);

  /* hall interrupt enable */
//  tmr_interrupt_enable(TMR1, TMR_HALL_INT, TRUE);

  /* tmr1 hall interrupt nvic init */
//  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
//  nvic_irq_enable(TMR1_TRG_HALL_TMR11_IRQn, 0, 0);

  /* tmr1 output enable */
  tmr_output_enable(TMR8, TRUE);

  /* enable tmr1 */
  tmr_counter_enable(TMR8, TRUE);
}

void TMR1_TRG_HALL_TMR11_IRQHandler(void)
{
  /* clear tmr1 com pending bit */
  tmr_flag_clear(TMR1, TMR_HALL_FLAG);
}

void TMR8_TRG_HALL_IRQHandler(void)
{
  /* clear tmr1 com pending bit */
  tmr_flag_clear(TMR8, TMR_HALL_FLAG);
}

void TIM2_Init(void)  
{
	tmr_output_config_type tmr_oc_init_structure;
	gpio_init_type gpio_initstructure;
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	
	gpio_pin_remap_config(TMR2_GMUX_011,TRUE);
	gpio_pin_remap_config(SWJTAG_GMUX_010,TRUE);
	
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_3;
  gpio_init(GPIOB, &gpio_initstructure);
	
 	tmr_base_init(TMR2, 1999, (crm_clocks_freq_struct.ahb_freq / 1000000) - 1);
	tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);

  tmr_output_default_para_init(&tmr_oc_init_structure);
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_oc_init_structure.oc_idle_state = FALSE;
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_oc_init_structure.oc_output_state = TRUE;

  tmr_output_channel_config(TMR2, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure);
  tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_2, 1);
  tmr_output_channel_buffer_enable(TMR2, TMR_SELECT_CHANNEL_2, TRUE);
	
	tmr_period_buffer_enable(TMR2, TRUE);
	/* tmr enable counter */
  tmr_counter_enable(TMR2, TRUE);
}

void TIM5_Init(void)  
{
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
 	tmr_base_init(TMR5, 999, (crm_clocks_freq_struct.ahb_freq / 1000000) - 1);
  tmr_cnt_dir_set(TMR5, TMR_COUNT_UP);
  tmr_interrupt_enable(TMR5, TMR_OVF_INT, TRUE);
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(TMR5_GLOBAL_IRQn, 2, 0);
  tmr_counter_enable(TMR5, TRUE);
}

void TMR5_GLOBAL_IRQHandler(void) // 1ms???
{
	if(tmr_flag_get(TMR5, TMR_OVF_FLAG) != RESET)
  {
    tmr_flag_clear(TMR5, TMR_OVF_FLAG);
		TIM_Flag = 1; // ???????
  }
}

