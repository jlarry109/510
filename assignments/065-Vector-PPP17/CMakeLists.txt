cmake_minimum_required( VERSION 3.5)

project(ppp_ch17_vector LANGUAGES CXX )
set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)
find_package(Catch2 3 REQUIRED)

add_executable(vector1 vector1_tests.cpp)
target_link_libraries(vector1 PRIVATE Catch2::Catch2WithMain)

