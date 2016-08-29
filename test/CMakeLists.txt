
add_executable (stringTest stringtest.cpp)
target_link_libraries(stringTest Pivot)
add_test(stringTest stringTest)

add_executable (sliceTest slicetest.cpp)
target_link_libraries(sliceTest Pivot)
add_test(sliceTest sliceTest)

add_executable (fileTest filetest.cpp)
target_link_libraries(fileTest Pivot)
add_test(fileTest fileTest)
