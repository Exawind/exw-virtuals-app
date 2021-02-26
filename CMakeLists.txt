cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)
project(ExwVirtuals CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL
  "Create compile commands database")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXW_KOKKOS_PATH "ext/kokkos")
add_subdirectory(${EXW_KOKKOS_PATH})

add_executable(exw_virtuals)
add_subdirectory(src)