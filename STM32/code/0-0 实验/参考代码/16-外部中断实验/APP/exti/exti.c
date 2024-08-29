#include "exti.h"
#include "led.h"
#include "SysTick.h"
#include "key.h"


/*******************************************************************************
* �� �� ��         : My_EXTI_Init
* ��������		   : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource14);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource13);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);//ѡ��GPIO�ܽ������ⲿ�ж���·
	
	//EXTI12-15 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//EXTI�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* �� �� ��         : EXTI15_10_IRQHandler
* ��������		   : �ⲿ�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line12)==1)
	{
		//delay_ms(10);
		if(KEY4==0)
			LED2=1;	
	}
	else if(EXTI_GetITStatus(EXTI_Line13)==1)
	{
		//delay_ms(10);
		if(KEY3==0)
			LED2=0;	
	}
	else if(EXTI_GetITStatus(EXTI_Line14)==1)
	{
		//delay_ms(10);
		if(KEY2==0)
			LED1=1;	
	}
	else if(EXTI_GetITStatus(EXTI_Line15)==1)
	{
		//delay_ms(10);
		if(KEY1==0)
			LED1=0;	
	}
	
	EXTI_ClearITPendingBit(EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15);
}
