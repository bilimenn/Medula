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
#include "Traces.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define TRACE_OUTPUT_BUFFER_SIZE 512

 char tcOutputBufferPing[TRACE_OUTPUT_BUFFER_SIZE];
 char tcOutputBufferPong[TRACE_OUTPUT_BUFFER_SIZE];
 char *pcOutputBuffer=NULL;
 int iIndex = 0;

UART_HandleTypeDef huart6;

	static const char tcLogApp[] = "APP";
	static const char tcLogError[] = ANSI_COLOR_RED"ERR"ANSI_COLOR_RESET;
	static const char tcLogWarning[] = ANSI_COLOR_YELLOW"WRN"ANSI_COLOR_RESET;
	static const char tcLogDebug[] = ANSI_COLOR_BLUE"DBG"ANSI_COLOR_RESET;
	static const char tcLogInfo[] = ANSI_COLOR_GREEN"INF"ANSI_COLOR_RESET;
	static const char *pcLogText[TRACE_LOG_INF+1] = {tcLogApp,tcLogError,tcLogWarning,tcLogDebug,tcLogInfo};

void Trace_Init( void )
{
	iIndex = 0;
	pcOutputBuffer = tcOutputBufferPing;
}

void Trace_Raw( const char * format, ...  )
{
	int iMaxSize = TRACE_OUTPUT_BUFFER_SIZE - iIndex - 2;
	int iLastIndex=iIndex,iTickCount=0;
	  va_list args;
	  if( (TRACE_OUTPUT_BUFFER_SIZE-iIndex)>1 )
	  {
		  va_start (args, format);
		  iIndex += vsnprintf (&pcOutputBuffer[iIndex],iMaxSize,format, args);
		  if( iIndex >= 511 )
		  {
			  iIndex = iLastIndex;
			  while( HAL_UART_GetState( &huart6 ) != HAL_UART_STATE_READY )
			  {
				  HAL_Delay(1);
				  iTickCount++;
			  }
			  Trace_Out();
			  iIndex += vsnprintf (&pcOutputBuffer[iIndex],TRACE_OUTPUT_BUFFER_SIZE-1,format, args);
			  iIndex += snprintf(&pcOutputBuffer[iIndex],TRACE_OUTPUT_BUFFER_SIZE-iIndex-1,"Trace wait:%dms\r\n",iTickCount);
		  }
		  va_end (args);
	  }

}

void Trace_Init_Status( const char *Title , int iStatus )
{
	if( iStatus )
		Trace_Raw("%X %d %-40s ["ANSI_COLOR_RED"Error"ANSI_COLOR_RESET"]\r\n",(int)pcOutputBuffer,iIndex,Title);
	else
		Trace_Raw("%X %d %-40s ["ANSI_COLOR_GREEN"Ok"ANSI_COLOR_RESET"]\r\n",(int)pcOutputBuffer,iIndex,Title);
	Trace_Out();
}

void Trace_log(  const char *pcModuleName, int iErrorLevel , const char *pcFuncname , int iLine , const char * format, ... )
{
	char tcLogLineBuffer[80];
	va_list args;
	va_start (args, format);
	if( iErrorLevel > TRACE_LOG_INF)
		iErrorLevel = 0;
	vsnprintf(tcLogLineBuffer,sizeof(tcLogLineBuffer),format,args);
	Trace_Raw("[%-8s][%s][%s():%d] %s\r\n",pcModuleName,pcLogText[iErrorLevel],pcFuncname,iLine,tcLogLineBuffer);
	va_end (args);
}

void Trace_Out( void )
{
	if( iIndex )
	{
		if( HAL_UART_GetState( &huart6 ) == HAL_UART_STATE_READY )
		{
			pcOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE-1]=0;
			HAL_UART_Transmit_DMA( &huart6 ,(uint8_t *) pcOutputBuffer, iIndex );
			if( pcOutputBuffer == tcOutputBufferPing )
			{
				pcOutputBuffer = tcOutputBufferPong;
			}
			else
			{
				pcOutputBuffer = tcOutputBufferPing;
			}
			iIndex = 0;
		}
	}
}
