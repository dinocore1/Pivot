
add_executable(sharedBufferTest sharedBufferTest.cpp)
target_link_libraries(sharedBufferTest Pivot gtest)
add_test(sharedBufferTest sharedBufferTest)

add_executable(arrayListTest ArrayListTest.cpp)
target_link_libraries(arrayListTest Pivot gtest)
add_test(arrayListTest arrayListTest)

# add_executable (stringTest stringtest.cpp)
# target_link_libraries(stringTest pivot)
# add_test(stringTest stringTest)

# add_executable (sliceTest slicetest.cpp)
# target_link_libraries(sliceTest pivot)
# add_test(sliceTest sliceTest)

# add_executable (fileTest filetest.cpp)
# target_link_libraries(fileTest pivot)
# add_test(fileTest fileTest)

# add_executable (optionalTest optionalTest.cpp)
# target_link_libraries(optionalTest pivot)
# add_test(optionalTest optionalTest)
