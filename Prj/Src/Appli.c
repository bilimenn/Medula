/*
 * Appli.c
 *
 *  Created on: 17 avr. 2016
 *      Author: luten
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
#define MODULE_NAME "APPLI"
#include <string.h>
#include "stm32f2xx_hal.h"
#include "Coroutine.h"
#include "Dynamixel.h"
#include "Dynamixel_p.h"
#include "IO_Data.h"
#include "Log.h"


int Appli( Task_Info_t *pTask  )
{
	static int iServoIndex=0;
	static int Moving;

	CR_TASK_INIT();

		while(1)
	{
		LOG_APP("Speed set to 50");
		for( iServoIndex=0;iServoIndex<6;iServoIndex++)
		{
			IO_SERVO_MOVING_SPEED_SET( iServoIndex , 200);
		}
		CR_TASK_YELD();
		LOG_APP("512 position set");
		do
		{
			Moving=0;
			for( iServoIndex=0;iServoIndex<6;iServoIndex++)
			{
				Moving|=IO_SERVO_MOVING(iServoIndex);
			}
			CR_TASK_YELD();
		}while(Moving);
		for( iServoIndex=0;iServoIndex<6;iServoIndex++)
		{
			IO_SERVO_GOAL_POSITION_SET( iServoIndex , 512);
		}
		CR_TASK_YELD();
		CR_TASK_DELAY(2000);
		LOG_APP("500 position set");
		for( iServoIndex=0;iServoIndex<6;iServoIndex++)
		{
			IO_SERVO_GOAL_POSITION_SET( iServoIndex , 400);
		}
		CR_TASK_YELD();
		CR_TASK_DELAY(2000);
		//return 1;

	}
	CR_TASK_END();
}
