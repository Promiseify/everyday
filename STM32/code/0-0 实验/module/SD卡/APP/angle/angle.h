#ifndef _angle_H
#define _angle_H

#include "system.h"

void CopeCmdData(unsigned char ucData);
void CmdProcess(void);
void RS485_IO_Init(void);
void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
void Delayms(uint16_t ucMs);
void CopeSensorData(uint32_t uiReg, uint32_t uiRegNum);
void AutoScanSensor(void);


#endif
