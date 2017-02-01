#ifndef ROBOCUP_INTERFACE_USB_H_
#define ROBOCUP_INTERFACE_USB_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usbd_def.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"

#include "com_interface.h"

#define USB_MAX_PACKET_SIZE                 512

comHandle_t usb_init(void);
size_t      usb_read(void *pBuffer, size_t length);
size_t      usb_write(const void *pBuffer, size_t length);
size_t      usb_readUntilZero(void *pBuffer, size_t length);

#endif /* ROBOCUP_INTERFACE_USB_H_ */
