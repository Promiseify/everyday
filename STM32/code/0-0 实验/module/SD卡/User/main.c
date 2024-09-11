#include "system.h"
#include "SysTick.h"
#include "usart.h"
// 压力传感器
#include "pressure.h"
// sd卡读取
#include "msd.h" 
#include "ff.h"
// 按键模块
#include "key.h"


// extern char file_num;//选中的文件标号
// extern DIR start_dirs; //目录起点信息
extern vu8 SD_Card_Ready;//SD卡初始化成功标志
FATFS fs;            
FIL fsrc;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

int main()
{
	u8 i = 0, ret = 1, key = 0, flag = 0;
	u16 value = 0;
	float vol; // 电压
	float pressure; // 压力
	char buffer[100];
	
	SysTick_Init(72);
	
	KEY_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	
	ADC0_Pressure_Init();
	
	USART1_Init(115200);
	
	//res=0 ； 证明OK
	ret = MSD_Init();
	printf("初始化: %d\n", ret);
	// 串口初始化
	SD_Card_Ready = ret;
	// 挂载
	res = f_mount(0, &fs);
	printf("挂载: %d\n", ret);
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 ； 证明OK
	printf("创建文件: %d\n", ret);
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	
	// f_close(&fsrc);
	// f_mount(0, NULL);
	
	while(1)
	{	
		i++;
		key = KEY_Scan(0);   //扫描按键
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
		
		// 按键模块触发关闭SD卡的读写
		switch(key)
		{
			case KEY1_PRESS:
				printf("按键1触发");
				flag = 1;
				break;
			case KEY2_PRESS: 
				printf("按键2触发");
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
