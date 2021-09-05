cmake_minimum_required(VERSION 2.6)
project(lagrangiansolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions( -DSRCDIR=\"${CMAKE_SOURCE_DIR}/\")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Werror=reorder")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -DBOOST_LOG_DYN_LINK -DNDEBUG")

include_directories( ${CMAKE_SOURCE_DIR}
                     ${GTEST_INCLUDE_DIRS}
)

add_executable( ex_rand
  examples/example_random_pts.cpp
  src/BoundingBox.cpp
  src/Data2D.cpp
  src/QuadTree.cpp
)