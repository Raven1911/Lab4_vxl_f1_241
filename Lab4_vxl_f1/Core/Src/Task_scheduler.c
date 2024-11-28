/*
 * Task_scheduler.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Admin
 */


#include "Task_scheduler.h"


void Toggle_Red(){
	HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
}

void Toggle_Yellow(){
	HAL_GPIO_TogglePin(Led_Yellow_GPIO_Port, Led_Yellow_Pin);
}

void Toggle_Green(){
	HAL_GPIO_TogglePin(Led_Green_GPIO_Port, Led_Green_Pin);
}


void Toggle_Red2(){
	HAL_GPIO_TogglePin(Led_Red2_GPIO_Port, Led_Red2_Pin);
}

void Toggle_Yellow2(){
	HAL_GPIO_TogglePin(Led_Yellow2_GPIO_Port, Led_Yellow2_Pin);
}

void Toggle_Green2(){
	HAL_GPIO_TogglePin(Led_Green2_GPIO_Port, Led_Green2_Pin);
}
