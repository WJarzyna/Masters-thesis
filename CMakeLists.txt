cmake_minimum_required(VERSION 3.21)


set(CMAKE_C_STANDARD 11)
set(PICO_SDK_PATH /home/kon/Documents/c/RP2040/pico-sdk)
include(pico_sdk_import.cmake)

project(inverter C CXX ASM )
add_executable(inverter main.c bridge.h bridge.c comms.c comms.h adc.c adc.h pid.c pid.h)
pico_sdk_init()

target_link_libraries(inverter
        pico_stdlib
        hardware_pwm
        hardware_adc
        hardware_dma
        hardware_irq)

pico_enable_stdio_usb(inverter 1)
pico_enable_stdio_uart(inverter 0)

pico_add_extra_outputs(inverter)
