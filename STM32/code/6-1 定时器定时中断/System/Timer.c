#include "stm32f10x.h"                  // Device header

// 1.声明了变量，在项目中自动找；头文件中的声明其实也是使用extern去使用的
extern uint16_t Num;

void Timer_Init(void) {
	// RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 该函数可以不写，定时器上电后默认使用的就是内部时钟
	TIM_InternalClockConfig(TIM2);
	
	// 初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	// 指定时钟分频（滤波器过滤信号，保证滤波）
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// 定时频率 为 1秒时 = 72MHz / 10000 - 1 + 1 / 7200 - 1+1
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 这里有一个问题！
	// 上电之后初始化完成后，会立即进入更新中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	// 这样手动把更新中断标志位清除一下，数字就会从0开始了
	
	// 使能更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// NVIC优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);
	
	// 运行控制，使能定时器
	TIM_Cmd(TIM2, ENABLE);
}

// 写中断函数
/*
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		Num ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
