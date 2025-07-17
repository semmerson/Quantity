add_executable(Dimension_test Dimension_test.cpp)
target_link_libraries(Dimension_test libquant ${GTEST_LIBRARY})
add_test(Dimension_test Dimension_test)