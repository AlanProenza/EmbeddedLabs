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
extern TIM_HandleTypeDef htim2; //Declared as extern because htim2 is defined in another file, main.c.

void App_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim2); //Enable the timer.
}

void App_MainLoop(void)
{
	//Do nothing in the main loop.
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}
