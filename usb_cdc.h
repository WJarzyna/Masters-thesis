#ifndef USB_CDC_H
#define USB_CDC_H

#include "tusb.h"
#include "pico/time.h"
#include "pico/binary_info.h"
#include "pico/mutex.h"
#include "hardware/irq.h"

#define USB_TASK_INTERVAL_US 1000
#define USB_WORKER_IRQ 31

#define USB_ERROR_DEADLOCK -1
#define USB_ERROR_NOT_CONNECTED -2

#define USB_ENABLE_RESET_VIA_BAUD 1

enum { UNKNOWN, UNMOUNTED, SUSPENDED, MOUNTED, CONNECTED };

bool usb_cdc_init(void);
uint32_t usb_cdc_write(const char *buf, uint32_t length);
uint32_t usb_cdc_read(char *buf, uint32_t length);

#if USB_ENABLE_RESET_VIA_BAUD
#include "pico/bootrom.h"

#define USB_RESET_BAUD_RATE 1200
#define USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK 0u

void tud_cdc_line_coding_cb(__unused uint8_t itf, cdc_line_coding_t const* p_line_coding)
{
    if (p_line_coding->bit_rate == USB_RESET_BAUD_RATE)
    {
        reset_usb_boot(0u, USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK);
    }
}
#endif

#endif
