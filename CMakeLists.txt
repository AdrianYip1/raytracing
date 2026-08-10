cmake_minimum_required(VERSION 3.15)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/enginemath)

add_executable(raytracer
    src/main.cpp 
    "src/color.cpp" 
    "src/ray.cpp" 
    "src/hittable.cpp" 
    "src/sphere.hpp" 
    "src/sphere.cpp"
    "src/hittable_list.cpp"
    "src/defines.h"
    "src/interval.cpp" 
    "src/camera.cpp" 
    "src/material.cpp")

target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(raytracer PRIVATE enginemath::enginemath)

set_target_properties(raytracer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_options(raytracer PRIVATE $<$<CONFIG:Release>:/O2>)
else()
    target_compile_options(raytracer PRIVATE $<$<CONFIG:Release>:-O2>)
endif()
