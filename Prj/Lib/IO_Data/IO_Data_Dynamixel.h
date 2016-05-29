/*
 * IO_Data_Servo.h
 *
 *  Created on: 7 mars 2015
 *      Author: luten
 */

#ifndef IO_DATA_SERVO_H_
#define IO_DATA_SERVO_H_

#define IO_SERVO_DATA_OFFSET 		24
#define IO_SERVO_DATA_SIZE 			25

#define IO_SERVO_MODEL_NUMBER_OFFSET		 0
#define IO_SERVO_FIRMWARE_VERSION_OFFSET	 2
#define IO_SERVO_RETURN_DELAY_TIME_OFFSET	 5
#define IO_SERVO_TORQUE_ENABLE_OFFSET		24
#define IO_SERVO_LED_ON_OFFSET				25
#define IO_SERVO_GOAL_POSITION_OFFSET		30
#define IO_SERVO_MOVING_SPEED_OFFSET		32
#define IO_SERVO_PRESENT_POSITION_OFFSET	36
#define IO_SERVO_PRESENT_SPEED_OFFSET		38
#define IO_SERVO_MOVING_OFFSET				46

#define IO_SERVO_GOAL_POSITION_GET( address ) 			IO_Data_Servo_Read_Word( address , IO_SERVO_GOAL_POSITION_OFFSET )
#define IO_SERVO_GOAL_POSITION_SET( address , data ) 	IO_Data_Servo_Write_Word( address , IO_SERVO_GOAL_POSITION_OFFSET , data  )
#define IO_SERVO_MOVING_SPEED_GET( address ) 			IO_Data_Servo_Read_Word( address , IO_SERVO_MOVING_SPEED_OFFSET )
#define IO_SERVO_MOVING_SPEED_SET( address , data ) 	IO_Data_Servo_Write_Word( address , IO_SERVO_MOVING_SPEED_OFFSET , data )
#define IO_SERVO_PRESENT_POSITION_GET( address )		IO_Data_Servo_Read_Word( address , IO_SERVO_PRESENT_POSITION_OFFSET )
#define IO_SERVO_PRESENT_SPEED_GET( address )			IO_Data_Servo_Read_Word( address , IO_SERVO_PRESENT_SPEED_OFFSET )
#define IO_SERVO_MOVING( address )						IO_Data_Servo_Read_Byte( address , IO_SERVO_MOVING_OFFSET )
#define IO_SERVO_TORQUE_ENABLE(address,data) 			IO_Data_Servo_Write_Byte( address , IO_SERVO_TORQUE_ENABLE_OFFSET , data!=0 )
#define IO_SERVO_LED_ON(address,data) 					IO_Data_Servo_Write_Byte( address , IO_SERVO_LED_ON_OFFSET , data!=0 )

uint8_t IO_Data_Servo_Read_Byte( uint8_t ucIndex  , uint8_t ucOffset);
uint16_t IO_Data_Servo_Read_Word( uint8_t ucIndex  , uint8_t ucOffset);
void  IO_Data_Servo_Write_Byte( uint8_t ucIndex  , uint8_t ucOffset , uint8_t ucData);
void  IO_Data_Servo_Write_Word( uint8_t ucIndex  , uint8_t ucOffset , uint16_t uiData);
 void IO_Data_Servo_init( void );
 int IO_Data_Servo_Scan_In_Process( Task_Info_t *pTask );
 int IO_Data_Servo_Scan_Out_Process( Task_Info_t *pTask );




#endif /* IO_DATA_SERVO_H_ */
