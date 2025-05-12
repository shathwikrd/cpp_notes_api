cmake_minimum_required(VERSION 3.14)
project(cpp_notes_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow needs Boost (for now)
find_package(Boost REQUIRED)

# Add path to nlohmann/json
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Add Crow
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.0+1
)
FetchContent_MakeAvailable(crow)

add_executable(cpp_notes_api main.cpp)

target_link_libraries(cpp_notes_api
  PRIVATE
  Crow::Crow
  nlohmann_json::nlohmann_json
  Boost::boost
)
