add_library(BracesValidator-lib
    src/BracesValidator.cpp

    inc/BracesValidator.hpp)

target_include_directories(BracesValidator-lib PRIVATE src PUBLIC inc)
