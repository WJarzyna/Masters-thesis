#include "bridge.h"

void sync_rotation()
{
    uint32_t hctab_al[8] = HCTAB_AL;
    uint32_t hctab_ah[8] = HCTAB_AH;
    uint32_t hctab_bl[8] = HCTAB_BL;
    uint32_t hctab_bh[8] = HCTAB_BH;
    uint32_t hctab_cl[8] = HCTAB_CL;
    uint32_t hctab_ch[8] = HCTAB_CH;

    uint32_t state = 0, prev_state = 0, run = 1;
    int32_t pwm_l = 0, pwm_h = 0;
    int rx;

    puts("BEGIN SYNCHRONOUS MODE");

    while(run)
    {
        while( state == prev_state )
        {
            state = ( gpio_get_all() & (H_ALL) ) >> 16;
            rx = getchar_timeout_us(0);
            if( rx != PICO_ERROR_TIMEOUT ) break;
        }

        switch (rx)
        {
            case ' ':
            {
                pwm_h = 0;
                pwm_l = 0;
                puts("STOP");
                break;
            }

            case '+':
            {
                if( pwm_l <= 55000 ) pwm_l += 5000;
                printf("PWM_L: %ld\r", pwm_l);
                break;
            }

            case '-':
            {
                if( pwm_l >= 5000 ) pwm_l -= 5000;
                printf("PWM_L: %ld\r", pwm_l);
                break;
            }

            case 'P':;
            case 'p':
            {
                if( pwm_h <= 55000 ) pwm_h += 5000;
                printf("PWM_H: %ld\r", pwm_h);
                break;
            }

            case 'M':;
            case 'm':
            {
                if( pwm_h >= 5000 ) pwm_h -= 5000;
                printf("PWM_H: %ld\r", pwm_h);
                break;
            }

            case 'e':;
            case 'E':
            {
                pwm_h = 0;
                pwm_l = 0;
                puts("EXIT SYNCHRONOUS MODE");
                run = 0;
                break;
            }


            case PICO_ERROR_TIMEOUT: break;
            default: puts("Unrecognized");
        }

        if( prev_state != state )
        {
            prev_state = state;
            //printf("State: %lu\n", state);

            pwm_set_both_levels(PH_A, 0, 0);
            pwm_set_both_levels(PH_B, 0, 0);
            pwm_set_both_levels(PH_C, 0, 0);

            sleep_us(10);

            pwm_set_both_levels(PH_A, hctab_al[state]*pwm_h, hctab_ah[state]*pwm_l);
            pwm_set_both_levels(PH_B, hctab_bl[state]*pwm_h, hctab_bh[state]*pwm_l);
            pwm_set_both_levels(PH_C, hctab_cl[state]*pwm_h, hctab_ch[state]*pwm_l);
        }
    }
    pwm_set_both_levels(PH_A, 0, 0);
    pwm_set_both_levels(PH_B, 0, 0);
    pwm_set_both_levels(PH_C, 0, 0);
}

void bridge_init()
{
    gpio_set_function( 0, GPIO_FUNC_PWM);
    gpio_set_function( 1, GPIO_FUNC_PWM);
    gpio_set_function( 2, GPIO_FUNC_PWM);
    gpio_set_function( 3, GPIO_FUNC_PWM);
    gpio_set_function( 4, GPIO_FUNC_PWM);
    gpio_set_function( 5, GPIO_FUNC_PWM);

    pwm_set_wrap(PH_A, 60000);
    pwm_set_wrap(PH_B, 60000);
    pwm_set_wrap(PH_C, 60000);

    pwm_set_both_levels(PH_A, 0, 0);
    pwm_set_both_levels(PH_B, 0, 0);
    pwm_set_both_levels(PH_C, 0, 0);

    pwm_set_enabled(PH_A, true);
    pwm_set_enabled(PH_B, true);
    pwm_set_enabled(PH_C, true);

}

void manual_step()
{
    uint32_t ctab_al[6] = CTAB_AL;
    uint32_t ctab_ah[6] = CTAB_AH;
    uint32_t ctab_bl[6] = CTAB_BL;
    uint32_t ctab_bh[6] = CTAB_BH;
    uint32_t ctab_cl[6] = CTAB_CL;
    uint32_t ctab_ch[6] = CTAB_CH;

    uint32_t prev_state = 0, state = 0, run = 1, cnt = 0;
    int32_t pwm_l = 0, pwm_h = 0;
    int rx;

    puts("BEGIN MANUAL STEPPING MODE");

    while(run)
    {
        state = ( gpio_get_all() & (H_ALL) ) >> 16;

        if( prev_state != state ) printf("Hall state: %lu\n", state);
        prev_state = state;

        rx = getchar_timeout_us(0);

        switch (rx)
        {
            case ' ':
            {
                pwm_h = 0;
                pwm_l = 0;
                puts("STOP");
                break;
            }

            case '+':
            {
                if( pwm_l <= 55000 ) pwm_l += 5000;
                printf("PWM_L: %ld\r", pwm_l);
                break;
            }

            case '-':
            {
                if( pwm_l >= 5000 ) pwm_l -= 5000;
                printf("PWM_L: %ld\r", pwm_l);
                break;
            }

            case 'P':;
            case 'p':
            {
                if( pwm_h <= 55000 ) pwm_h += 5000;
                printf("PWM_H: %ld\r", pwm_h);
                break;
            }

            case 'M':;
            case 'm':
            {
                if( pwm_h >= 5000 ) pwm_h -= 5000;
                printf("PWM_H: %ld\r", pwm_h);
                break;
            }

            case 'e':;
            case 'E':
            {
                pwm_h = 0;
                pwm_l = 0;
                puts("EXIT MANUAL STEPPING MODE");
                run = 0;
                break;
            }

            case 'f':;
            case 'F':
            {
                cnt++;
                if( cnt > 5 ) cnt = 0;
                printf("Commutation state %ld    Transistors: %s | %s\n", cnt,
                       ctab_al[cnt] ? "A_L" : (ctab_bl[cnt] ? "B_L" : (ctab_cl[cnt] ? "C_L" : "")),
                       ctab_ah[cnt] ? "A_H" : (ctab_bh[cnt] ? "B_H" : (ctab_ch[cnt] ? "C_H" : "")) );

                pwm_set_both_levels(PH_A, ctab_al[cnt]*pwm_h, ctab_ah[cnt]*pwm_l);
                pwm_set_both_levels(PH_B, ctab_bl[cnt]*pwm_h, ctab_bh[cnt]*pwm_l);
                pwm_set_both_levels(PH_C, ctab_cl[cnt]*pwm_h, ctab_ch[cnt]*pwm_l);

                sleep_ms(1000);

                pwm_set_both_levels(PH_A, 0, 0);
                pwm_set_both_levels(PH_B, 0, 0);
                pwm_set_both_levels(PH_C, 0, 0);

                break;
            }

            case 'b':;
            case 'B':
            {
                cnt--;
                if( cnt > 5 ) cnt = 5;
                printf("Commutation state %ld    Transistors: %s | %s\n", cnt,
                       ctab_al[cnt] ? "A_L" : (ctab_bl[cnt] ? "B_L" : (ctab_cl[cnt] ? "C_L" : "")),
                       ctab_ah[cnt] ? "A_H" : (ctab_bh[cnt] ? "B_H" : (ctab_ch[cnt] ? "C_H" : "")) );

                pwm_set_both_levels(PH_A, ctab_al[cnt]*pwm_h, ctab_ah[cnt]*pwm_l);
                pwm_set_both_levels(PH_B, ctab_bl[cnt]*pwm_h, ctab_bh[cnt]*pwm_l);
                pwm_set_both_levels(PH_C, ctab_cl[cnt]*pwm_h, ctab_ch[cnt]*pwm_l);

                sleep_ms(1000);

                pwm_set_both_levels(PH_A, 0, 0);
                pwm_set_both_levels(PH_B, 0, 0);
                pwm_set_both_levels(PH_C, 0, 0);
                break;
            }


            case PICO_ERROR_TIMEOUT: break;
            default: puts("Unrecognized");
        }
    }
    pwm_set_both_levels(PH_A, 0, 0);
    pwm_set_both_levels(PH_B, 0, 0);
    pwm_set_both_levels(PH_C, 0, 0);
}