#include "position.h"

volatile int32_t enc_pos;
volatile uint32_t hall_pos, enc_valid;

void pos_irq( uint gpio, uint32_t events )
{
    static const int alpha_tab[8] = ALPHA_TAB;

    switch(gpio)
    {
        case H1:;
        case H2:;
        case H3:
            hall_pos = alpha_tab[( gpio_get_all() & (H_ALL) )];
            if( !enc_valid ) enc_pos = hall_pos/3 + ENC_OFFSET;
            break;

        case ENC_A: if( !(gpio_get_all() & (1<<ENC_B)) ) --enc_pos; break;
        case ENC_B: if( !(gpio_get_all() & (1<<ENC_A)) ) ++enc_pos; break;

        case ENC_Z: enc_pos = 0; enc_valid = 1; break;

        default: break;
    }

    if( enc_pos > 720 ) enc_pos -= 720;
    if( enc_pos < 0 ) enc_pos += 720;
}



void hall_init()
{
    gpio_init_mask(  H_ALL );
    gpio_set_dir_in_masked( H_ALL );

    gpio_set_irq_enabled_with_callback( H1, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, pos_irq);
    gpio_set_irq_enabled_with_callback( H2, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, pos_irq);
    gpio_set_irq_enabled_with_callback( H3, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, pos_irq);
}




void enc_init()
{
    enc_pos = 0;
    enc_valid = 0;

    gpio_init_mask(ENC_MASK);
    gpio_set_dir_in_masked(ENC_MASK);
    gpio_pull_up(ENC_A);
    gpio_pull_up(ENC_B);
    gpio_pull_up(ENC_Z);

    gpio_set_irq_enabled_with_callback( ENC_A, GPIO_IRQ_EDGE_RISE, 1, pos_irq);
    gpio_set_irq_enabled_with_callback( ENC_B, GPIO_IRQ_EDGE_RISE, 1, pos_irq);
    gpio_set_irq_enabled_with_callback( ENC_Z, GPIO_IRQ_EDGE_RISE, 1, pos_irq);
}
