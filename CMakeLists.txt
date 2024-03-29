cmake_minimum_required(VERSION 3.10)
project(MPRPC)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/example)
include_directories(${PROJECT_SOURCE_DIR}/src/include)

set(muduo "/root/GaoSheng/build/release-install-cpp11")
link_directories(${muduo}/lib)
include_directories(${muduo}/include)

add_subdirectory(src)
add_subdirectory(example)


