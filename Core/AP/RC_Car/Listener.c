/*
 * Listener.c
 *
 *  Created on: Apr 26, 2024
 *      Author: k1min
 */


#include "Listener.h"

UART_HandleTypeDef *myHuart;

//extern uint8_t rcvData;
Que_t uart2RxQue;
uint8_t CarModeBuf[20];
uint8_t index_carmodebuf;
uint8_t CarModeState_Li;

/*
 * Listener
 * 1. Receive a string via UART to decide modeState & save in Model
 *
 */

void Listener_ISR_Process(uint8_t rcvData)
{
	enQue_CarModeState(rcvData);
	if(rcvData == '\n')			// Check the last char in a string
	{
		printf("rxCmplt\n");		// for debug
	}
}

void Listener_init()
{
	CarModeState_Li = OFF;
	Listener_clearModeBuf();
}

void Listener_CarMode_EventCheck()
{
  uint8_t ch = deQue_CarModeState();
	if(Que_Car_isEmpty())
	{
		memset(CarModeBuf, 0, sizeof(CarModeBuf));
		index_carmodebuf = 0;
	}
	if(ch)
	{
		printf("%c\n", ch);		// for debug
		CarModeBuf[index_carmodebuf++] = ch;
	}

	if (strcmp(CarModeBuf, "OFF") == 0)
	{
		CarModeState_Li = OFF;
		Model_setCarModeState(CarModeState_Li);
		printf("%s\n", CarModeBuf);		// for debug
		Listener_clearModeBuf();
	}
	else if (strcmp(CarModeBuf, "FORW") == 0)
	{
		CarModeState_Li = FORWARD;
		Model_setCarModeState(CarModeState_Li);
		printf("%s\n", CarModeBuf);		// for debug
		Listener_clearModeBuf();
	}
	else if (strcmp(CarModeBuf, "BACK") == 0)
	{
		CarModeState_Li = BACKWARD;
		Model_setCarModeState(CarModeState_Li);
		Listener_clearModeBuf();
	}
	else if (strcmp(CarModeBuf, "RIGHT") == 0)
	{
		CarModeState_Li = RIGHT_FORWARD;
		Model_setCarModeState(CarModeState_Li);
		Listener_clearModeBuf();
	}
	else if (strcmp(CarModeBuf, "LEFT") == 0)
	{
		CarModeState_Li = LEFT_FORWARD;
		Model_setCarModeState(CarModeState_Li);
		Listener_clearModeBuf();
	}
}

void Listener_clearModeBuf()
{
	memset(CarModeBuf, 0, sizeof(CarModeBuf));
	index_carmodebuf = 0;
	printf("ClearBuffer\n");		// for debug
}
