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
	u8 i = 0, ret = 1, key = 0, flag = 0;
	u16 value = 0;
	float vol; // ��ѹ
	float pressure; // ѹ��
	char buffer[100];
	
	SysTick_Init(72);
	
	KEY_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	
	ADC0_Pressure_Init();
	
	USART1_Init(115200);
	
	//res=0 �� ֤��OK
	ret = MSD_Init();
	printf("��ʼ��: %d\n", ret);
	// ���ڳ�ʼ��
	SD_Card_Ready = ret;
	// ����
	res = f_mount(0, &fs);
	printf("����: %d\n", ret);
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 �� ֤��OK
	printf("�����ļ�: %d\n", ret);
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	
	// f_close(&fsrc);
	// f_mount(0, NULL);
	
	while(1)
	{	
		i++;
		key = KEY_Scan(0);   //ɨ�谴��
		if (flag == 0)
		{
			if (i % 100 == 0)
			{
				value = Get_AD0_Value();
				
				vol = Get_ADC_Value_to_Voltage(value);
				
				pressure = Get_Voltage_to_Pressure(vol);
				
				sprintf(buffer, "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
				printf("buffer: %s", buffer);
				f_puts(buffer, &fsrc);
			}
			
			delay_ms(10);
		}
		
		// ����ģ�鴥���ر�SD���Ķ�д
		switch(key)
		{
			case KEY1_PRESS:
				printf("����1����");
				flag = 1;
				break;
			case KEY2_PRESS: 
				printf("����2����");
				if (flag == 1) // ȷ���ڹر�SD��ʱ�ļ��Ѿ���
				{
					// ��ͬ�����ݵ�SD����ȷ���ļ�����д��
					res = f_sync(&fsrc);
					if (res == FR_OK) {
						printf("����ͬ���ɹ�\n");
					} else {
						printf("����ͬ��ʧ�ܣ�������: %d\n", res);
					}

					// �ر��ļ�
					res = f_close(&fsrc);
					if (res == FR_OK) {
						printf("�ļ��رճɹ�\n");
					} else {
						printf("�ļ��ر�ʧ�ܣ�������: %d\n", res);
					}

					// ȡ������
					res = f_mount(0, NULL);
					if (res == FR_OK) {
						printf("SD��ȡ�����سɹ�\n");
					} else {
						printf("SD��ȡ������ʧ�ܣ�������: %d\n", res);
					}
				}
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
