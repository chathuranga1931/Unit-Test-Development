/** @file system.h
 *  @brief System wide definitions
 *
 *  KUBE2 system specific definitions are included in this file
 *
 *  @author Kanishka W (kanishkaw@zone24x7.com)
 *  @bug No known bugs.
 * 
 *  @par Change Log
 *  2016-Mar-01 	Create the new file. 
 *                  Add peripheral ID and Command ID definitions (Refer KUBE_Commands doc)
 */
	
// Peripheral ID Definition
#define MCU						0x01	// Microcontroller
#define TEMP_SENSE				0x03	// Temperature Sensor
#define LED0					0x05	// LED0
#define LED1					0x06	// LED1
#define LED2					0x07	// LED2
#define BTN0					0x0A	// Button0
#define BTN1					0x0B	// Button1
#define BUZZER					0x10	// Buzzer
#define AUDIO_AMP				0x11	// Audio amplifier
#define PROX_IR0				0x15	// Proximity IR sensor 0
#define PROX_IR1				0x16	// Proximity IR sensor 1
#define PROX_IR2				0x17	// Proximity IR sensor 2
#define PROX_US					0x18	// Proximity Ultra-Sonic
#define RF_SCANNER				0x1C	// RFID scanner
#define BARCODE_SCANNER			0x1D	// Barcode scanner

// MCU Commands
#define MCU_DEBUG_ENABLE		0x03	// Enable to push messages through Debug serial interface
#define MCU_DEBUG_DISABLE		0x04	// Disable to push messages through Debug serial interface
#define MCU_FIRMWARE_UPGRADE	0x05	// MCU changes to firmware upgrade mode
#define MCU_REG_A_5V_ON			0x0B	// Turn on REG_A_5V regulator
#define MCU_REG_A_5V_OFF		0x0C	// Turn off REG_A_5V regulator
#define MCU_REG_B_5V_ON			0x0D	// Turn on REG_B_5V regulator
#define MCU_REG_B_5V_OFF		0x0E	// Turn off REG_B_5V regulator
#define MCU_REG_A_3V3_ON		0x0F	// Turn on REG_A_3V3 regulator
#define MCU_REG_A_3V3_OFF		0x10	// Turn off REG_A_3V3 regulator
#define MCU_REG_9V_ON			0x13	// Turn on REG_9V regulator
#define MCU_REG_9V_OFF			0x14	// Turn off REG_9V regulator
#define MCU_ALL_REG_ON			0x15	// Turn on all the Regulators
#define MCU_GET_FW_VERSION		0x16	// Requesting the firmware version
#define MCU_GET_BOARDID			0x17	// Requesting the Board ID
#define MCU_DIP_READ			0x18	// Request the port values of the dip switches

// TEMP_SENSE Commands
#define TEMP_READ				0x03	// Requesting for the current temperature
#define TEMP_SET_UPPER_LIM		0x04	// Set upper limit. Over temperature threshold of the temperature sensor
#define TEMP_SET_LOWER_LIM		0x05	// Set lower limit. This is to clear the over temperature detect event

// LED Commands
#define LED_ON					0x01	// Turn on the relevant LED
#define LED_OFF					0x02	// Turn off the relevant LED
#define LED_BLINK_SLOW			0x03	// Blink the LED 50% duty cycle. 1s ON time
#define LED_BLINK_FAST			0x04	// Blink the LED 50% duty cycle. 0.25 ON time
#define LED_BLINK_MID			0x05	// Blink the LED 50% duty cycle. 0.5s ON time
#define LED_BLINK				0x06	// Custom on time and off time

// BTN Commands
#define BTN_READ				0x03	// Request the status of the relevant button

// BUZZER Commands
#define BEEP_SHORT				0x03	// Buzzer will beep for 0.25mS once
#define BEEP_LONG				0x04	// Buzzer will beep for 0.5mS once
#define BEEP_SHORT_FOR			0x05	// Buzzer will beep n times with 50% duty cycle with short duration
#define BEEP_LONG_FOR			0x06	// Buzzer will beep n times with 50% duty cycle with long time duration
#define BEEP_FOR				0x07	// Buzzer will beep for t milliseconds

// AUDIO_AMP Commands
#define AMP_MUTE				0x03	// Mute the output of the amplifier
#define AMP_STANDBY				0x04	// Amplifier set to Standby mode
#define AMP_VOLUME_LEVEL		0x05	// Level of volume (1, 2, 3, 4)

// PROXIMITY Commands
#define PROX_READ				0x03	// Requesting the reading of the relevant proximity sensor

// RF_SCANNER Commands
#define RF_ON					0x01	// Turn on the power of the RF Scanner
#define RF_OFF					0x02	// Turn off the power of the RF Scanner
#define RF_RESET				0x03	// Reset the RF Scanner
#define RF_FT_UARTBRIDGE_RESET	0x04	// Reset the FT232 UART Bridge. 


// BARCODE_SCANNER Commands
#define BARCODE_ON				0x01	// Turn on the power of the Barcode Scanner
#define BARCODE_OFF				0x02	// Turn off the power of the Barcode Scanner 
