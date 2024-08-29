#ifndef _pressure_H
#define _pressure_H

#include "system.h"

void ADC0_Pressure_Init(void);
uint16_t Get_AD0_Value(void);
float Get_ADC_Value_to_Voltage(uint16_t adc_value);
float Get_Voltage_to_Pressure(float voltage);

#endif
