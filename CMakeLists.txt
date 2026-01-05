cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)

add_executable(Main
src/main.cpp
src/window/Window.cpp
src/window/Events.cpp
src/graphics/Shader.cpp
src/graphics/Texture.cpp
src/loaders/png_loading.cpp)

target_link_libraries(
    Main
    GLEW::GLEW 
    glfw 
    OpenGL::GL
    PNG::PNG
)

add_custom_target(copy_res ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying resources to build directory"
)
add_dependencies(Main copy_res)