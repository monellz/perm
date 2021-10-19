add_executable(validation
  validation.cpp
)
target_link_libraries(validation
  gtest_main
  gmock

  dictorder
)