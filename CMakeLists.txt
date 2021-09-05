cmake_minimum_required(VERSION 2.6)
project(quadtree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions( -DSRCDIR=\"${CMAKE_SOURCE_DIR}/\")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Werror=reorder")

include_directories( ${CMAKE_SOURCE_DIR} )

add_executable( ex_rand
  examples/example_random_pts.cpp
  src/BoundingBox.cpp
  src/Data2D.cpp
  src/QuadTree.cpp
)