#include "stm32f10x.h"
#include "msd.h" 
#include "ff.h"
#include "stdio.h"
extern char file_num;//选中的文件标号
extern DIR start_dirs; //目录起点信息
extern vu8 SD_Card_Ready;//SD卡初始化成功标志
FATFS fs;            
FIL fsrc, fdst,file;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

static const u8 txt_buf[10]={1,2,3,4,5,6,7,8,9,10};

	  
int main(void)
{	
 	u8 ret = 1;	
	ret = MSD_Init();
	SD_Card_Ready = ret;//ret=0 ； 证明Ready
	
	res=f_mount(0, &fs);//res=0 ； 证明OK
  res=f_open(&fsrc,"MEng.txt", FA_CREATE_ALWAYS | FA_WRITE);//res=0 ； 证明OK
	res = f_write(&fsrc, txt_buf, 10, &bw);//写入BMP首部//res=0 ； 证明OK
	
	f_close(&fsrc);
  f_mount(0, NULL);
	
	while( 1 )
	{	
	}
}




