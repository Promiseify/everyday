#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count = 0;

// 中断初始化
void CountSensor_Init(void) {
	// 1.配置RCC，将涉及到的外设的时钟打开
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// 2.配置GPIO，选择我们的端口为输入模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 3.配置AFIO，选择我们用的这一路的GPIO，连接到后面的EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式 另一个是事件模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 我这里选择下降沿触发
	
	// 4.配置EXTI
	EXTI_Init(&EXTI_InitStructure);
	
	// 5.配置NVIC，给中断选择一个合适的优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
}

uint16_t Get_CountSensor_Count(void) {
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line14) == SET) {
		
		CountSensor_Count++;
		// 如果不清除中断的EXTI的标志位，那么循环就会一直触发当前中断就一直在当前中断里边
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
