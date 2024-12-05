add_subdirectory(Utils)

add_library(AdventOfCode-lib
    HistorianHysteria/src/HistorianHysteria.cpp
    RedNosedReports/src/RedNosedReports.cpp
    MullItOver/src/MullItOver.cpp
    CeresSearch/src/CeresSearch.cpp
    PrintQueue/src/PrintQueue.cpp

    HistorianHysteria/inc/HistorianHysteria.hpp
    RedNosedReports/inc/RedNosedReports.hpp
    MullItOver/inc/MullItOver.hpp
    CeresSearch/inc/CeresSearch.hpp
    PrintQueue/inc/PrintQueue.hpp)

target_include_directories(AdventOfCode-lib
    PRIVATE
    HistorianHysteria/src
    RedNosedReports/src
    MullItOver/src
    CeresSearch/src
    PrintQueue/src
    PUBLIC
    HistorianHysteria/inc
    RedNosedReports/inc
    MullItOver/inc
    CeresSearch/inc
    PrintQueue/inc)

target_link_libraries(AdventOfCode-lib
    PUBLIC
    Utils-lib)