/*
 * Coroutine.h
 *
 *  Created on: 16 avr. 2016
 *      Author: luten
 */

#ifndef COROUTINE_H_
#define COROUTINE_H_


#define CR_TASK_INIT()       static int iTaskDelayInit=0,iTimeoutInit;(void)iTaskDelayInit;(void)iTimeoutInit; switch( *piTaskState ) { case 0:
#define CR_TASK_END()        *piTaskState=-1; default: *piTaskState=-1;} return 0;
#define CR_TASK_YELD()        \
        *piTaskState = __LINE__; \
        return 1;              \
        case __LINE__:

#define CR_TASK_DELAY( nb_ms )                    \
        iTaskDelayInit= HAL_GetTick();             \
        *piTaskState = __LINE__;                     \
        return 1;                                    \
        case __LINE__:                                 \
        if((HAL_GetTick()-iTaskDelayInit) < nb_ms) \
            return 1;

#define CR_TIMEOUT_INIT( value ) \
		iTimeoutInit= value; \
		iTaskDelayInit= HAL_GetTick();

#define CR_TIMEOUT_TEST()  ((HAL_GetTick() - iTaskDelayInit)>iTimeoutInit)

#define CR_TASK_EXECUTE(task) while( (task) ) { CR_TASK_YELD();} \


#define CR_PRINTF( ... ) do  {dprintf(__VA_ARGS__); \
                            CR_TASK_DELAY(2) } while(0)


#endif /* COROUTINE_H_ */
