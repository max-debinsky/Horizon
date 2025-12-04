cmake_minimum_required(VERSION 3.16)
project(app)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILES src/*.cpp)

add_executable(app ${SRC_FILES})

target_include_directories(app PUBLIC include)
