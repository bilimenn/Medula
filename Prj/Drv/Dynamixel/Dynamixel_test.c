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
#define MODULE_NAME "DYNA"
#include <string.h>
#include "stm32f2xx_hal.h"
#include "Coroutine.h"
#include "Dynamixel.h"
#include "Dynamixel_p.h"
#include "Log.h"

#define IO_SERVO_DATA_OFFSET 		24
#define IO_SERVO_DATA_SIZE 			25

int Dynamixel_test(  Task_Info_t *pTask )
{
#ifdef PINg_TEST
	static tDynamixelBusHandle *pDynamixelBus=NULL;
	static uint8_t tDataBuffer[64];
	unsigned char ucErr=0;
	CR_TASK_INIT();
	LOG_APP("Test Start");
	Dynamixel_Init();
	pDynamixelBus = Dynamixel_Bus_Get_By_Index( 0 );
	LOG_APP("Ping test:");
	Dynamixel_Ping_Send(pDynamixelBus,8);
	CR_TIMEOUT_INIT(100);
	while( Dynamixel_Ping_Result(pDynamixelBus, &ucErr) && !CR_TIMEOUT_TEST())
	{
		CR_TASK_YELD();
	}
	if( !CR_TIMEOUT_TEST() )
		LOG_APP("Ping done: ok");
	else
		LOG_APP("Ping done: Error");
	CR_TASK_END();
#endif
#ifdef SCAN_TEST
	static Task_Info_t State=TASK_INFO_INIT;
	CR_TASK_INIT();
	LOG_APP("Test Start");
	Dynamixel_Init();
	CR_TASK_EXECUTE(Dynamixel_Bus_Scan(&State,0));
	State.iState=0;
	CR_TASK_EXECUTE(Dynamixel_Bus_Scan(&State,1));
	State.iState=0;
	CR_TASK_EXECUTE(Dynamixel_Bus_Scan(&State,2));
	CR_TASK_END();
#endif
	//static Task_Info_t State=TASK_INFO_INIT;
	static tDynamixelBusHandle *pDynamixelBus=NULL;
	static int iReturn;
	static unsigned char ucError;
	static unsigned char tucBuff[128];
	CR_TASK_INIT();
	LOG_APP("Test Start");
	Dynamixel_Init();
	pDynamixelBus = Dynamixel_Bus_Get_By_Index( 2 );
	CR_TASK_YELD();
	while( 1 )
	{
		CR_TASK_DELAY(15);
		ucError=0;
		Dynamixel_Read_Data_Send(pDynamixelBus, 4 , IO_SERVO_DATA_OFFSET, IO_SERVO_DATA_SIZE);
		do
		{
			CR_TASK_YELD();
			iReturn = Dynamixel_Read_Data_Result(pDynamixelBus,&ucError,tucBuff);
		} while (iReturn > 0);
		if( ucError && ucError!=0xff)
			ucError=0;
		ucError=0;
		while( Dynamixel_Busy(pDynamixelBus))
		{
			CR_TASK_YELD();
		}
		Dynamixel_Read_Data_Send(pDynamixelBus, 15 , IO_SERVO_DATA_OFFSET, IO_SERVO_DATA_SIZE);
		do
		{
			CR_TASK_YELD();
			iReturn = Dynamixel_Read_Data_Result(pDynamixelBus,&ucError,tucBuff);
		} while (iReturn > 0);
		if( ucError && ucError!=0xff)
			ucError=0;
	}
	CR_TASK_END();
}
