cmake_minimum_required(VERSION 3.10)
project(crow_api)

set(CMAKE_CXX_STANDARD 17)

add_executable(crow_api main.cpp)

# Crow and nlohmann/json are header-only
target_include_directories(crow_api PRIVATE /usr/local/include)
