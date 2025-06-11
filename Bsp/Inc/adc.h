#ifndef __adc_H
#define __adc_H
#include "app.h"

extern float Car_VoltVin;

void TriggerADC_Init(void);
void ADC_Config(void);
void Get_ADCTemp(void);
void Get_InputVolt(void);

#endif
