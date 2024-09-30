cmake_minimum_required(VERSION 3.10)

project(TerrainGeneration VERSION 1.0)

add_compile_options(-g -Wall -Wextra -Wpedantic -O3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(TerrainGeneration
    src/terrain.cpp
    src/perlin.cpp
    src/shader.cpp
    src/camera.cpp
    src/chunk.cpp
    src/texture.cpp
    src/fbm.cpp
    src/cube.cpp
    src/application.cpp
    src/window.cpp
    src/main.cpp
    events/event_manager.cpp
    external/glad/glad.c
)

find_package(glfw3 REQUIRED)

target_include_directories(TerrainGeneration PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/events
        ${PROJECT_SOURCE_DIR}/external
        ${PROJECT_SOURCE_DIR}/external/glm
)

add_link_options(-fsanitize=address) 

target_link_libraries(TerrainGeneration PRIVATE glfw) 

