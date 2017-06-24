
add_executable(sharedBufferTest sharedBufferTest.cpp)
target_link_libraries(sharedBufferTest Pivot GTest::main)
add_test(sharedBufferTest sharedBufferTest)

add_executable(arrayListTest ArrayListTest.cpp)
target_link_libraries(arrayListTest Pivot GTest::main)
add_test(arrayListTest arrayListTest)
