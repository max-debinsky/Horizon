cmake_minimum_required(VERSION 3.16)
project(horizon)

set(CMAKE_CXX_STANDARD 20)

# List all source files explicitly
set(SRC_FILES
    src/main.cpp
    src/output.cpp
    src/color.cpp
    src/rgb.cpp
    src/vector3.cpp
    src/ray.cpp
    src/ray_object.cpp
    src/object_group.cpp
    src/material.cpp
    src/camera.cpp
    src/renderer.cpp
    src/sphere.cpp
    src/interval.cpp
)

add_executable(horizon ${SRC_FILES})

# Include directories for headers
target_include_directories(horizon PUBLIC include)
