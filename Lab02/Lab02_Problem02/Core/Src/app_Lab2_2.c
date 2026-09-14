/*
 * app.c
 *
 *  Created on: Jun 19, 2022
 *      Author: Xinrong Li
 */

/* Includes ------------------------------------------------------------------*/
#include "app.h"

/* Private define ------------------------------------------------------------*/

#define 	LED_PORT 		GPIOA
#define 	LED_PIN 		GPIO_PIN_5


/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


void App_Init(void)
{
	//Do nothing in app init.
}


void App_MainLoop(void)
{
	//Do nothing in the main loop.
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}
