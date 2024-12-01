add_library(AdventOfCode-lib
    HistorianHysteria/src/HistorianHysteria.cpp

    HistorianHysteria/inc/HistorianHysteria.hpp)

target_include_directories(AdventOfCode-lib
    PRIVATE
    HistorianHysteria/src
    PUBLIC
    HistorianHysteria/inc)