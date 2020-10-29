cmake_minimum_required(VERSION 3.11.3)

project(Mandelbrot_Set)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB project_SRCS src/*.cpp)

add_executable(mandelbrot_set ${project_SRCS})
target_link_libraries(mandelbrot_set ${OpenCV_LIBRARIES} ${SDL2_LIBRARIES})