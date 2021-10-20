cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(perm LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty)

add_library(dictorder STATIC
  src/dict_order.cpp
)
add_library(ascendorder STATIC
  src/ascend_order.cpp
)
add_library(descendorder STATIC
  src/descend_order.cpp
)
add_library(sjtorder STATIC
  src/sjt_order.cpp
)


add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/googletest)

enable_testing()

add_subdirectory(test)
