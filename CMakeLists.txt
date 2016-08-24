cmake_minimum_required (VERSION 2.8.11)
project (Pivot)

enable_testing ()

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)



if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
