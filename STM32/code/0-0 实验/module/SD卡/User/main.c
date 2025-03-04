#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "UART2.h"
/*
// 压力传感器
#include "pressure.h"
// sd卡读取
#include "msd.h" 
#include "ff.h"
*/
// 按键模块
#include "key.h"

#include "angle.h"

/*
extern vu8 SD_Card_Ready; // SD卡初始化成功标志
FATFS fs;            
FIL fsrc;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	
*/

int main()
{
	float fAcc[3], fGyro[3], fAngle[3], vol, pressure;
	
	u8 i = 0, ret = 1, key = 0, flag = 0, j = 0;
	u16 value = 0;
	
	char buffer[100], accBuffer[100], gyroBuffer[100], angleBuffer[100], magBuffer[100];
	
	SysTick_Init(72);
	KEY_Init();
	USART1_Init(9600);
	
	/*
	
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	ADC0_Pressure_Init();
	
	//res=0 ； 证明OK
	ret = MSD_Init();
	printf("初始化: %d\n", ret);
	// 串口初始化
	SD_Card_Ready = ret;
	
	if (ret != 0) {
		printf("SD卡初始化失败\n");
	}
	// 挂载
	res = f_mount(0, &fs);
	if (res != FR_OK) {
		printf("挂载失败，错误码: %d\n", res);
		// 处理挂载失败
	}

	res = f_open(&fsrc, "Test.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 ； 证明OK

	if (res != FR_OK) {
		printf("创建文件失败，错误码: %d\n", res);
		// 处理文件打开失败
	}
	
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	*/
	
	// 角度传感器初始化相关问题
	Usart2Init(9600);
	
	RS485_IO_Init();
	
	WitInit(WIT_PROTOCOL_MODBUS, 0x50);
	WitSerialWriteRegister(SensorUartSend);
	WitRegisterCallBack(CopeSensorData);
	WitDelayMsRegister(Delayms);
	printf("starting... \n");
	AutoScanSensor();
	
	while(1)
	{	
		key = KEY_Scan(0);   //扫描按键
		
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
			/*
			if(s_cDataUpdate & ACC_UPDATE)
			{
				snprintf(accBuffer, sizeof(accBuffer), "acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
				printf("accBuffer: %s", accBuffer);
				
				f_puts(accBuffer, &fsrc);
				
				s_cDataUpdate &= ~ACC_UPDATE;
			}
			if(s_cDataUpdate & GYRO_UPDATE)
			{
				snprintf(gyroBuffer, sizeof(gyroBuffer), "gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
				printf("gyroBuffer: %s", gyroBuffer);
				
				f_puts(gyroBuffer, &fsrc);
				
				s_cDataUpdate &= ~GYRO_UPDATE;
			}
			if(s_cDataUpdate & ANGLE_UPDATE)
			{
				snprintf(angleBuffer, sizeof(angleBuffer), "angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
				printf("angleBuffer: %s", angleBuffer);
				
				f_puts(angleBuffer, &fsrc);
				
				s_cDataUpdate &= ~ANGLE_UPDATE;
			}
			if(s_cDataUpdate & MAG_UPDATE)
			{
				snprintf(magBuffer, sizeof(magBuffer), "mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
				printf("magBuffer: %s", magBuffer);
				
				f_puts(magBuffer, &fsrc);
				
				s_cDataUpdate &= ~MAG_UPDATE;
			}
			*/
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
		
		// 压力传感器
		/*
		i++;
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
		
		// 按键模块触发关闭SD卡的读写
		switch(key)
		{
			case KEY1_PRESS:
				printf("按键1触发");
				flag = 1;
				break;
			case KEY2_PRESS: 
				printf("按键2触发");
			/*
				if (flag == 1) // 确保在关闭SD卡时文件已经打开
				{
					// 先同步数据到SD卡，确保文件完整写入
					res = f_sync(&fsrc);
					if (res == FR_OK) {
						printf("数据同步成功\n");
					} else {
						printf("数据同步失败，错误码: %d\n", res);
					}

					// 关闭文件
					res = f_close(&fsrc);
					if (res == FR_OK) {
						printf("文件关闭成功\n");
					} else {
						printf("文件关闭失败，错误码: %d\n", res);
					}

					// 取消挂载
					res = f_mount(0, NULL);
					if (res == FR_OK) {
						printf("SD卡取消挂载成功\n");
					} else {
						printf("SD卡取消挂载失败，错误码: %d\n", res);
					}
				}
				*/
				break;
			case KEY3_PRESS: 
				printf("按键3触发");
				break;
			case KEY4_PRESS: 
				printf("按键4触发");
				break;
		}
	}
	
}
