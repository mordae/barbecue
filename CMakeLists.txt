cmake_minimum_required(VERSION 3.12)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

set(PICO_BOARD barbecue10)
set(PICO_BOARD_HEADER_DIRS $ENV{PWD}/src/boards)

add_definitions(-I$ENV{PWD}/src)
list(APPEND PICO_CONFIG_HEADER_FILES task_hooks.h)

project(barbecue)
pico_sdk_init()

add_subdirectory(src)
