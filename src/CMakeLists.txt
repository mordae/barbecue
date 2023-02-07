add_executable(barbecue main.c task.c renc.c scene.c)

target_link_libraries(barbecue
                      pico_tft
                      pico_stdlib
                      pico_util
                      pico_sync
                      pico_divider
                      pico_multicore
                      hardware_adc
                      hardware_spi
                      hardware_dma
                      hardware_timer)

pico_add_extra_outputs(barbecue)
pico_enable_stdio_usb(barbecue ENABLED)

set_property(TARGET barbecue
             PROPERTY C_STANDARD 23)

#pico_set_binary_type(barbecue no_flash)
#pico_set_binary_type(barbecue copy_to_ram)
