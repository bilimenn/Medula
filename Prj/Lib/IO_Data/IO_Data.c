#include "string.h"
#include "stm32f2xx_hal.h"
#include "Medula_conf.h"
#define MODULE_NAME "IO_DATA"
#include "Log.h"
#include "Coroutine.h"
#include "Dynamixel.h"
#include "IO_Data.h"




void IO_Data_init( void )
{
#ifdef USE_DYNAMIXEL
	IO_Data_Servo_init();
#endif
#ifdef USE_ECHO
	IO_Data_Echo_Init();
#endif
}


void IO_Data_Scan_In( void )
{
	int iBuzy=0;
	//int iServoState=0,iAdcState=0 , iImuState=0 ,iEchoState=0;
	Task_Info_t ServoState=TASK_INFO_INIT;

	do
	{
		iBuzy = 0;

		iBuzy |= IO_Data_Servo_Scan_In_Process(&ServoState);
		//iBuzy |= IO_Data_Adc_Scan_In_Process( &iAdcState );
		//iBuzy |= IO_Data_Imu_Scan_In_Process( &iImuState );
		//iBuzy |= IO_Data_Echo_Scan_In_Process(&iEchoState);

	} while(iBuzy);
}


void IO_Data_Scan_Out( void )
{
	Task_Info_t ServoState=TASK_INFO_INIT;
	//IO_Data_Servo_Scan_Out();
	while(IO_Data_Servo_Scan_Out_Process(&ServoState));
}







