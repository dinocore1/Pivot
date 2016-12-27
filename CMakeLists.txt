cmake_minimum_required (VERSION 2.8.11)
project (Pivot)

set (Pivot_VERSION_MAJOR 1)
set (Pivot_VERSION_MINOR 0)

option (BuildTests "Build unit tests" ON)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in.cmake"
  "${PROJECT_BINARY_DIR}/src/config.h"
)

include_directories(include ${CMAKE_BINARY_DIR}/src)
file(GLOB pivot_headers include/pivot/*.h)
file(GLOB pivot_sources src/*.cpp)
add_library(pivot "${PROJECT_BINARY_DIR}/src/config.h" ${pivot_headers} ${pivot_sources})

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(pivot PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

install (
  TARGETS pivot EXPORT PivotConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin # this is for Windows
)
install (DIRECTORY include/ DESTINATION include)

# This make the project importable from the install directory
# put the config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake
install (EXPORT PivotConfig DESTINATION cmake)

# This makes the project importable from the build directory
export (TARGETS pivot FILE PivotConfig.cmake)
export (PACKAGE pivot)


if (BuildTests)
  enable_testing ()
  add_subdirectory(test)
endif()

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
