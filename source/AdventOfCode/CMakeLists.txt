add_library(AdventOfCode-lib
    HistorianHysteria/src/HistorianHysteria.cpp
    RedNosedReports/src/RedNosedReports.cpp

    HistorianHysteria/inc/HistorianHysteria.hpp
    RedNosedReports/inc/RedNosedReports.hpp)

target_include_directories(AdventOfCode-lib
    PRIVATE
    HistorianHysteria/src
    RedNosedReports/src
    PUBLIC
    HistorianHysteria/inc
    RedNosedReports/inc)