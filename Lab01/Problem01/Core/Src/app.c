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

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
void App_Init(void)
{

}

void App_MainLoop(void)
{
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
	HAL_Delay(200);
}

