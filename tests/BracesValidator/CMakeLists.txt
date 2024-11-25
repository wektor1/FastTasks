add_executable(BracesValidator_UT BracesValidatorTests.cpp)

target_link_libraries(BracesValidator_UT
    PRIVATE
    GTest::gtest_main
    BracesValidator-lib)
add_test(Tests BracesValidator_UT)
