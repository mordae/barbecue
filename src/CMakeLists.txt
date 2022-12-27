add_executable(barbecue main.c)
target_link_libraries(barbecue pico_stdlib)
pico_add_extra_outputs(barbecue)
pico_enable_stdio_usb(barbecue ENABLED)

#pico_set_binary_type(barbecue no_flash)
#pico_set_binary_type(barbecue copy_to_ram)
