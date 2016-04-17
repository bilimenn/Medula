/*
 * Dynamixel_p.h
 *
 *  Created on: 17 avr. 2016
 *      Author: luten
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

#ifndef DYNAMIXEL_P_H_
#define DYNAMIXEL_P_H_

/* INTRUCTION */
#define INSTRUCTION_PING        0x01
#define INSTRUCTION_READ_DATA   0x02
#define INSTRUCTION_WRITE_DATA  0x03

#define STATE_IDLE      0
#define STATE_TX        1
#define STATE_WAITRX    2
#define STATE_RX_READ   3
#define STATE_RX_RESULT 4
unsigned char Dynamixel_Send_Data_Buffer( tDynamixelBusHandle *pHandle , unsigned char ucAddress , unsigned char ucInstruction , unsigned char ucLength, unsigned char *pucData );

#endif /* DYNAMIXEL_P_H_ */
