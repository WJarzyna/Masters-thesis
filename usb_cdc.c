#include "usb_cdc.h"

static_assert(USB_WORKER_IRQ > RTC_IRQ, "IRQ LOCKUP DANGER");
static mutex_t usb_mutex;
volatile uint32_t cdc_status;

static void usb_worker_irq(void)
{
    if (mutex_try_enter(&usb_mutex, NULL))
    {
        tud_task();
        mutex_exit(&usb_mutex);
    }
}



static int64_t timer_task(__unused alarm_id_t id, __unused void *user_data)
{
    irq_set_pending(USB_WORKER_IRQ);
    return USB_TASK_INTERVAL_US;
}



bool usb_cdc_init(void)
{
    tusb_init();

    irq_set_exclusive_handler(USB_WORKER_IRQ, usb_worker_irq);
    irq_set_enabled(USB_WORKER_IRQ, true);

    mutex_init(&usb_mutex);

    return add_alarm_in_us(USB_TASK_INTERVAL_US, timer_task, NULL, true);
}



uint32_t usb_cdc_write(const char *buf, uint32_t length)
{
    uint32_t retval = 0;
    uint32_t owner, to_write = 0, available = 0, written = 0;

    if( !mutex_try_enter(&usb_mutex, &owner))
    {
        if( owner == get_core_num()) return USB_ERROR_DEADLOCK; // would deadlock otherwise
        mutex_enter_blocking(&usb_mutex);
    }

    if( tud_cdc_connected() )
    {
        for( retval = 0; retval < length; )
        {
            to_write = length - retval;
            available = tud_cdc_write_available();
            written = 0;
            if( to_write > available ) to_write = available;
            if( to_write ) written = tud_cdc_write(buf + retval, to_write );

            tud_task();
            tud_cdc_write_flush();
            retval += written;
        }
    }
    else retval = USB_ERROR_NOT_CONNECTED;
    mutex_exit(&usb_mutex);

    return retval;
}



uint32_t usb_cdc_read(char *buf, uint32_t length)
{
    uint32_t owner, retval = 0, available = 0;

    if( !mutex_try_enter(&usb_mutex, &owner))
    {
        if( owner == get_core_num()) return USB_ERROR_DEADLOCK; // would deadlock otherwise
        mutex_enter_blocking(&usb_mutex);
    }

    if( tud_cdc_connected() )
    {
        available = tud_cdc_available();
        if( available < length ) length = available;
        if( length > 0 ) retval = tud_cdc_read(buf, (uint32_t) length);
    }

    mutex_exit(&usb_mutex);

    return retval;
}



void tud_mount_cb(void)
{
    cdc_status = MOUNTED;
}



void tud_umount_cb(void)
{
    cdc_status = UNMOUNTED;
}



void tud_suspend_cb(__unused bool remote_wakeup_en)
{
//    (void) remote_wakeup_en;

    cdc_status = SUSPENDED;
}



void tud_resume_cb(void)
{
    cdc_status = MOUNTED;
}



void tud_cdc_line_state_cb(__unused uint8_t itf, bool dtr, __unused bool rts)
{
//    (void) itf;
//    (void) rts;

    if ( dtr ) cdc_status = CONNECTED;
    else cdc_status = MOUNTED;
}



void tud_cdc_rx_cb(__unused uint8_t itf)
{
//    (void) itf;
}