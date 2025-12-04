cmake_minimum_required(VERSION 3.16)
project(horizon)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILES src/*.cpp)

add_executable(horizon ${SRC_FILES})

target_include_directories(horizon PUBLIC include)
