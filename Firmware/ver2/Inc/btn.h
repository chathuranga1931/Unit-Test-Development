/** @file btn.h
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
#include "stm32f0xx_hal.h"

 /* Public Functions ----------------------------------------------------------*/
 
 /**
 * @brief Reads button status as specified by btn_idx
 *
 * Reads the corresponding GPIO of the requested button.
 * Input parameter must be validated before calling this function.
 *
 * @param btn_idx 	The peripheral ID of the Button to be read. 
 * @return Buttom status
 *         GPIO_PIN_RESET for low
 *         GPIO_PIN_SET for high
 */
GPIO_PinState btn_Read(uint8_t btn_idx);
