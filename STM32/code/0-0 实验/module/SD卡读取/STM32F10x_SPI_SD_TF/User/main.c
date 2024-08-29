#include "system.h"
#include "msd.h" 
#include "ff.h"
#include "usart.h"

extern char file_num;//ѡ�е��ļ����
extern DIR start_dirs; //Ŀ¼�����Ϣ
extern vu8 SD_Card_Ready;//SD����ʼ���ɹ���־
FATFS fs;            
FIL fsrc, fdst, file;      // file objects
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count	

static const u8 txt_buf[10]={1,2,3,4,5,6,7,8,9,10};

	  
int main(void)
{	

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
	
	while( 1 )
	{	
		
	}
}




