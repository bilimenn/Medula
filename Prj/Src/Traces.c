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


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "stm32f2xx_hal.h"

#define TRACE_OUTPUT_BUFFER_SIZE 1024

 char tcOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE];
int iIndex = 0;

UART_HandleTypeDef huart6;

void Trace_Init( void )
{
	iIndex = 0;
}

void Trace_Print( const char * format, ...  )
{
	int iMaxSize = TRACE_OUTPUT_BUFFER_SIZE - iIndex - 1;
	  va_list args;
	  if( (TRACE_OUTPUT_BUFFER_SIZE-iIndex)>1 )
	  {
		  va_start (args, format);
		  iIndex += vsnprintf (&tcOutputBuffer[iIndex],iMaxSize,format, args);
		  va_end (args);
	  }
}

void Trace_Out( void )
{
	if( iIndex )
	{
		tcOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE-1]=0;
		HAL_UART_Transmit_DMA( &huart6 ,(uint8_t *) tcOutputBuffer, iIndex );
		iIndex = 0;
	}
}
