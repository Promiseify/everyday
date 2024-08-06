#include "stm32f10x.h"                  // Device header

// LED初始化函数
void LED_Init(void) {
	// 使用RCC开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 使用GPIO_Init函数初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// LED灯采用低电平电量，目前设置成高电平，LED默认熄灭
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void LED1_ON(void) {
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED1_OFF(void) {
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

// LED灯显示反转
void LED1_Turn(void) {
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

void LED2_ON(void) {
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2_OFF(void) {
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED2_Turn(void) {
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}


