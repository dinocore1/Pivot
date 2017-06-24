

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# enable parallel build
	set( ENV{CL} /MP )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# Increase warning levels
	add_compile_options(-Wall -Wextra -pedantic)
endif()


add_library(${PROJECT_NAME}
	"SharedBuffer.cpp"
  "ArrayListImpl.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
