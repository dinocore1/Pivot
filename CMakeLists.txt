cmake_minimum_required (VERSION 2.8.11)
project (Pivot)

option (BuildTests "Build unit tests" ON)


configure_file(src/config.h.in.cmake src/config.h)
include_directories(include ${CMAKE_BINARY_DIR}/src)
file(GLOB pivot_headers include/pivot/*.h)
file(GLOB pivot_sources src/*.cpp)
add_library(pivot "${CMAKE_BINARY_DIR}/src/config.h" ${pivot_headers} ${pivot_sources})
target_include_directories(pivot PUBLIC include)

if (BuildTests)
  enable_testing ()
  add_subdirectory(test)
endif()

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
