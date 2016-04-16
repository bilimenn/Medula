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
#include "Dynamixel.h"
#include "Log.h"
#include "Coroutine.h"

int Dynamixel_test( int *piTaskDelayInit )
{
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
}
