#include "stm32f10x.h"                  // Device header

int main(void) {
	// 使用RCC开启GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIO_Init第二个参数结构体类型 GPIO_InitTypeDef;
	GPIO_InitTypeDef GPIO_InitStructure;
	// 设置GPIO的工作模式（8种工作模式）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 采用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	// 使用GPIO_Init函数初始化GPIO
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 使用输出或者输入的函数控制GPIO口
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); // pin0端口设置低电平，点灯操作完成
	
	while(1) {
		
	}
}
