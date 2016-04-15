/*
 * Log.h
 *
 *  Created on: 10 avr. 2016
 *      Author: luten
 */

#ifndef LOG_H_
#define LOG_H_

#include "Traces.h"
#ifndef MODULE_NAME
#error "MODULE_NAME must be define"
#endif

#define LOG_APP(...) Trace_log(MODULE_NAME,TRACE_LOG_APP,__FUNCTION__,__LINE__, __VA_ARGS__);
#define LOG_ERR(...) Trace_log(MODULE_NAME,TRACE_LOG_ERR,__FUNCTION__,__LINE__, __VA_ARGS__);
#define LOG_WRN(...) Trace_log(MODULE_NAME,TRACE_LOG_WNG,__FUNCTION__,__LINE__, __VA_ARGS__);
#define LOG_DBG(...) Trace_log(MODULE_NAME,TRACE_LOG_DBG,__FUNCTION__,__LINE__, __VA_ARGS__);
#define LOG_INF(...) Trace_log(MODULE_NAME,TRACE_LOG_INF,__FUNCTION__,__LINE__, __VA_ARGS__);

#endif /* LOG_H_ */
