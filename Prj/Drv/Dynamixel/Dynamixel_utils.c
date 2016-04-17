/*
 * Dynamixel_utils.c
 *
 ******************************************************************************
    Copyright (C) 2016  Gwendal Le Gall
    This file is part of Medula Firmware.

    Medula Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Medula is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Medula.  If not, see <http://www.gnu.org/licenses/>.

  */


#define MODULE_NAME "DYNA"
#include <string.h>
#include "stm32f2xx_hal.h"
#include "Dynamixel.h"
#include "Dynamixel_p.h"
#include "Log.h"
#include "Coroutine.h"

#define PING_TIME_OUT 3

void Dynamixel_Ping_Send( tDynamixelBusHandle *pHandle , unsigned char ucId )
{
    Dynamixel_Send_Data_Buffer( pHandle ,ucId , INSTRUCTION_PING , 0 , (unsigned char *) 0 );
    pHandle->ucRXindex = 0;
    pHandle->ucRXLength = 6;

}

unsigned char Dynamixel_Ping_Result( tDynamixelBusHandle *pHandle , unsigned char *pucError )
{
    if( pHandle->ucState != STATE_RX_RESULT)
    {
    	if( (HAL_GetTick() - pHandle->uiTickRef ) > PING_TIME_OUT )
    	{
    		//time out!
    		pHandle->ucState = STATE_IDLE;
    		*pucError = 1;
    	}
        return 1;
    }



    pHandle->ucState = STATE_IDLE;
    *pucError = 0;
    return 0;
}


int Dynamixel_Bus_Scan( int *piTaskState , uint8_t ucBusindex )
{
	static tDynamixelBusHandle *pDynamixelBus=NULL;
	static uint8_t ucIndex;
	unsigned char ucErr=0;

	CR_TASK_INIT();
	pDynamixelBus = Dynamixel_Bus_Get_By_Index( ucBusindex );
	LOG_APP("Scan Start for bus %d",ucBusindex);
	for(ucIndex=0;ucIndex<254;ucIndex++)
	{
		CR_TASK_DELAY(5);
		Dynamixel_Ping_Send(pDynamixelBus,ucIndex);
		while( Dynamixel_Ping_Result(pDynamixelBus, &ucErr) && !ucErr)
		{
			CR_TASK_YELD();
		}
		if( !ucErr )
			LOG_APP("Found dynamixel slave id:%d",ucIndex);
	}
	LOG_APP("Bus Scan Stop");
	CR_TASK_END();
}
