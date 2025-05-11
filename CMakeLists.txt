cmake_minimum_required(VERSION 3.5)
project(my_cpp_api)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_notes_api main.cpp)

add_subdirectory(crow)
target_link_libraries(cpp_notes_api PRIVATE Crow)
