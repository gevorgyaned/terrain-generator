cmake_minimum_required(VERSION 3.10)

project(TerrainGeneration VERSION 1.0)

set(PROJECT_SOURCE_DIR ~/Graphics/terrain-generation)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(TerrainGeneration
    src/main.cpp
    src/terrain.cpp
    src/perlin.cpp
    src/shader.cpp
    src/utility.cpp
    src/vec2.cpp
    ../external/glad/glad.c
)

target_include_directories(TerrainGeneration PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../external/glm
)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(TerrainGeneration ${OPENGL_LIBRARIES})
endif()

target_link_libraries(TerrainGeneration glfw)
