#include "stm32f10x.h"                  // Device header
#include "Delay.c"

int main(void) {
	// 使用RCC开启GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIO_Init第二个参数结构体类型 GPIO_InitTypeDef;
	GPIO_InitTypeDef GPIO_InitStructure;
	// 设置GPIO的工作模式（8种工作模式）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 采用推挽输出
	// sGPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	// 使用GPIO_Init函数初始化GPIO
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1) {
		// 使用这两种方式闪烁灯的方式完成
		GPIO_Write(GPIOA, ~0x0001);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0002);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0004);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0008);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0010);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0020);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0040);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x0080);
		Delay_ms(500);
	}
}
