# Debug (-g) otherwise leaves this 20kHz control chain at GCC's default -O0.
# Keep symbols and IEEE arithmetic; optimize only the interrupt call path.
get_target_property(_motor_rt_sources ${HPM_SDK_LIB} SOURCES)
foreach(_motor_rt_source IN LISTS _motor_rt_sources)
    string(REPLACE "\\" "/" _motor_rt_path "${_motor_rt_source}")
    if(_motor_rt_path MATCHES "/middleware/hpm_mcl_v2/" OR
       _motor_rt_path MATCHES "/motor/(bldc_foc|encoder_mt6816|motor_ident)\\.c$" OR
       _motor_rt_path MATCHES "/generated/hpm_mcl_loop\\.c$" OR
       _motor_rt_path MATCHES "/drivers/src/hpm_spi_drv\\.c$")
        set_property(SOURCE "${_motor_rt_source}" TARGET_DIRECTORY ${HPM_SDK_LIB}
                     APPEND PROPERTY COMPILE_OPTIONS -O2)
    endif()
endforeach()
