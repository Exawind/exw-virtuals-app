cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)
project(ExwVirtuals CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL
  "Create compile commands database")

option(EXAWIND_USE_EXTERNAL_KOKKOS "Use external Kokkos installation" OFF)
option(EXAWIND_TEST_VIRTUALS "Activate testing virtual device functions" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EXAWIND_USE_EXTERNAL_KOKKOS)
  find_package(Kokkos REQUIRED)
else()
set(EXW_KOKKOS_PATH "ext/kokkos")
add_subdirectory(${EXW_KOKKOS_PATH})
endif()

add_executable(exw_virtuals)
add_subdirectory(src)
