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
/*!
 *  \file Traces.h
 *
 *  \defgroup TraceGrp Trace Module
 *  @{
 */
#define USE_FULL_ASSERT 1

#define TRACE_LOG_APP		0
#define TRACE_LOG_ERR		1
#define TRACE_LOG_WNG	2
#define TRACE_LOG_DBG		3
#define TRACE_LOG_INF		4

/*!
 * \brief trace module initialization
 *
 * \note must be call before using trace functions
 */
void Trace_Init( void );

/*!
 * \brief Send raw trace on serial port
 *
 *  \note no CR LF at the end of line
 */
void Trace_Raw( const char * format, ...  );

/*!
 *  \brief initialization traces OK/Error
 *
 *
 */
void Trace_Init_Status( const char *Title , int iStatus );

/*!
 *  \brief generic log function
 */
void Trace_log(  const char *pcModuleName, int iErrorLevel , const char *pcFuncname , int iLine , const char * format, ... );


/*!
 *  \brief trace task
 *
 */
void Trace_Task( void );

/**@}*/
#endif /* TRACE_H_ */

