cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pivot VERSION 0.1.0 LANGUAGES CXX C)

OPTION(BUILD_TESTS "Build unit tests" ON)



add_library(pivot
  include/pivot/ArrayList.h
  include/pivot/Atomic.h
  include/pivot/File.h
  include/pivot/FileOutputStream.h
  include/pivot/InputStream.h
  include/pivot/Memory.h
  include/pivot/Optional.h
  include/pivot/OutputStream.h
  include/pivot/Pivot.h
  include/pivot/SharedBuffer.h
  include/pivot/Slice.h
  include/pivot/Status.h
  include/pivot/String8.h
  include/pivot/TypeHelpers.h
  include/pivot/Types.h
  include/pivot/View.h
  src/ArrayListImpl.cpp
  src/Memory.cpp
  src/SharedBuffer.cpp
  src/Static.cpp
  src/String8.cpp
)

target_include_directories(pivot
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src
)


install(TARGETS pivot
  EXPORT pivotConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin # this is for Windows
)

install(DIRECTORY include/
  DESTINATION include
)

install(EXPORT pivotConfig
  DESTINATION cmake
)
if(BUILD_TESTS)
  add_executable(stringtest tests/stringtest.cpp)
  target_link_libraries(stringtest pivot)
  add_test(stringtest stringtest)
endif()
