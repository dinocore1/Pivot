cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

option (BuildTests "Build unit tests" ON)

add_subdirectory(src)

# unit tests
if(BuildTests)
	set(VERSION_GTEST "1.8.0" CACHE STRING "Google Test framework version")
	enable_testing ()
	add_subdirectory(3rdParty/gtest)
	add_subdirectory(tests)
endif()

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
