add_executable(validation
  validation.cpp
)

add_executable(benchmark
  benchmark.cpp
)

target_link_libraries(validation
  gtest_main
  gmock

  dictorder
  ascendorder
  descendorder
  sjtorder
)
target_link_libraries(benchmark
  gtest_main
  gmock

  dictorder
)