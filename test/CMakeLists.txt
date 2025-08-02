add_executable(Dimension_test Dimension_test.cpp)
target_link_libraries(Dimension_test libquant ${GTEST_LIBRARY})
add_test(Dimension_test Dimension_test)

add_executable(Calendar_test Calendar_test.cpp)
target_link_libraries(Calendar_test libquant ${GTEST_LIBRARY})
add_test(Calendar_test Calendar_test)

add_executable(AffineScale_test AffineScale_test.cpp)
target_link_libraries(AffineScale_test libquant ${GTEST_LIBRARY})
add_test(AffineScale_test AffineScale_test)

add_executable(BaseUnit_test BaseUnit_test.cpp)
target_link_libraries(BaseUnit_test libquant ${GTEST_LIBRARY})
add_test(BaseUnit_test BaseUnit_test)