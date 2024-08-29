#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"

int main()
{
	u8 i=0;
	u16 t=0;
	u16 len=0;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	USART1_Init(115200);
	LED_Init();
	
	while(1)
	{	
		if(USART1_RX_STA&0x8000)
		{					   
			len=USART1_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART1_RX_BUF[t]);         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			USART1_RX_STA=0;
		}
		i++;
		if(i%10==0)
			LED0=!LED0;

		delay_ms(10);
	}
}
