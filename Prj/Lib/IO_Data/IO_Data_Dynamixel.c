/*
 * IO_Data_Servo.c
 *
 *  Created on: 7 mars 2015
 *      Author: luten
 */

#include "string.h"
#include "stm32f2xx_hal.h"
#define MODULE_NAME "IO_DATA"
#include "Log.h"
#include "Dynamixel.h"
#include "IO_Data.h"
#include "Coroutine.h"
#include "Traces.h"
#define IO_BUS_COUNT 3
#define IO_SERVO_COUNT 18
#define DEFULAT_RETURN_DELAY_TIME 10
typedef struct {
	tDynamixelBusHandle *phBus;
	//UART_HandleTypeDef huart;
	uint8_t ucAdress;
	uint8_t tucDataIn[IO_SERVO_DATA_SIZE];
	uint8_t tucDataOut[IO_SERVO_DATA_SIZE];
} tIO_Servo;

tIO_Servo tServoList[IO_SERVO_COUNT];

void IO_Data_Servo_init(void) {
	uint8_t ucServoIndex, tucBuffer[2], ucError;
	tIO_Servo *pServo = &tServoList[0];

	Dynamixel_Init();

	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 1;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 2;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 3;
	pServo++;

	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 10;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 11;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(2);
	pServo->ucAdress = 12;
	pServo++;

	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 4;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 5;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 6;
	pServo++;

	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 13;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 14;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(1);
	pServo->ucAdress = 15;
	pServo++;

	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 16;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 17;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 18;
	pServo++;

	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 7;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 8;
	pServo++;
	pServo->phBus = Dynamixel_Bus_Get_By_Index(0);
	pServo->ucAdress = 9;
	pServo++;
	pServo = &tServoList[0];
	LOG_DBG("Servo list:");
	for (ucServoIndex = 0; ucServoIndex < IO_SERVO_COUNT;
			ucServoIndex++, pServo++) {
		LOG_DBG("Id: %d Bus:%d Address:%02d ", ucServoIndex,
				pServo->phBus->ucBusIndex, pServo->ucAdress);
		Dynamixel_Read_Data_Send(pServo->phBus, pServo->ucAdress,
				IO_SERVO_MODEL_NUMBER_OFFSET, 2);
		while (Dynamixel_Read_Data_Result(pServo->phBus, &ucError, tucBuffer)
				> 0)
			;
		LOG_DBG("Model: %02X%02X ", tucBuffer[0], tucBuffer[1]);
		Dynamixel_Read_Data_Send(pServo->phBus, pServo->ucAdress,
				IO_SERVO_FIRMWARE_VERSION_OFFSET, 1);
		while (Dynamixel_Read_Data_Result(pServo->phBus, &ucError, tucBuffer)
				> 0)
			;
		LOG_DBG("Firmware: %02X ", tucBuffer[0]);
		Dynamixel_Read_Data_Send(pServo->phBus, pServo->ucAdress,
				IO_SERVO_RETURN_DELAY_TIME_OFFSET, 1);
		while (Dynamixel_Read_Data_Result(pServo->phBus, &ucError, tucBuffer)
				> 0)
			;
		LOG_DBG("Return Delay time: %02X", tucBuffer[0]);
		//Trace_Out();
		if (tucBuffer[0] != DEFULAT_RETURN_DELAY_TIME) {
			LOG_DBG("\tSet Return Delay Time to:%d\n",
					DEFULAT_RETURN_DELAY_TIME);
			tucBuffer[0] = DEFULAT_RETURN_DELAY_TIME;
			Dynamixel_Write_Data_Send(pServo->phBus, pServo->ucAdress,
					IO_SERVO_RETURN_DELAY_TIME_OFFSET, 1, tucBuffer);
			while (Dynamixel_Busy(pServo->phBus) == 1)
				;
		}
		HAL_Delay(50);
	}

}

uint8_t IO_Data_Servo_Read_Byte(uint8_t ucIndex, uint8_t ucOffset) {
	return tServoList[ucIndex].tucDataIn[ucOffset - IO_SERVO_DATA_OFFSET];
}

uint16_t IO_Data_Servo_Read_Word(uint8_t ucIndex, uint8_t ucOffset) {
	uint16_t uiData = (uint16_t) tServoList[ucIndex].tucDataIn[ucOffset
			- IO_SERVO_DATA_OFFSET];

	uiData += ((uint16_t) tServoList[ucIndex].tucDataIn[ucOffset + 1
			- IO_SERVO_DATA_OFFSET]) << 8;
	return uiData;
}

void IO_Data_Servo_Write_Byte(uint8_t ucIndex, uint8_t ucOffset, uint8_t ucData) {
	tServoList[ucIndex].tucDataOut[ucOffset - IO_SERVO_DATA_OFFSET] = ucData;
}

void IO_Data_Servo_Write_Word(uint8_t ucIndex, uint8_t ucOffset,
		uint16_t uiData) {
	if( ucOffset == 32 )
		LOG_DBG("%d ",uiData);
	tServoList[ucIndex].tucDataOut[ucOffset - IO_SERVO_DATA_OFFSET] =
			(uint8_t) uiData;
	tServoList[ucIndex].tucDataOut[ucOffset + 1 - IO_SERVO_DATA_OFFSET] =
			(uint8_t) (uiData >> 8);
}

int IO_Data_Servo_Scan_In_Process_By_Bus(int *piTaskState, uint8_t ucBusIndex) {
	static uint8_t ucIndex[IO_BUS_COUNT], ucError[IO_BUS_COUNT];
	tIO_Servo *pServo;
	int iReturn;

	CR_TASK_INIT()


	for (ucIndex[ucBusIndex] = 0; ucIndex[ucBusIndex] < IO_SERVO_COUNT;
			ucIndex[ucBusIndex]++) {
		pServo = &tServoList[ucIndex[ucBusIndex]];
		if (pServo->phBus == Dynamixel_Bus_Get_By_Index(ucBusIndex)) {
			Dynamixel_Read_Data_Send(pServo->phBus, pServo->ucAdress,
					IO_SERVO_DATA_OFFSET, IO_SERVO_DATA_SIZE);
			do {
				CR_TASK_YELD();
				pServo = &tServoList[ucIndex[ucBusIndex]];
				iReturn = Dynamixel_Read_Data_Result(pServo->phBus,
						&ucError[ucBusIndex], pServo->tucDataIn);
			} while (iReturn > 0);
			if (iReturn == 0)
				memcpy(pServo->tucDataOut, pServo->tucDataIn,
						IO_SERVO_DATA_SIZE);
			else
				ucError[ucBusIndex] = 0;
		}
	}
	CR_TASK_END()

return 0;
}

int IO_Data_Servo_Scan_In_Process(int *piTaskState) {
static int ProcessState[IO_BUS_COUNT];
static int iBuzy = 0;

CR_TASK_INIT()

ProcessState[0] = 0;
ProcessState[1] = 0;
ProcessState[2] = 0;
do {
	iBuzy = 0;
	iBuzy |= IO_Data_Servo_Scan_In_Process_By_Bus(&ProcessState[0], 0);
	iBuzy |= IO_Data_Servo_Scan_In_Process_By_Bus(&ProcessState[1], 1);
	iBuzy |= IO_Data_Servo_Scan_In_Process_By_Bus(&ProcessState[2], 2);
	CR_TASK_YELD();
} while (iBuzy);
CR_TASK_END()

}

int IO_Data_Servo_Scan_Out_Process_By_Bus(int *piTaskState, uint8_t ucBusIndex) {
static uint8_t ucIndex[IO_BUS_COUNT], ucOffset[IO_BUS_COUNT],
	ucLen[IO_BUS_COUNT];
tIO_Servo *pServo;

CR_TASK_INIT()


for (ucIndex[ucBusIndex] = 0; ucIndex[ucBusIndex] < IO_SERVO_COUNT;
	ucIndex[ucBusIndex]++) {
ucOffset[ucBusIndex] = 0;
ucLen[ucBusIndex] = 0;
pServo = &tServoList[ucIndex[ucBusIndex]];
if (pServo->phBus == Dynamixel_Bus_Get_By_Index(ucBusIndex)) {
	while (ucOffset[ucBusIndex] < IO_SERVO_DATA_SIZE) {

		while (pServo->tucDataIn[ucOffset[ucBusIndex]]
				== pServo->tucDataOut[ucOffset[ucBusIndex]]
				&& ucOffset[ucBusIndex] < IO_SERVO_DATA_SIZE) {
			ucOffset[ucBusIndex]++;
		}
		while (pServo->tucDataIn[ucOffset[ucBusIndex] + ucLen[ucBusIndex]]
				!= pServo->tucDataOut[ucOffset[ucBusIndex] + ucLen[ucBusIndex]]
				&& ucOffset[ucBusIndex] + ucLen[ucBusIndex] < IO_SERVO_DATA_SIZE) {
			ucLen[ucBusIndex]++;
		}
		if (ucOffset[ucBusIndex] < IO_SERVO_DATA_SIZE) {
			if ((ucLen[ucBusIndex] & 1))
				ucLen[ucBusIndex]++;
			Dynamixel_Write_Data_Send(pServo->phBus, pServo->ucAdress,
					ucOffset[ucBusIndex] + IO_SERVO_DATA_OFFSET,
					ucLen[ucBusIndex],
					&(pServo->tucDataOut[ucOffset[ucBusIndex]]));
			while (Dynamixel_Busy(pServo->phBus) == 1) {
				CR_TASK_YELD();
				pServo = &tServoList[ucIndex[ucBusIndex]];
			}
		}
		ucOffset[ucBusIndex] += ucLen[ucBusIndex];
		ucLen[ucBusIndex] = 0;
	}
}
}
CR_TASK_END()
return 0;
}

int IO_Data_Servo_Scan_Out_Process(int *piTaskState) {
static int ProcessStatus[IO_BUS_COUNT];
static int iBuzy = 0;

CR_TASK_INIT()
;
ProcessStatus[0] = 0;
ProcessStatus[1] = 0;
ProcessStatus[2] = 0;
do {
iBuzy = 0;
iBuzy |= IO_Data_Servo_Scan_Out_Process_By_Bus(&ProcessStatus[0], 0);
iBuzy |= IO_Data_Servo_Scan_Out_Process_By_Bus(&ProcessStatus[1], 1);
iBuzy |= IO_Data_Servo_Scan_Out_Process_By_Bus(&ProcessStatus[2], 2);
CR_TASK_YELD();
} while (iBuzy);
CR_TASK_END()
return 0;
}
