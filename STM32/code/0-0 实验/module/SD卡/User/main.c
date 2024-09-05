#include "system.h"
#include "SysTick.h"
#include "usart.h"
// ѹ��������
#include "pressure.h"
// sd����ȡ
#include "msd.h" 
#include "ff.h"


// extern char file_num;//ѡ�е��ļ����
// extern DIR start_dirs; //Ŀ¼�����Ϣ
extern vu8 SD_Card_Ready;//SD����ʼ���ɹ���־
FATFS fs;            
FIL fsrc;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

int main()
{
	u8 i=0;
	u16 value=0;
	float vol;
	float pressure;
	char buffer[100];
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	ADC0_Pressure_Init();
	USART1_Init(115200);
	
	printf("start...");
	
	u8 ret = 1;	
	ret = MSD_Init();
	// ���ڳ�ʼ��
	SD_Card_Ready = ret;//ret=0 �� ֤��Ready
	// ����
	res = f_mount(0, &fs);//res=0 �� ֤��OK
	// �򿪻��ߴ���һ���ļ�
	// &fsrcָ��հ�file��ָ��
	// Test.txtָ����ļ���
	// ����ģʽ���ļ���ģʽ��־
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_OPEN_ALWAYS);//res=0 �� ֤��OK
	
	const TCHAR *start_text = "start writing!\r\n";
	
	f_puts(start_text, &fsrc);
	
	f_close(&fsrc);
	
	f_mount(0, NULL);
	
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
			
			sprintf(buffer, "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
			f_puts(buffer, &fsrc);
		}
		delay_ms(10);
		
	}
}
