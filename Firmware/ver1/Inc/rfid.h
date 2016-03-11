/** @file rfid.h
 *  @brief An API to control LEDs
 *
 *  This exposes includes the functions to control the RFID Scanner.
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

 /* Definitions ---------------------------------------------------------------*/
 #define TICK_CNT_100US		(800)
 
 /* Public Functions ----------------------------------------------------------*/
 
 /**
 * @brief Turns on the RFID scanner
 *
 * Sets the corresponding GPIO low to turn on the RFID scanner. 
 *
 * @param void
 * @return void
 */
void rfid_Turn_On(void);

/**
 * @brief Turns off the RFID scanner 
 *
 * Sets the corresponding GPIO high to turn off the RFID scanner. 
 *
 * @param void
 * @return void
 */
void rfid_Turn_Off(void);

/**
 * @brief Resets the RFID scanner 
 *
 * Sets the corresponding GPIO low for a specified time (>25us)
 * and set it back to high
 *
 * @param void
 * @return void
 */
void rfid_Reset(void);

/**
 * @brief Resets the FT UART Bridge of the RFID scanner 
 *
 * Sets the corresponding GPIO low for a specified time 
 * and set it back to high
 *
 * @param void
 * @return void
 */
void rfid_FT_UartBridge_Reset(void);
