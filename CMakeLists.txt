cmake_minimum_required(VERSION 3.16)
project(horizon)

set(CMAKE_CXX_STANDARD 20)

# List source files explicitly
set(SRC_FILES
    src/main.cpp
    src/output.cpp
)

add_executable(horizon ${SRC_FILES})

target_include_directories(horizon PUBLIC include)
