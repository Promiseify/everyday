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

#include "wit_c_sdk.h"
#include "UART1.h"
#include "UART2.h"
#include "angle.h"


#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;

extern vu8 SD_Card_Ready;//SD����ʼ���ɹ���־
FATFS fs;            
FIL fsrc;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

int main()
{
	float fAcc[3], fGyro[3], fAngle[3];
	int j;
	
	u8 i = 0, ret = 1, key = 0, flag = 0;
	u16 value = 0;
	/*
	float vol; // ��ѹ
	float pressure; // ѹ��
	char buffer[100];
	
	SysTick_Init(72);
	
	KEY_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	
	ADC0_Pressure_Init();
	*/
	USART1_Init(9600);
	
	//res=0 �� ֤��OK
	ret = MSD_Init();
	printf("��ʼ��: %d\n", ret);
	// ���ڳ�ʼ��
	SD_Card_Ready = ret;
	
	if (ret != 0) {
		printf("SD����ʼ��ʧ��\n");
	}
	// ����
	res = f_mount(0, &fs);
	if (res != FR_OK) {
		printf("����ʧ�ܣ�������: %d\n", res);
		// �������ʧ��
	}

	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 �� ֤��OK

	if (res != FR_OK) {
		printf("�����ļ�ʧ�ܣ�������: %d\n", res);
		// �����ļ���ʧ��
	}
	
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	
	// �Ƕȴ�������ʼ���������
	Usart2Init(9600);
	
	RS485_IO_Init();
	
	WitInit(WIT_PROTOCOL_MODBUS, 0x50);
	WitSerialWriteRegister(SensorUartSend);
	WitRegisterCallBack(CopeSensorData);
	WitDelayMsRegister(Delayms);
	AutoScanSensor();
	
	while(1)
	{	
		WitReadReg(AX, 12);
		delay_ms(500);
		CmdProcess();
		if(s_cDataUpdate)
		{
			for(j = 0; j < 3; j++)
			{
				fAcc[j] = sReg[AX+j] / 32768.0f * 16.0f;
				fGyro[j] = sReg[GX+j] / 32768.0f * 2000.0f;
				fAngle[j] = sReg[Roll+j] / 32768.0f * 180.0f;
			}
			if(s_cDataUpdate & ACC_UPDATE)
			{
				printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
				s_cDataUpdate &= ~ACC_UPDATE;
			}
			if(s_cDataUpdate & GYRO_UPDATE)
			{
				printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
				s_cDataUpdate &= ~GYRO_UPDATE;
			}
			if(s_cDataUpdate & ANGLE_UPDATE)
			{
				printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
				s_cDataUpdate &= ~ANGLE_UPDATE;
			}
			if(s_cDataUpdate & MAG_UPDATE)
			{
				printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
				s_cDataUpdate &= ~MAG_UPDATE;
			}
		}
		
		/*
		i++;
		key = KEY_Scan(0);   //ɨ�谴��
		if (flag == 0)
		{
			if (i % 100 == 0)
			{
				value = Get_AD0_Value();
				
				vol = Get_ADC_Value_to_Voltage(value);
				
				pressure = Get_Voltage_to_Pressure(vol);
				
				snprintf(buffer, sizeof(buffer), "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
				printf("buffer: %s", buffer);
				f_puts(buffer, &fsrc);
			}
			
			delay_ms(10);
		}
		*/
		
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
