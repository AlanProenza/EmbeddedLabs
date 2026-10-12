/*
 * app.c
 *
 *  Created on: July 12, 2022
 *      Author: Xinrong Li
 */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "stm32l4xx_hal.h"
#include "app.h"

/* Private define ------------------------------------------------------------*/
#define 	LED_PORT 			GPIOA
#define 	LED_PIN 			GPIO_PIN_5

#define 	LED_MODE_OFF		0
#define 	LED_MODE_ON			1
#define 	LED_MODE_FLASHING	2

#define 	DAC_DATA_RANGE				0x00FF
#define		DAC_SAMPLES_PER_PERIOD		21


/* Private function prototypes -----------------------------------------------*/
void ShowCommands(void);
void UART_TransmitString(UART_HandleTypeDef *p_huart, char a_string[], int newline);


/* Extern global variables ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart2;
extern DAC_HandleTypeDef hdac1;


//Should be declared as volatile if variables' values are changed in ISR.
volatile char rxData;  //One byte data received from UART
volatile int ledMode = LED_MODE_FLASHING;

volatile int dacDataIndex = 0;


void App_Init(void) {
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);

	UART_TransmitString(&huart2, "-----------------", 1);
	UART_TransmitString(&huart2, "~ Nucleo-L476RG ~", 1);
	UART_TransmitString(&huart2, "-----------------", 1);

	ShowCommands();

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_UART_Receive_IT(&huart2, (uint8_t*) &rxData, 1); //Start the Rx interrupt.

	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
}


void App_MainLoop(void) {

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *p_htim) {

	uint32_t dacData;

	if (p_htim == &htim3) {
	    if (ledMode == LED_MODE_FLASHING) {
		    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
	    }
	}

	if (p_htim == &htim2) {
		dacData = (uint32_t) (((float) dacDataIndex/(DAC_SAMPLES_PER_PERIOD - 1)) * DAC_DATA_RANGE);
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacData);

		dacDataIndex += 1;
		if (dacDataIndex >= DAC_SAMPLES_PER_PERIOD) {
			dacDataIndex = 0;
		}

	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *p_huart) {
	//Process the data received from UART.
	switch (rxData) {
	case 'I':
	case 'i':
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
		ledMode = LED_MODE_ON;
		break;
	case 'O':
	case 'o':
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
		ledMode = LED_MODE_OFF;
		break;
	case 'F':
	case 'f':
		ledMode = LED_MODE_FLASHING;
		break;
	case 'H':
	case 'h':
		ShowCommands();
		break;
	}

	HAL_UART_Receive_IT(p_huart, (uint8_t*) &rxData, 1); //Restart the Rx interrupt.
}

void ShowCommands(void) {
	UART_TransmitString(&huart2, "Type on keyboard to send command from PC to MCU:", 1);
	UART_TransmitString(&huart2, "> I: turn on LED, O: turn off LED, F: flashing LED, H: show commands", 1);
}

void UART_TransmitString(UART_HandleTypeDef *p_huart, char a_string[], int newline) {
	HAL_UART_Transmit(p_huart, (uint8_t*) a_string, strlen(a_string), HAL_MAX_DELAY);
	if (newline != 0) {
		HAL_UART_Transmit(p_huart, (uint8_t*) "\n\r", 2, HAL_MAX_DELAY);
	}
}
