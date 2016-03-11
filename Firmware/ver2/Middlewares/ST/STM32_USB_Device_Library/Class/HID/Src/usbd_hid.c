/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @version V2.4.0
  * @date    28-February-2015
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"
#include "usbd_conf.h"    //{KW}: USB_CUBE definition needed


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_HID_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 




/** @defgroup USBD_HID_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);
static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length);

#ifdef USB_KUBE
uint8_t  USBD_HID_DataOut (USBD_HandleTypeDef  *pdev, uint8_t epnum);
#else
static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length);
#endif//USB_KUBE
static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Variables
  * @{
  */ 

#ifdef USB_KUBE
USBD_ClassTypeDef  USBD_HID = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /* EP0_TxSent */  
  NULL, /* EP0_RxReady */ 
  USBD_HID_DataIn, /*DataIn*/
  USBD_HID_DataOut, /*DataOut*/
  NULL, /*SOF */   
  NULL, /* IsoINIncomplete */
  NULL, /* IsoOUTIncomplete */	
	
  NULL, /* GetHSConfigDescriptor */	 
  USBD_HID_GetCfgDesc,  /* GetFSConfigDescriptor */	
  NULL, /* GetOtherSpeedConfigDescriptor */
  NULL, /* GetDeviceQualifierDescriptor */
};
#else	
USBD_ClassTypeDef  USBD_HID = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/  
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL, 
	
  USBD_HID_GetCfgDesc,
  USBD_HID_GetCfgDesc, 
  USBD_HID_GetCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};
#endif //USB_KUBE

#ifdef USB_KUBE
/* ----------------------------- USB Descriptors--------------------------------------*/

// Report Descriptors

// Kube Kube Command Responce Report Descriptor - Used in Interface 0	
#ifdef ENABLE_KUBE_CMD_INTF

static __attribute__((aligned(4)))
uint8_t KubeCmdRespReportDescriptor[] =
{
	0x06, 0x00,0xFF,	// USAGE_PAGE (Vendor Defined 1)
	0x09, 0x01,			// USAGE (Vendor Defined Usage 1)
	0xa1, 0x01,			// COLLECTION (Application)

	// Report ID 1 - Command Response
	0x85, 0x01,			//   REPORT_ID (1)
	0x09, 0x03,			//   USAGE (chars)
	0x15, 0x00,			//   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,	//   LOGICAL_MAXIMUM (255)
	0x75, 0x08,			//   REPORT_SIZE (8 bits)
	0x95, 0x3F,			//   REPORT_COUNT (63)
	0x91, 0x82,			//   OUTPUT (Data, Variable, Absolute, Volatile)

	0x85, 0x01,			//   REPORT_ID (1)
	0x09, 0x03,			//   USAGE (chars)
	0x15, 0x00,			//   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,	//   LOGICAL_MAXIMUM (255)
	0x75, 0x08,			//   REPORT_SIZE (8 bits)
	0x95, 0x3F,			//   REPORT_COUNT (63)
	0x81, 0x82,			//   INPUT (Data, Variable, Absolute, Volatile)

	0xc0				// END_COLLECTION
};
#endif


// Kube Proximity Data Report Descriptor - Used in Interface 1
#ifdef ENABLE_KUBE_PROXI_INTF

static __attribute__((aligned(4)))
uint8_t ProximityReportDescriptor[] =
{
	  0x06, 0x00,0xFF,		// USAGE_PAGE (Vendor Defined 1)
	  0x09, 0x02,			// USAGE  (Vendor Defined Usage 2)
	  0xa1, 0x01,			// COLLECTION (Application)

	  0x85, 0x02,			// REPORT_ID (2)
	  0x09, 0x0A,			// USAGE (Left)
	  0x09, 0x0B,			// USAGE (Right)
	  0x15, 0x00,			// LOGICAL_MINIMUM (0)
	  0x26, 0xff, 0x0F,		// LOGICAL_MAXIMUM (4095)
	  0x75, 0x10,			// REPORT_SIZE (16 bits)
	  0x95, 0x02,			// REPORT_COUNT (2)
	  0x81, 0x82,			// INPUT (Data,Var,Abs,Vol)
	  0xc0					// END_COLLECTION
};
#endif


// Kube Notifications Report Descriptor - Used in Interface 2
#ifdef ENABLE_KUBE_NOTIF_INTF

static __attribute__((aligned(4)))
uint8_t NotificationsReportDescriptor[] =
{
	  0x06, 0x00,0xFF,		// USAGE_PAGE (Vendor Defined 1)
	  0x09, 0x03,			// USAGE  (Vendor Defined Usage 3)
	  0xa1, 0x01,			// COLLECTION (Application)

	  0x85, 0x03,			// REPORT_ID (3)
	  0x09, 0x03,			// USAGE (chars)
	  0x15, 0x00,			// LOGICAL_MINIMUM (0)
	  0x26, 0xff, 0x00,		// LOGICAL_MAXIMUM (255)
	  0x75, 0x08,			// REPORT_SIZE (8 bits)
	  0x95, 0x3F,			// REPORT_COUNT (63)
	  0x81, 0x82,			// INPUT (Data,Var,Abs,Vol)
	  0xc0					// END_COLLECTION
};
#endif

// Kube Debug Report Descriptor - Used in Interface 3
#ifdef ENABLE_KUBE_DEBUG_INTF

static __attribute__((aligned(4)))
uint8_t DebugReportDescriptor[] =
{
	  0x06, 0x00,0xFF,		// USAGE_PAGE (Vendor Defined 1)
	  0x09, 0x04,			// USAGE  (Vendor Defined Usage 4)
	  0xa1, 0x01,			// COLLECTION (Application)

	  0x85, 0x04,			// REPORT_ID (4)
	  0x09, 0x03,			// USAGE (chars)
	  0x15, 0x00,			// LOGICAL_MINIMUM (0)
	  0x26, 0xff, 0x00,		// LOGICAL_MAXIMUM (255)
	  0x75, 0x08,			// REPORT_SIZE (8 bits)
	  0x95, 0x3F,			// REPORT_COUNT (63)
	  0x81, 0x82,			// INPUT (Data,Var,Abs,Vol)
	  0xc0					// END_COLLECTION
};
#endif

// Kube Reader Configuration Descriptor
__attribute__((aligned(4)))
struct __attribute__((packed)) {
	usb_configuration_descriptor_t  cd01;
	
#ifdef ENABLE_KUBE_CMD_INTF
	usb_interface_descriptor_t      i00a00;
	usb_hid_descriptor_t			hid_i00a00;
	usb_endpoint_descriptor_t       ep01i_i00a00;
	usb_endpoint_descriptor_t       ep01o_i00a00;
#endif

#ifdef ENABLE_KUBE_PROXI_INTF
	usb_interface_descriptor_t      i01a00;
	usb_hid_descriptor_t            hid_i01a00;
	usb_endpoint_descriptor_t       ep02i_i01a00;
#endif
	
#ifdef ENABLE_KUBE_NOTIF_INTF
	usb_interface_descriptor_t      i02a00;
	usb_hid_descriptor_t            hid_i02a00;
	usb_endpoint_descriptor_t       ep03i_i02a00;
#endif
	
#ifdef ENABLE_KUBE_DEBUG_INTF
	usb_interface_descriptor_t      i03a00;
	usb_hid_descriptor_t            hid_i03a00;
	usb_endpoint_descriptor_t       ep04i_i03a00;
#endif

} USBD_HID_CfgDesc =
{
  // Configuration Descriptor
	{
		sizeof(usb_configuration_descriptor_t),		// Size of this descriptor in bytes
		USB_DESC_TYPE_CONFIGURATION,         		// CONFIGURATION descriptor type
		sizeof(USBD_HID_CfgDesc),  				    // Total length of data for this cfg(LS byte)
		USBD_ITF_MAX_NUM,                   		// Number of interfaces in this cfg
		0x01,                      					// Index value of this configuration
		0x00,	                      				// Configuration string index
		0x80, 										// bmAttributes - Bus Powered
		0x32,                     					// Max power consumption (2X mA) -  100 mA
	},

#ifdef ENABLE_KUBE_CMD_INTF
	////// Interface 0: Kube Command Response Interface
	{
		// Interface Descriptor
		sizeof(usb_interface_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_INTERFACE,     		// INTERFACE descriptor type
		INTF_HID_KUBE_CMD,        			// Interface Number
		0x00,								// Alternate Setting Number
		0x02,                     			// Number of endpoints in this intf
		HID_DEVICE,          				// Class code
		0x00, 								// Subclass code
		0x00,                				// Protocol code - None
		0x00,								// Interface string index
	},
	// HID Class-Specific Descriptors
	{
		sizeof(usb_hid_descriptor_t),			// Size of this descriptor in bytes
		HID_DESCRIPTOR_TYPE,					// bDescriptorType - HID
		0x0110, 	 	 	 	 	 			// bcdUSB(L/H) USB spec rev (BCD) - 0x0110
		0x00,									// Hardware target country
		0x01,									// Number of HID class descriptors to follow
		HID_REPORT_DESC,						// Followed Descriptor - Report descriptor
		sizeof(KubeCmdRespReportDescriptor),	// Total length of Report descriptor
	},

	// Endpoint Descriptors
	{	// [In] Endpoint - EP1
		sizeof(usb_endpoint_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_ENDPOINT,				// bDescriptorType - USB_DSC_ENDPOINT
		HID_CMD_IN_EP,						// bEndpointAddress - 0x81
		USB_DEVICE_EP_INT,					// bmAttributes - Interrupt EP
		USB_EP_MAX_SIZE,					// wMaxPacketSize - 64 bytes
		0x01								// Endpoint Polling interval every 1 ms
	},
	{	// [Out] Endpoint - EP1
		sizeof(usb_endpoint_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_ENDPOINT,				// bDescriptorType - USB_DSC_ENDPOINT
		HID_CMD_OUT_EP,						// bEndpointAddress - 0x01			
		USB_DEVICE_EP_INT,					// bmAttributes - Interrupt EP
		USB_EP_MAX_SIZE,					// wMaxPacketSize - 64 bytes
		0x01								// Endpoint Polling interval every 1 ms
	},
#endif

#ifdef ENABLE_KUBE_PROXI_INTF
	////// Interface 1: Kube Proximity Data HID Interface
	{
	// Interface Descriptor
		sizeof(usb_interface_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_INTERFACE,     		// INTERFACE descriptor type
		INTF_HID_KUBE_PROXI,    			// Interface Number
		0x00,								// Alternate Setting Number
		0x01,                     			// Number of endpoints in this intf
		HID_DEVICE,          				// Class code
		0x00, 								// Subclass code
		0x00,                				// Protocol code - None
		0x00,								// Interface string index
	},
	// HID Class-Specific Descriptors
	{
		sizeof(usb_hid_descriptor_t),			// Size of this descriptor in bytes
		HID_DESCRIPTOR_TYPE,					// bDescriptorType - HID
		0x0110, 	 	 	 	 	 			// bcdUSB(L/H) USB spec rev (BCD) - 0x0110
		0x00,									// Hardware target country
		0x01,									// Number of HID class descriptors to follow
		HID_REPORT_DESC,						// Followed Descriptor - Report descriptor
		sizeof(ProximityReportDescriptor),		// Total length of Report descriptor
	},
	// Endpoint Descriptor
	{	// [In] Endpoint - EP2
		sizeof(usb_endpoint_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_ENDPOINT,				// bDescriptorType - USB_DSC_ENDPOINT
		HID_PROXIMITY_IN_EP,				// bEndpointAddress - 0x82
		USB_DEVICE_EP_INT,					// bmAttributes - Interrupt EP
		PROXIMITY_IN_EP_MAX_SIZE,			// wMaxPacketSize - 8 bytes
		0x10								// Endpoint Polling interval every 10 ms
	},
#endif
	
#ifdef ENABLE_KUBE_NOTIF_INTF
	////// Interface 2: The Kube Notifications HID Interface
	{
	// Interface Descriptor
		sizeof(usb_interface_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_INTERFACE,     		// INTERFACE descriptor type
		INTF_HID_KUBE_NOTIF,    			// Interface Number
		0x00,								// Alternate Setting Number
		0x01,                     			// Number of endpoints in this intf
		HID_DEVICE,          				// Class code
		0x00, 								// Subclass code
		0x00,                				// Protocol code - None
		0x00,								// Interface string index
	},
	// HID Class-Specific Descriptors
	{
		sizeof(usb_hid_descriptor_t),			// Size of this descriptor in bytes
		HID_DESCRIPTOR_TYPE,					// bDescriptorType - HID
		0x0110, 	 	 	 	 	 			// bcdUSB(L/H) USB spec rev (BCD) - 0x0110
		0x00,									// Hardware target country
		0x01,									// Number of HID class descriptors to follow
		HID_REPORT_DESC,						// Followed Descriptor - Report descriptor
		sizeof(NotificationsReportDescriptor),	// Total length of Report descriptor
	},
	// Endpoint Descriptor
	{	// [In] Endpoint - EP3
		sizeof(usb_endpoint_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_ENDPOINT,				// bDescriptorType - USB_DSC_ENDPOINT
		HID_NOTIFICATION_IN_EP,				// bEndpointAddress - 0x83
		USB_DEVICE_EP_INT,					// bmAttributes - Interrupt EP
		USB_EP_MAX_SIZE,					// wMaxPacketSize - 64 bytes
		0x01,								// Endpoint Polling interval every 01 ms
	},
#endif
	
#ifdef ENABLE_KUBE_DEBUG_INTF
	////// Interface 3: Kube Debug Message HID Interface
	{
	// Interface Descriptor
		sizeof(usb_interface_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_INTERFACE,     		// INTERFACE descriptor type
		INTF_HID_KUBE_DEBUG,    			// Interface Number
		0x00,								// Alternate Setting Number
		0x01,                     			// Number of endpoints in this intf
		HID_DEVICE,          				// Class code
		0x00, 								// Subclass code
		0x00,                				// Protocol code - None
		0x00,								// Interface string index
	},
	// HID Class-Specific Descriptors
	{
		sizeof(usb_hid_descriptor_t),			// Size of this descriptor in bytes
		HID_DESCRIPTOR_TYPE,					// bDescriptorType - HID
		0x0110, 	 	 	 	 	 			// bcdUSB(L/H) USB spec rev (BCD) - 0x0110
		0x00,									// Hardware target country
		0x01,									// Number of HID class descriptors to follow
		HID_REPORT_DESC,						// Followed Descriptor - Report descriptor
		sizeof(DebugReportDescriptor),			// Total length of Report descriptor
	},
	// Endpoint Descriptor
	{	// [In] Endpoint - EP4
		sizeof(usb_endpoint_descriptor_t),	// Size of this descriptor in bytes
		USB_DESC_TYPE_ENDPOINT,				// bDescriptorType - USB_DSC_ENDPOINT
		HID_DEBUG_IN_EP,					// bEndpointAddress - 0x83
		USB_DEVICE_EP_INT,					// bmAttributes - Interrupt EP
		USB_EP_MAX_SIZE,					// wMaxPacketSize - 64 bytes
		0x01,								// Endpoint Polling interval every 1 ms
	},
#endif

};

#else
/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  
  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  
  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval (10 ms)*/
  /* 34 */
} ;

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[USB_HID_DESC_SIZ]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
{
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x09,   0x01,
  
  0xA1,   0x00,
  0x05,   0x09,
  0x19,   0x01,
  0x29,   0x03,
  
  0x15,   0x00,
  0x25,   0x01,
  0x95,   0x03,
  0x75,   0x01,
  
  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x05,
  0x81,   0x01,
  
  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,
  0x09,   0x38,
  
  0x15,   0x81,
  0x25,   0x7F,
  0x75,   0x08,
  0x95,   0x03,
  
  0x81,   0x06,
  0xC0,   0x09,
  0x3c,   0x05,
  0xff,   0x09,
  
  0x01,   0x15,
  0x00,   0x25,
  0x01,   0x75,
  0x01,   0x95,
  
  0x02,   0xb1,
  0x22,   0x75,
  0x06,   0x95,
  0x01,   0xb1,
  
  0x01,   0xc0
}; 

#endif //USB_KUBE

/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{
  uint8_t ret = 0;
  
  /* Open EP IN */
  USBD_LL_OpenEP(pdev,
                 HID_EPIN_ADDR,
                 USBD_EP_TYPE_INTR,
                 HID_EPIN_SIZE);  
  
  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  }
  return ret;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev,
                  HID_EPIN_ADDR);
  
  /* FRee allocated memory */
  if(pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  } 
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
      
      
    case HID_REQ_SET_PROTOCOL:
      hhid->Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:
      hhid->IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->IdleState,
                        1);        
      break;      
      
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      if( req->wValue >> 8 == HID_REPORT_DESC)
      {
#ifdef USB_KUBE
		switch (req->wIndex)
		{
			#ifdef ENABLE_KUBE_CMD_INTF
			case INTF_HID_KUBE_CMD:
				len = MIN(sizeof(KubeCmdRespReportDescriptor) , req->wLength);
				pbuf = (uint8_t*)KubeCmdRespReportDescriptor;
				break;
			#endif // ENABLE_KUBE_CMD_INTF
			#ifdef ENABLE_KUBE_PROXI_INTF
			case INTF_HID_KUBE_PROXI:
				len = MIN(sizeof(ProximityReportDescriptor) , req->wLength);
				pbuf = (uint8_t*)ProximityReportDescriptor;
				break;
			#endif // ENABLE_KUBE_PROXI_INTF
			#ifdef ENABLE_KUBE_NOTIF_INTF
			case INTF_HID_KUBE_NOTIF:
				len = MIN(sizeof(NotificationsReportDescriptor) , req->wLength);
				pbuf = (uint8_t*)NotificationsReportDescriptor;
				break;
			#endif // ENABLE_KUBE_NOTIF_INTF
			#ifdef ENABLE_KUBE_DEBUG_INTF
			case INTF_HID_KUBE_DEBUG:
				len = MIN(sizeof(DebugReportDescriptor) , req->wLength);
				pbuf = (uint8_t*)DebugReportDescriptor;
				break;
			#endif // ENABLE_KUBE_DEBUG_INTF
			default:
				break;
		}
#else
		len = MIN(HID_MOUSE_REPORT_DESC_SIZE , req->wLength);
        pbuf = HID_MOUSE_ReportDesc;
#endif //USB_KUBE
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
#ifdef USB_KUBE
		switch (req->wIndex)
		{
			#ifdef ENABLE_KUBE_CMD_INTF
			case INTF_HID_KUBE_CMD:
				pbuf = (uint8_t*)&USBD_HID_CfgDesc.hid_i00a00;
				len = MIN(USBD_HID_CfgDesc.hid_i00a00.bFunctionalLength , req->wLength);
				break;
			#endif // ENABLE_KUBE_CMD_INTF
			#ifdef ENABLE_KUBE_PROXI_INTF
			case INTF_HID_KUBE_PROXI:
				pbuf = (uint8_t*)&USBD_HID_CfgDesc.hid_i01a00;
				len = MIN(USBD_HID_CfgDesc.hid_i01a00.bFunctionalLength , req->wLength);
				break;
			#endif // ENABLE_KUBE_PROXI_INTF
			#ifdef ENABLE_KUBE_NOTIF_INTF
			case INTF_HID_KUBE_NOTIF:
				pbuf = (uint8_t*)&USBD_HID_CfgDesc.hid_i02a00;
				len = MIN(USBD_HID_CfgDesc.hid_i02a00.bFunctionalLength , req->wLength);
				break;
			#endif // ENABLE_KUBE_NOTIF_INTF
			#ifdef ENABLE_KUBE_DEBUG_INTF
			case INTF_HID_KUBE_DEBUG:
				pbuf = (uint8_t*)&USBD_HID_CfgDesc.hid_i03a00;
				len = MIN(USBD_HID_CfgDesc.hid_i03a00.bFunctionalLength , req->wLength);
				break;	
			#endif // ENABLE_KUBE_DEBUG_INTF
			default:
				break;
		}
#else		  
        pbuf = USBD_HID_Desc;   
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
#endif //USB_KUBE
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&hhid->AltSetting,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      hhid->AltSetting = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USBD_HandleTypeDef  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
  
  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    if(hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit (pdev, 
                        HID_EPIN_ADDR,                                      
                        report,
                        len);
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetPollingInterval 
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0;

  /* HIGH-speed endpoints */
  if(pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers. 
    Values between 1..16 are allowed. Values correspond to interval 
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1 <<(HID_HS_BINTERVAL - 1)))/8);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full 
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }
  
  return ((uint32_t)(polling_interval));
}

#ifdef USB_KUBE
/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return (uint8_t *)(&USBD_HID_CfgDesc);
}
#else
/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return USBD_HID_CfgDesc;
}
#endif //USB_KUBE

/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
  
  /* Ensure that the FIFO is empty before a new transfer, this condition could 
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  return USBD_OK;
}

#ifdef USB_KUBE
/**
  * @brief  USBD_HID_DataOut
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
uint8_t  USBD_HID_DataOut (USBD_HandleTypeDef  *pdev, uint8_t epnum)
{
#warning "complete this line"
//	DCD_EP_PrepareRx(pdev,HID_CMD_IN_EP,Report_buf,sizeof(Report_buf));

	return USBD_OK;
}

#else
/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}
#endif //USB_KUBE
/**
  * @}
  */ 


/**
  * @}
  */ 


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
