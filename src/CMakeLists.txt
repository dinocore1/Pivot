

set(Pivot_SRC_FILES
  "String.cpp"
)

include_directories(../include)
add_library (Pivot ${Pivot_SRC_FILES})
target_include_directories (Pivot PUBLIC ../include)
