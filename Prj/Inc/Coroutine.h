/*
 * Coroutine.h
 *
 *  Created on: 16 avr. 2016
 *      Author: luten
 */

#ifndef COROUTINE_H_
#define COROUTINE_H_

typedef struct
{
	int iState;
	int iDelayInit;
	int iTimeoutInit;
} Task_Info_t;

#define TASK_INFO_INIT {0,0,0}
#define TASK_INFO_RESET( task)  task.iState=0,task.iDelayInit=0,task.iTimeoutInit=0

#define CR_TASK_INIT()       switch( pTask->iState ) { case 0:
#define CR_TASK_END()        pTask->iState=-1; default: pTask->iState=-1;} return 0;
#define CR_TASK_YELD()        \
        pTask->iState = __LINE__; \
        return 1;              \
        case __LINE__:

#define CR_TASK_DELAY( nb_ms )                    \
         pTask->iDelayInit= HAL_GetTick();             \
        pTask->iState = __LINE__;                     \
        return 1;                                    \
        case __LINE__:                                 \
        if((HAL_GetTick()- pTask->iDelayInit) < nb_ms) \
            return 1;

#define CR_TIMEOUT_INIT( value ) \
		 pTask->iTimeoutInit= value; \
		 pTask->iDelayInit= HAL_GetTick();

#define CR_TIMEOUT_TEST()  ((HAL_GetTick() -  pTask->iDelayInit)> pTask->iTimeoutInit)

#define CR_TASK_EXECUTE(task) while( (task) ) { CR_TASK_YELD();} \


#define CR_PRINTF( ... ) do  {dprintf(__VA_ARGS__); \
                            CR_TASK_DELAY(2) } while(0)


#endif /* COROUTINE_H_ */
