
add_executable (stringTest stringtest.cpp)
target_link_libraries(stringTest pivot)
add_test(stringTest stringTest)

add_executable (sliceTest slicetest.cpp)
target_link_libraries(sliceTest pivot)
add_test(sliceTest sliceTest)

add_executable (fileTest filetest.cpp)
target_link_libraries(fileTest pivot)
add_test(fileTest fileTest)

add_executable (optionalTest optionalTest.cpp)
target_link_libraries(optionalTest pivot)
add_test(optionalTest optionalTest)
