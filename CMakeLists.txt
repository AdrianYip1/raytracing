cmake_minimum_required(VERSION 3.15)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer
    src/main.cpp)

target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(raytracer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_options(raytracer PRIVATE $<$<CONFIG:Release>:/O2>)
else()
    target_compile_options(raytracer PRIVATE $<$<CONFIG:Release>:-O2>)
endif()
