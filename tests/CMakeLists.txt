
add_executable(commonTests commonTests.cpp)
target_link_libraries(commonTests pivot gtest_main)
add_test(sharedBufferTest commonTests)
