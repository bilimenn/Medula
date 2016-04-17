#include "string.h"
#include "stm32f2xx_hal.h"
#include "Medula_conf.h"
#define MODULE_NAME "IO_DATA"
#include "Log.h"
#include "Dynamixel.h"
#include "IO_Data.h"
#include "Coroutine.h"






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
	int iServoState=0;

	do
	{
		iBuzy = 0;

		iBuzy |= IO_Data_Servo_Scan_In_Process(&iServoState);
		//iBuzy |= IO_Data_Adc_Scan_In_Process( &iAdcState );
		//iBuzy |= IO_Data_Imu_Scan_In_Process( &iImuState );
		//iBuzy |= IO_Data_Echo_Scan_In_Process(&iEchoState);

	} while(iBuzy);
}


void IO_Data_Scan_Out( void )
{
	int iServoState=0;
	//IO_Data_Servo_Scan_Out();
	while(IO_Data_Servo_Scan_Out_Process(&iServoState));
}







