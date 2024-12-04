add_subdirectory(Utils)

add_library(AdventOfCode-lib
    HistorianHysteria/src/HistorianHysteria.cpp
    RedNosedReports/src/RedNosedReports.cpp
    MullItOver/src/MullItOver.cpp
    CeresSearch/src/CeresSearch.cpp

    HistorianHysteria/inc/HistorianHysteria.hpp
    RedNosedReports/inc/RedNosedReports.hpp
    MullItOver/inc/MullItOver.hpp
    CeresSearch/inc/CeresSearch.hpp)

target_include_directories(AdventOfCode-lib
    PRIVATE
    HistorianHysteria/src
    RedNosedReports/src
    MullItOver/src
    CeresSearch/src
    PUBLIC
    HistorianHysteria/inc
    RedNosedReports/inc
    MullItOver/inc
    CeresSearch/inc)

target_link_libraries(AdventOfCode-lib
    PUBLIC
    Utils-lib)