if (EXAWIND_TEST_VIRTUALS)
  target_compile_definitions(exw_virtuals PRIVATE EXAWIND_TEST_VIRTUALS)
  target_sources(exw_virtuals PRIVATE
    Algorithm.cpp)
endif()

target_sources(exw_virtuals PRIVATE
  main.cpp)
target_link_libraries(exw_virtuals PRIVATE
  Kokkos::kokkos)
