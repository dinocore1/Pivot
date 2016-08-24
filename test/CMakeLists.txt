
add_executable (stringTest stringtest.cpp)
target_link_libraries(stringTest Pivot)

add_test(stringTest stringTest)
