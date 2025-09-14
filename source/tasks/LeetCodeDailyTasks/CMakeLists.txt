add_library(DailyTask-lib src/DailyTask.hpp)
set_target_properties(DailyTask-lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(DailyTask-lib PUBLIC src)
