/** @file barcode.c
 *  @brief An API to control Barcode Scanner
 *
 *  This file includes the functions to control the Barcode Scanner.
 *  The fuctions are exposed to application layer.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Implement Barcode Scanner On Off functions.
 */
 
/* Includes ------------------------------------------------------------------*/
#include "barcode.h"
#include "system.h"



 /**
 * @brief Turns on the Barcode scanner
 *
 * Sets the corresponding GPIO high to turn on the Barcode scanner. (Regulator 3.3 V)
 *
 * @param void
 * @return void
 */
void barcode_Turn_On(void)
{	
	HAL_GPIO_WritePin(REG_3V3_EN_GPIO_Port, REG_3V3_EN_Pin, GPIO_PIN_SET);			
}

/**
 * @brief Turns off the Barcode scanner 
 *
 * Sets the corresponding GPIO low to turn off the Barcode scanner. (Regulator 3.3 V)
 *
 * @param void
 * @return void
 */
void barcode_Turn_Off(void)
{
	HAL_GPIO_WritePin(REG_3V3_EN_GPIO_Port, REG_3V3_EN_Pin, GPIO_PIN_RESET);	
}
	
