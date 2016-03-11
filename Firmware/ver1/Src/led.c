/** @file led.c
 *  @brief An API to control LEDs
 *
 *  This file includes the functions to control the LEDs.
 *  The fuctions are exposed to application layer.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Implement LED On Off functions.
 */
 
/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "system.h"

/**
 * @brief Turns on an LED as specified by led_idx
 *
 * Sets the corresponding GPIO high to turn on an LED.
 * Input parameter must be validated before calling this function.
 *
 * @param led_idx 	The peripheral ID of the LED to be turned on 
 * @return void
 */
void led_Turn_On(uint8_t led_idx)
{
	switch(led_idx)
	{
		case LED0:
			HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
			break;
		case LED1:
			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
			break;
		case LED2:
			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
	}	
}

/**
 * @brief Turns off an LED as specified by led_idx
 *
 * Sets the corresponding GPIO low to turn off an LED.
 * Input parameter must be validated before calling this function.
 *
 * @param led_idx 	The peripheral ID of the LED to be turned off 
 * @return void
 */
void led_Turn_Off(uint8_t led_idx)
{
	switch(led_idx)
	{
		case LED0:
			HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
			break;
		case LED1:
			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
			break;
		case LED2:
			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}	
}
	
