add_executable(DailyTask_UT DailyTaskTests.cpp)

target_link_libraries(DailyTask_UT
    PRIVATE
    GTest::gtest_main
    DailyTask-lib)
add_test(Tests DailyTask_UT)
