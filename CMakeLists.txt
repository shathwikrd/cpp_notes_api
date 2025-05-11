cmake_minimum_required(VERSION 3.10)
project(crow_api)

set(CMAKE_CXX_STANDARD 17)

include_directories(. ./crow ./nlohmann)

add_executable(crow_api main.cpp)