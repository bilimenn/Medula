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
#ifndef TRACE_H_
#define TRACE_H_
#define USE_FULL_ASSERT 1

#define TRACE_LOG_APP		0
#define TRACE_LOG_ERR		1
#define TRACE_LOG_WNG	2
#define TRACE_LOG_DBG		3
#define TRACE_LOG_INF		4

void Trace_Init( void );
void Trace_Raw( const char * format, ...  );
void Trace_Out( void );
void Trace_Init_Status( const char *Title , int iStatus );
void Trace_log(  const char *pcModuleName, int iErrorLevel , const char *pcFuncname , int iLine , const char * format, ... );

#endif /* TRACE_H_ */
