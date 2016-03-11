/** @file btn.c
 *  @brief An API to access buttons
 *
 *  This exposes includes the functions to access the buttons.
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Add button read function.
 */
 
/* Includes ------------------------------------------------------------------*/
#include "btn.h"
#include "system.h"

 /**
 * @brief Reads button status as specified by btn_idx
 *
 * Reads the corresponding GPIO of the requested button.
 * Input parameter must be validated before calling this function.
 *
 * @param btn_idx 	The peripheral ID of the Button to be read. 
 * @return Button status
 *         GPIO_PIN_RESET for low
 *         GPIO_PIN_SET for high
 */
GPIO_PinState btn_Read(uint8_t btn_idx)
{
	GPIO_PinState btn = GPIO_PIN_RESET;
	
	switch(btn_idx)
	{
		case BTN0:
			btn = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
			break;
		case BTN1:
			btn = HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
			break;
		default:
			break;
	}
	
	return btn;
}
