#include "system.h"
#include "SysTick.h"
#include "usart.h"
// ѹ��������
#include "pressure.h"
// sd����ȡ
#include "msd.h" 
#include "ff.h"


extern char file_num;//ѡ�е��ļ����
extern DIR start_dirs; //Ŀ¼�����Ϣ
extern vu8 SD_Card_Ready;//SD����ʼ���ɹ���־
FATFS fs;            
FIL fsrc, fdst, file;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

static const u8 txt_buf[10]={1,2,3,4,5,6,7,8,9,10};

int main()
{
	/*u8 i=0;
	u16 value=0;
	float vol;
	float pressure;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	USART1_Init(115200);
	ADC0_Pressure_Init();
	
	
	*/
	printf("start...");
	
	u8 ret = 1;	
	ret = MSD_Init();
	// ���ڳ�ʼ��
	USART1_Init(115200);
	SD_Card_Ready = ret;//ret=0 �� ֤��Ready
	printf("ret:%d\n", ret);
	res = f_mount(0, &fs);//res=0 �� ֤��OK
	printf("res1:%d\n", res);
	res = f_open(&fsrc,"MEng.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 �� ֤��OK
	printf("res2:%d\n", res);
	res = f_write(&fsrc, txt_buf, 10, &bw);//д��BMP�ײ�//res=0 �� ֤��OK
	printf("res3:%d\n", res);
	f_close(&fsrc);
	f_mount(0, NULL);
	
	while(1)
	{	
		
		/*
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
		*/
		
	}
}
