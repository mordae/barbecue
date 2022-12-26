cmake_minimum_required(VERSION 3.12)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(barbecue)
pico_sdk_init()

add_executable(barbecue barbecue.c)
target_link_libraries(barbecue pico_stdlib)
pico_add_extra_outputs(barbecue)

#pico_set_binary_type(barbecue no_flash)
#pico_set_binary_type(barbecue copy_to_ram)
