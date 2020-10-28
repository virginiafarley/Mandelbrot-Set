cmake_minimum_required(VERSION 3.11.3)

project(Mandelbrot_Set)

set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/opencv/)
# set(OpenCV_INCLUDE_DIRS ${OpenCV_ROOT}/include)


# add_subdirectory(${OpenCV_DIR})
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

# find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h REQUIRED)
# find_library(FREEIMAGE_LIBRARY libfreeimageplus)
# include_directories(${FREEIMAGE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB project_SRCS src/*.cpp)

add_executable(mandelbrot_set ${project_SRCS})
# target_link_libraries(mandelbrot_set ${freeimage_LIBRARIES})