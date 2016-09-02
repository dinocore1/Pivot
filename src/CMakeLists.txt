
configure_file(config.h.in config.h)

set(Pivot_SRC_FILES
  "config.h.in"
  "String8.cpp"
  "File.cpp"
  "FileOutputStream.cpp"
)

include_directories(../include ${CMAKE_CURRENT_BINARY_DIR})
add_library (Pivot ${Pivot_SRC_FILES})
target_include_directories (Pivot PUBLIC ../include)
