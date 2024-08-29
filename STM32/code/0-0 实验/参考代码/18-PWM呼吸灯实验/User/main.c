#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "pwm.h"

int main()
{
	u8 i=0;
	u8 fx=0;
	u16 j=0;
	
	SysTick_Init(72);
	LED_Init();
	TIM3_CH2_PWM_Init(500,72-1); //频率是2Kh
	
	while(1)
	{	
		if(fx==0)
		{
			j++;
			if(j==300)
				fx=1;
		}
		else
		{
			j--;
			if(j==0)
				fx=0;
		}
		TIM_SetCompare2(TIM3,j);  //i值最大可以取499，因为ARR最大值是499.
		
		i++;
		if(i%10==0)
			LED0=!LED0;

		delay_ms(10);
	}
}
