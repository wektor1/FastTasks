add_library(Utils-lib
    src/Parsers.cpp

    inc/Utils/Parsers.hpp)

target_include_directories(Utils-lib
    PRIVATE
    src
    PUBLIC
    inc)