#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "pressure.h"


int main()
{
	u8 i=0;
	u16 value=0;
	float vol;
	float pressure;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	USART1_Init(115200);
	ADC0_Pressure_Init();
	
	printf("start...");
	while(1)
	{	
		i++;
		
		if(i%100==0)
		{
			value = Get_AD0_Value();
			printf("���ADֵΪ��%d\r\n",value);
			vol = Get_ADC_Value_to_Voltage(value);
			printf("����ѹֵΪ��%.2fV\r\n", vol);
			pressure = Get_Voltage_to_Pressure(vol);
			printf("�������Ϊ��%.2fkg\r\n", pressure);
		}
		delay_ms(10);
		
		
	}
}
