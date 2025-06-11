#ifndef __APP_H
#define __APP_H

#include <stdlib.h>
#include "string.h"
#include "stdio.h"
#include "string.h"
#include "arm_math.h"

#include "at32f413_wk_config.h"
#include "delay.h"
#include "timer.h"
#include "MPU6500.h"
#include "usart.h"
#include "Debug.h"
#include "AHRS.h"
#include "led.h"
#include "adc.h"
#include "AT32F413RC_FOC_LIB.h"
#include "Control.h"
#include "Gpio_Config.h"
#include "key.h"
#include "Encoder.h"
#include "flash.h"
#include "Calibration.h"
#include "RcData.h"
#include "WS2812.h"

void app_main(void);

#endif //APP_H
