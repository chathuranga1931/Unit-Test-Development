/** @file barcode.h
 *  @brief An API to control Barcode Scanner
 *
 *  This exposes includes the functions to control the Barcode Scanner.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Add Barcode reader On Off functions.
 */
 
 /* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

 /* Public Functions ----------------------------------------------------------*/
 
 /**
 * @brief Turns on the Barcode scanner
 *
 * Sets the corresponding GPIO high to turn on the Barcode scanner. (Regulator 3.3 V)
 *
 * @param void
 * @return void
 */
void barcode_Turn_On(void);

/**
 * @brief Turns off the Barcode scanner 
 *
 * Sets the corresponding GPIO low to turn off the Barcode scanner. (Regulator 3.3 V)
 *
 * @param void
 * @return void
 */
void barcode_Turn_Off(void);
