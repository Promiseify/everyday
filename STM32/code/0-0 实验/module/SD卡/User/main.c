#include "system.h"
#include "SysTick.h"
#include "usart.h"
// ѹ��������
#include "pressure.h"
// sd����ȡ
#include "msd.h" 
#include "ff.h"
// ����ģ��
#include "key.h"


// extern char file_num;//ѡ�е��ļ����
// extern DIR start_dirs; //Ŀ¼�����Ϣ
extern vu8 SD_Card_Ready;//SD����ʼ���ɹ���־
FATFS fs;            
FIL fsrc;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

int main()
{
	u8 i = 0, ret = 1, key = 0;
	u16 value = 0;
	float vol; // ��ѹ
	float pressure; // ѹ��
	char buffer[100];
	char timeBuffer[100];

	SysTick_Init(72);
	
	KEY_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	
	ADC0_Pressure_Init();
	
	USART1_Init(115200);
	
	//res=0 �� ֤��OK
	ret = MSD_Init();
	// ���ڳ�ʼ��
	SD_Card_Ready = ret;
	// ����
	res = f_mount(0, &fs);
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_OPEN_ALWAYS);//res=0 �� ֤��OK
	
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	
	// f_close(&fsrc);
	// f_mount(0, NULL);
	
	while(1)
	{	
		i++;
		key = KEY_Scan(0);   //ɨ�谴��
		sprintf(timeBuffer, "time: %d\r\n", i);
		f_puts(timeBuffer, &fsrc);
		
		if (i % 100 == 0)
		{
			value = Get_AD0_Value();
			printf("���ADֵΪ��%d\r\n", value);
			
			vol = Get_ADC_Value_to_Voltage(value);
			printf("����ѹֵΪ��%.2fV\r\n", vol);
			
			pressure = Get_Voltage_to_Pressure(vol);
			printf("�������Ϊ��%.2fkg\r\n", pressure);
			
			sprintf(buffer, "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
			f_puts(buffer, &fsrc);
		}
		
		delay_ms(10);
		
		// ����ģ�鴥���ر�SD���Ķ�д
		switch(key)
		{
			case KEY1_PRESS:
				printf("����1����");
				f_close(&fsrc);
				f_mount(0, NULL);
				break;
			case KEY2_PRESS: 
				printf("����2����");
				break;
			case KEY3_PRESS: 
				printf("����3����");
				break;
			case KEY4_PRESS: 
				printf("����4����");
				break;
		}
	}
	
}
