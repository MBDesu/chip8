cmake_minimum_required(VERSION 4.1)
project(mbdchip8)

set(CXX_STANDARD_REQUIRED 23)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(BREW_INCLUDES /opt/homebrew/include)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${BREW_INCLUDES}
)

file(GLOB all_src
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  main.cpp
)

add_executable(mbdchip8 ${all_src})
target_link_libraries(mbdchip8
  /opt/homebrew/lib/libsdl2.dylib)
target_compile_features(mbdchip8 PUBLIC cxx_std_23)
