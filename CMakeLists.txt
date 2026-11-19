cmake_minimum_required(VERSION 3.13)

# Pull in the Pico SDK (must happen before project() is called)
include(pico_sdk_import.cmake)

project(my_blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Define your executable target
add_executable(main
    main.c
)

# Link the Pico standard library (provides GPIO, timing, etc.)
target_link_libraries(main pico_stdlib)

# Enable USB output for serial printing, disable UART by default
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# Generate standard output files (.hex, .bin, .uf2)
pico_add_extra_outputs(main)