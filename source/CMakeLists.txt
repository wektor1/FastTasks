add_subdirectory(tasks)

add_executable(FastTasks main.cpp)
target_link_libraries(FastTasks PUBLIC BracesValidator-lib)