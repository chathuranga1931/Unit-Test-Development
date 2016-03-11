/** @file led.h
 *  @brief An API to control LEDs
 *
 *  This exposes includes the functions to control the LEDs.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Add LED On Off functions.
 */
 
 /* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

 /* Public Functions ----------------------------------------------------------*/
 
 /**
 * @brief Turns on an LED as specified by led_idx
 *
 * Sets the corresponding GPIO high to turn on an LED.
 * Input parameter must be validated before calling this function.
 *
 * @param led_idx 	The peripheral ID of the LED to be turned on 
 * @return void
 */
void led_Turn_On(uint8_t led_idx);

/**
 * @brief Turns off an LED as specified by led_idx
 *
 * Sets the corresponding GPIO low to turn off an LED.
 * Input parameter must be validated before calling this function.
 *
 * @param led_idx 	The peripheral ID of the LED to be turned off 
 * @return void
 */
void led_Turn_Off(uint8_t led_idx);
