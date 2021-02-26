target_sources(exw_virtuals PRIVATE
  Algorithm.cpp
  main.cpp)

target_link_libraries(exw_virtuals PRIVATE
  Kokkos::kokkos)
