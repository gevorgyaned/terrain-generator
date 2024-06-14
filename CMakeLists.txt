cmake_minimum_required(VERSION 3.10)
project(TerrainGenerator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(TerrainGenerator
    src/main.cpp
    #    src/terrain.cpp
    #    src/terrain.h
    src/shader.cpp
    ~/Graphics/external/glad/glad.c
)

# Link GLFW
target_link_libraries(TerrainGenerator glfw)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    target_include_directories(TerrainGenerator PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(TerrainGenerator ${OPENGL_gl_LIBRARY})
endif()

