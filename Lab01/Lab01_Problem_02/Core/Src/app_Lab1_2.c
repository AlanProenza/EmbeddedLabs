/*
* app.c
*
* Created on: Jun 19, 2022
* Author: Xinrong Li
*/

/* Includes ------------------------------------------------------------------*/
#include "app.h"

/* Private define ------------------------------------------------------------*/
#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_5
#define BUTTON_PORT GPIOC
#define BUTTON_PIN GPIO_PIN_13

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
void App_Init(void)
{

}

void App_MainLoop(void)
{
	if(HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == 0) {
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
	}
}
