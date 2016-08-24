cmake_minimum_required (VERSION 2.8.11)
project (Pivot)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(
    GLOB_RECURSE
    SRC_FILES
    src/*.cpp
)

file(
    GLOB_RECURSE
    INCLUDE_FILES
    include/*.h
)

add_library (Pivot ${SRC_FILES})
target_include_directories (Pivot PUBLIC ${INCLUDE_FILES})


if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
