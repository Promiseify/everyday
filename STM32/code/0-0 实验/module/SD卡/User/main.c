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
	u8 i = 0, ret = 1, key = 0;
	u16 value = 0;
	float vol; // 电压
	float pressure; // 压力
	char buffer[100];
	char timeBuffer[100];

	SysTick_Init(72);
	
	KEY_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	
	ADC0_Pressure_Init();
	
	USART1_Init(115200);
	
	//res=0 ； 证明OK
	ret = MSD_Init();
	// 串口初始化
	SD_Card_Ready = ret;
	// 挂载
	res = f_mount(0, &fs);
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_OPEN_ALWAYS);//res=0 ； 证明OK
	
	const TCHAR *start_text = "start writing!\r\n";
	f_puts(start_text, &fsrc);
	
	// f_close(&fsrc);
	// f_mount(0, NULL);
	
	while(1)
	{	
		i++;
		key = KEY_Scan(0);   //扫描按键
		sprintf(timeBuffer, "time: %d\r\n", i);
		f_puts(timeBuffer, &fsrc);
		
		if (i % 100 == 0)
		{
			value = Get_AD0_Value();
			printf("检测AD值为：%d\r\n", value);
			
			vol = Get_ADC_Value_to_Voltage(value);
			printf("检测电压值为：%.2fV\r\n", vol);
			
			pressure = Get_Voltage_to_Pressure(vol);
			printf("检测重量为：%.2fkg\r\n", pressure);
			
			sprintf(buffer, "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
			f_puts(buffer, &fsrc);
		}
		
		delay_ms(10);
		
		// 按键模块触发关闭SD卡的读写
		switch(key)
		{
			case KEY1_PRESS:
				printf("按键1触发");
				f_close(&fsrc);
				f_mount(0, NULL);
				break;
			case KEY2_PRESS: 
				printf("按键2触发");
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
