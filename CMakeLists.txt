cmake_minimum_required(VERSION 3.16)
project(horizon)

set(CMAKE_CXX_STANDARD 20)

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Executable
add_executable(horizon ${SRC_FILES})

# Include directories
target_include_directories(horizon PUBLIC include)
