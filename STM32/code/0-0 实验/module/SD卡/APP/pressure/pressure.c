#include "stm32f10x.h"
// 校准参数
#define SENSOR_RANGE 100.0f     // 传感器总量程 (单位: kg)
#define MAX_VOLTAGE 5.0f        // 传感器输出电压的最大值 (单位: V)
#define MIN_VOLTAGE 0         // 传感器输出电压的最小值 (单位: V)
#define ZERO_VOLTAGE 0.0f        // 空载时的电压 (单位: V)

void ADC0_Pressure_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t Get_AD0_Value(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

// 将ADC值转换为电压
float Get_ADC_Value_to_Voltage(uint16_t adc_value) {
    return (float)adc_value * (3.3f / 4095.0f);  // 假设ADC参考电压为3.3V，12位分辨率
}

// 将电压转换为重量
float Get_Voltage_to_Pressure(float voltage) {
    // 计算重量
    return (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * SENSOR_RANGE;
}
