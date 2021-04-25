cmake_minimum_required (VERSION 3.8)
project (min_max_heap LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(src/ lib/)
add_executable (min_max_heap_test test/min_max_heap_test.cpp)