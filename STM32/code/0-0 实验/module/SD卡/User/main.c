#include "system.h"
#include "SysTick.h"
#include "usart.h"
// 压力传感器
#include "pressure.h"
// sd卡读取
#include "msd.h" 
#include "ff.h"


// extern char file_num;//选中的文件标号
// extern DIR start_dirs; //目录起点信息
extern vu8 SD_Card_Ready;//SD卡初始化成功标志
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	ADC0_Pressure_Init();
	USART1_Init(115200);
	
	printf("start...");
	
	u8 ret = 1;	
	ret = MSD_Init();
	// 串口初始化
	SD_Card_Ready = ret;//ret=0 ； 证明Ready
	// 挂载
	res = f_mount(0, &fs);//res=0 ； 证明OK
	// 打开或者创建一个文件
	// &fsrc指向空白file的指针
	// Test.txt指向的文件名
	// 访问模式和文件打开模式标志
	res = f_open(&fsrc,"Test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_OPEN_ALWAYS);//res=0 ； 证明OK
	
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
			printf("检测AD值为：%d\r\n",value);
			vol = Get_ADC_Value_to_Voltage(value);
			printf("检测电压值为：%.2fV\r\n", vol);
			pressure = Get_Voltage_to_Pressure(vol);
			printf("检测重量为：%.2fkg\r\n", pressure);
			
			sprintf(buffer, "AD: %d, vol: %.2fV, weight: %.2fkg\r\n", value, vol, pressure);
			f_puts(buffer, &fsrc);
		}
		delay_ms(10);
		
	}
}
