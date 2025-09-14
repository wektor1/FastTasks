add_subdirectory(BracesValidator)
add_subdirectory(DailyTask)

add_custom_target(UT
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMAND ${CMAKE_CTEST_COMMAND}
    VERBATIM
    USES_TERMINAL)