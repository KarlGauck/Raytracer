# Explains itsself
cmake_minimum_required(VERSION 2.8)

project(raytracer)

add_subdirectory(./libs/SDL2-2.26.5)

# Sets into which executable all the code should be build
add_executable(raytracer raytracer.cpp shader.cpp shaderProgram.cpp shader.hpp shaderProgram.hpp)
target_link_libraries(raytracer SDL2)
target_link_libraries(raytracer GL)
target_link_libraries(raytracer GLU)
target_link_libraries(raytracer GLEW)

# makes cmake copy our binary into the bin dir
install(TARGETS raytracer DESTINATION bin)
