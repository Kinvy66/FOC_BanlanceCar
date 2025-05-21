/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_A_Pin GPIO_PIN_13
#define KEY_A_GPIO_Port GPIOC
#define PWER_EN_Pin GPIO_PIN_14
#define PWER_EN_GPIO_Port GPIOC
#define BAT_Pin GPIO_PIN_0
#define BAT_GPIO_Port GPIOC
#define TEMP1_Pin GPIO_PIN_2
#define TEMP1_GPIO_Port GPIOC
#define TEMP2_Pin GPIO_PIN_3
#define TEMP2_GPIO_Port GPIOC
#define MPU_CS_Pin GPIO_PIN_4
#define MPU_CS_GPIO_Port GPIOA
#define MPU_CLK_Pin GPIO_PIN_5
#define MPU_CLK_GPIO_Port GPIOA
#define MPU_MISO_Pin GPIO_PIN_6
#define MPU_MISO_GPIO_Port GPIOA
#define MPU_MOSI_Pin GPIO_PIN_7
#define MPU_MOSI_GPIO_Port GPIOA
#define M1_ADC1_IN14_Pin GPIO_PIN_4
#define M1_ADC1_IN14_GPIO_Port GPIOC
#define M1_ADC1_IN15_Pin GPIO_PIN_5
#define M1_ADC1_IN15_GPIO_Port GPIOC
#define M2_ADC2_IN8_Pin GPIO_PIN_0
#define M2_ADC2_IN8_GPIO_Port GPIOB
#define M2_ADC2_IN9_Pin GPIO_PIN_1
#define M2_ADC2_IN9_GPIO_Port GPIOB
#define M2_CS_Pin GPIO_PIN_12
#define M2_CS_GPIO_Port GPIOB
#define M2_PWM1_Pin GPIO_PIN_6
#define M2_PWM1_GPIO_Port GPIOC
#define M2_PWM2_Pin GPIO_PIN_7
#define M2_PWM2_GPIO_Port GPIOC
#define M2_PWM3_Pin GPIO_PIN_8
#define M2_PWM3_GPIO_Port GPIOC
#define M1_PWM1_Pin GPIO_PIN_8
#define M1_PWM1_GPIO_Port GPIOA
#define M1_PWM2_Pin GPIO_PIN_9
#define M1_PWM2_GPIO_Port GPIOA
#define M1_PWM3_Pin GPIO_PIN_10
#define M1_PWM3_GPIO_Port GPIOA
#define MPU_INT_Pin GPIO_PIN_2
#define MPU_INT_GPIO_Port GPIOD
#define MPU_TIM2_Pin GPIO_PIN_3
#define MPU_TIM2_GPIO_Port GPIOB
#define M1_CS_Pin GPIO_PIN_5
#define M1_CS_GPIO_Port GPIOB
#define RGB1_Pin GPIO_PIN_8
#define RGB1_GPIO_Port GPIOB
#define RGB2_Pin GPIO_PIN_9
#define RGB2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
