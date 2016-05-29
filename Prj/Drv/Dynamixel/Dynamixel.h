/**
  ******************************************************************************
    Copyright (C) 2016  Gwendal Le Gall
    This file is part of Medula Firmware.

    Medula Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.


  */
#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H
#define TX_BUFER_SIZE 256
#define RX_BUFER_SIZE 256

typedef struct
{
	unsigned char ucBusIndex;
	unsigned char ucTargetAddress;
	UART_HandleTypeDef *phUuart;
	unsigned char tucCommandBuffer[256];
	unsigned char tucTxBuffer[TX_BUFER_SIZE];
	unsigned char ucTXindex;
	unsigned char ucTXLength;
	unsigned char ucRXindex;
	unsigned char ucRXLength;
	unsigned char tucRxBuffer[RX_BUFER_SIZE];
	unsigned char ucState;
	unsigned char ucErrorCode;
	unsigned char *pucCommandParams;
	TIM_HandleTypeDef    *pTimHandle;
	uint32_t uiTickRef;
} tDynamixelBusHandle;

void Dynamixel_Init(void );
tDynamixelBusHandle *Dynamixel_Bus_Get_By_Index( uint8_t ucIndex);
int Dynamixel_Busy( tDynamixelBusHandle *pHandle  );
void Dynamixel_Read_Data_Send( tDynamixelBusHandle *pHandle ,  unsigned char ucAddress , unsigned char ucMemOffset , unsigned char ucLength  );
int Dynamixel_Read_Data_Result( tDynamixelBusHandle *pHandle , unsigned char *pucError ,  unsigned char *pucData );
void Dynamixel_Ping_Send( tDynamixelBusHandle *pHandle , unsigned char ucId );
unsigned char Dynamixel_Ping_Result( tDynamixelBusHandle *pHandle , unsigned char *pucError );
void Dynamixel_Write_Data_Send( tDynamixelBusHandle *pHandle , unsigned char ucId , unsigned char ucAddress , unsigned char ucLength   , unsigned char *pucData);

int Dynamixel_test( Task_Info_t *pTask );
int Dynamixel_Bus_Scan(  Task_Info_t *pTask , uint8_t ucBusindex );
#endif
