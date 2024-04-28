/*
 * defineModel.c
 *
 *  Created on: Apr 27, 2024
 *      Author: k1min
 */

#include "defineModel.h"

/*
 * Model
 * 1. Manage all #define used in the AP
 * 2. Manage all hardware (Motor, Ultrasonic, ...)
 * 3. Store various states
 */

extern UART_HandleTypeDef huart2;
Button_t Button_1, Button_2, Button_3;
LED_t LED_1, LED_2, LED_3;
Ultrasonic_t LeftUltra, CenterUltra, RightUltra;
Motor_t hLeftMotor, hRightMotor;
//htim_t hTIM;

uint8_t CarModeState_Mo;


void Model_hardwareinit(TIM_HandleTypeDef *motor_htim, TIM_HandleTypeDef *UltraLeft_htim,
		TIM_HandleTypeDef *UltraCenter_htim, TIM_HandleTypeDef *UltraRight_htim)
{
	Motor_init(&hLeftMotor, motor_htim, TIM_CHANNEL_1, LEFT_DIR1_Port,
			LEFT_DIR1_Port_Pin, LEFT_DIR2_Port, LEFT_DIR2_Port_Pin);
	Motor_init(&hRightMotor, motor_htim, TIM_CHANNEL_2, RIGHT_DIR1_Port,
			RIGHT_DIR1_Port_Pin, RIGHT_DIR2_Port, RIGHT_DIR2_Port_Pin);
}


int _write(int file, char *ptr, int len)		// for printf() function
{
	HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 1000);

	return len;
}


uint8_t Model_getCarModeState()
{
	return CarModeState_Mo;
}
void Model_setCarModeState(uint8_t data)
{
	CarModeState_Mo = data;
}
