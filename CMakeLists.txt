cmake_minimum_required(VERSION 3.16)
project(Sgames VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")

add_executable(Sgames ${SOURCES})

target_include_directories(Sgames PRIVATE "${PROJECT_SOURCE_DIR}/include/Sgames")

find_package(SDL3 REQUIRED)
target_link_libraries(Sgames PRIVATE SDL3::SDL3)

find_package(SDL3_image REQUIRED)
target_link_libraries(Sgames PRIVATE SDL3_image::SDL3_image)
