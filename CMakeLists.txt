cmake_minimum_required(VERSION 3.10)

project(TerrainGeneration VERSION 1.0)

add_compile_options(-g -Wall -Wextra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(TerrainGeneration
    src/main.cpp
    src/terrain.cpp
    src/perlin.cpp
    src/shader.cpp
    src/utility.cpp
    src/vec2.cpp
    src/camera.cpp
    src/terrain_renderer.cpp
    src/chunk.cpp
    external/glad/glad.c
)

find_package(glfw3 REQUIRED)

target_include_directories(TerrainGeneration PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glad
)

target_link_libraries(TerrainGeneration PRIVATE glfw)

