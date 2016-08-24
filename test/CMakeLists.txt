
add_executable (stringTest stringtest.cpp)
target_link_libraries(stringTest Pivot)

add_test(Name stringTest Command stringTest)
