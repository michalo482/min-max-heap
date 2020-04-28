cmake_minimum_required (VERSION 3.8)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories("${CMAKE_SOURCE_DIR}/extern")

add_executable(min_max_heap "main.cpp" "test/min_max_heap_test.cpp")

set_property(TARGET min_max_heap PROPERTY CXX_STANDARD 17)