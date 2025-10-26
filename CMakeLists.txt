cmake_minimum_required(VERSION 3.10)
project(lab3_oop_var23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(include)

add_library(figures_lib
  src/array/constructors.cpp
  src/array/tools.cpp
  src/figures/constructors.cpp
  src/figures/operators.cpp
  src/figures/tools.cpp
)


add_executable(main_app ./src/main.cpp)
target_link_libraries(main_app PRIVATE figures_lib)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE figures_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
