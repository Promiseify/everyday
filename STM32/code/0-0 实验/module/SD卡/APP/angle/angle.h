#ifndef _angle_H
#define _angle_H

#include "system.h"
#include "wit_c_sdk.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;

void CopeCmdData(unsigned char ucData);
void CmdProcess(void);
void RS485_IO_Init(void);
void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
void Delayms(uint16_t ucMs);
void CopeSensorData(uint32_t uiReg, uint32_t uiRegNum);
void AutoScanSensor(void);


#endif
