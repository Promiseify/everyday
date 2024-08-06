#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void) 
{
	// 使用RCC开启GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// GPIO_Init第二个参数结构体类型 GPIO_InitTypeDef;
	GPIO_InitTypeDef GPIO_InitStructure;
	// 设置GPIO的工作模式（8种工作模式）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 采用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	// 使用GPIO_Init函数初始化GPIO
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1) {
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
		Delay_ms(500);
	}
}
