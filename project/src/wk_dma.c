/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_dma.c
  * @brief    work bench config program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "wk_dma.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init dma1 channel1 for "adc1"
  * @param  none
  * @retval none
  */
void wk_dma1_channel1_init(void)
{
  /* add user code begin dma1_channel1 0 */

  /* add user code end dma1_channel1 0 */

  dma_init_type dma_init_struct;

  dma_reset(DMA1_CHANNEL1);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_LOW;
  dma_init_struct.loop_mode_enable = TRUE;
  dma_init(DMA1_CHANNEL1, &dma_init_struct);
	
  /* flexible function enable */
  dma_flexible_config(DMA1, FLEX_CHANNEL1, DMA_FLEXIBLE_ADC1);
  /* add user code begin dma1_channel1 1 */

  /* add user code end dma1_channel1 1 */
}

/**
  * @brief  config dma channel transfer parameter
  * @param  dmax_channely: DMAx_CHANNELy
  * @param  peripheral_base_addr: peripheral address.
  * @param  memory_base_addr: memory address.
  * @param  buffer_size: buffer size.
  * @retval none
  */
void wk_dma_channel_config(dma_channel_type* dmax_channely, uint32_t peripheral_base_addr, uint32_t memory_base_addr, uint16_t buffer_size)
{
  /* add user code begin dma_channel_config 0 */

  /* add user code end dma_channel_config 0 */

  dmax_channely->dtcnt = buffer_size;
  dmax_channely->paddr = peripheral_base_addr;
  dmax_channely->maddr = memory_base_addr;

  /* add user code begin dma_channel_config 1 */

  /* add user code end dma_channel_config 1 */
}

/* add user code begin 1 */

/* add user code end 1 */
