/*
 * Presenter.c
 *
 *  Created on: Apr 26, 2024
 *      Author: k1min
 */

#include "Presenter.h"

extern UART_HandleTypeDef huart2;
extern Motor_t hLeftMotor, hRightMotor;

/*
 * Presenter
 * : Execute output hardware actions for each mode
 * 1. UART : printf output
 * 2. Motor : Forward, Back, ...
 *
 */

int _write(int file, char *ptr, int len)		// for printf() function
{
	HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 1000);

	return len;
}

void Presenter_Motor_Run(uint8_t state)
{
	switch (state)
	{
		case OFF:
			Motor_Stop(&hLeftMotor);
			Motor_Stop(&hRightMotor);
			break;

		case FORWARD:
			Motor_Forward(&hLeftMotor);
			Motor_Forward(&hRightMotor);
			break;

		case BACKWARD:
			Motor_Backward(&hLeftMotor);
			Motor_Backward(&hRightMotor);
			break;

		case RIGHT_FORWARD:
			Motor_Forward(&hLeftMotor);
			Motor_Forward(&hRightMotor);
			break;

		case LEFT_FORWARD:
			Motor_Forward(&hLeftMotor);
			Motor_Forward(&hRightMotor);
			break;
	}
}

void Presenter_UART_Run(uint8_t state)
{
	switch (state)
	{
		case OFF:
			printf("Mode : OFF\n");
			break;

		case FORWARD:
			printf("Mode : Forward\n");
			break;

		case BACKWARD:
			printf("Mode : Backward\n");
			break;

		case RIGHT_FORWARD:
			printf("Mode : RightForward\n");
			break;

		case LEFT_FORWARD:
			printf("Mode : LeftForward\n");
			break;
	}
}
