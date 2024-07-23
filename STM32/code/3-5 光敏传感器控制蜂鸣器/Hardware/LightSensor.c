#include "stm32f10x.h"                  // Device header


void LightSensor_Init(void) {
	// 使用RCC开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 使用GPIO_Init函数初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t LightSensor_Get(void) {
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
