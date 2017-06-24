cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include("cmake/HunterGate.cmake")

# 1. Try to detect hunter by:
#   * cmake variable
#   * environment variable
#   * in HOME (`.hunter` directory)
#   * in SYSTEMDRIVE (`.hunter` directory, windows only)
#   * in USERPROFILE (`.hunter` directory, windows only)
# 2. if failed, download it
# 3. set HUNTER_GATE_* variables
# 4. include master file: 'include(${HUNTER_SELF}/cmake/Hunter)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.18.12.tar.gz"
    SHA1 "7e8c74787e08c476484d3e5106524fe7a5a0cc56"
)

project(Pivot VERSION 0.1 LANGUAGES CXX)

option (BuildTests "Build unit tests" ON)

add_subdirectory(src)

# unit tests
if(BuildTests)
	hunter_add_package(GTest)
	find_package(GTest CONFIG REQUIRED)
	enable_testing ()
	add_subdirectory(tests)
endif()

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
