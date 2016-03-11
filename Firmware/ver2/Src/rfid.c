/** @file rfid.c
 *  @brief An API to control RFID Scanner
 *
 *  This file includes the functions to control the RFID Scanner.
 *  The fuctions are exposed to application layer.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Implement RFID Scanner On Off functions.
 */
 
/* Includes ------------------------------------------------------------------*/
#include "rfid.h"
#include "system.h"



 /**
 * @brief Turns on the RFID scanner
 *
 * Sets the corresponding GPIO low to turn on the RFID scanner. 
 *
 * @param void
 * @return void
 */
void rfid_Turn_On(void)
{	
	HAL_GPIO_WritePin(RFID_NEN_GPIO_Port, RFID_NEN_Pin, GPIO_PIN_RESET);			
}

/**
 * @brief Turns off the RFID scanner 
 *
 * Sets the corresponding GPIO high to turn off the RFID scanner. 
 *
 * @param void
 * @return void
 */
void rfid_Turn_Off(void)
{
	HAL_GPIO_WritePin(RFID_NEN_GPIO_Port, RFID_NEN_Pin, GPIO_PIN_SET);	
}
	
/**
 * @brief Resets the RFID scanner 
 *
 * Sets the corresponding GPIO low for a specified time (>25us)
 * and set it back to high
 *
 * @param void
 * @return void
 */
void rfid_Reset(void)
{
	int i = 0;
	
	HAL_GPIO_WritePin(RFID_NRST_GPIO_Port, RFID_NRST_Pin, GPIO_PIN_RESET);	
	
	// Hold the reset pin in reset state for 100us (at least 25us according to datasheet)		
	for(i = 0; i < TICK_CNT_100US ; i++); 
	
	HAL_GPIO_WritePin(RFID_NRST_GPIO_Port, RFID_NRST_Pin, GPIO_PIN_SET);
}

/**
 * @brief Resets the FT UART Bridge of the RFID scanner 
 *
 * Sets the corresponding GPIO low for a specified time 
 * and set it back to high
 *
 * @param void
 * @return void
 */
void rfid_FT_UartBridge_Reset(void)
{
	int i = 0;
	
	HAL_GPIO_WritePin(FT_NRST_GPIO_Port, FT_NRST_Pin, GPIO_PIN_RESET);	
	
	// Hold the reset pin in reset state for 100us
	for(i = 0; i < TICK_CNT_100US ; i++); 
	
	HAL_GPIO_WritePin(FT_NRST_GPIO_Port, FT_NRST_Pin, GPIO_PIN_SET);
}
