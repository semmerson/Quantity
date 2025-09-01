add_executable(Dimension_test Dimension_test.cpp)
target_link_libraries(Dimension_test libquant ${GTEST_LIBRARY})
add_test(Dimension_test Dimension_test)

add_executable(Calendar_test Calendar_test.cpp)
target_link_libraries(Calendar_test libquant ${GTEST_LIBRARY})
add_test(Calendar_test Calendar_test)

add_executable(BaseUnit_test BaseUnit_test.cpp)
target_link_libraries(BaseUnit_test libquant ${GTEST_LIBRARY})
add_test(BaseUnit_test BaseUnit_test)

add_executable(AffineUnit_test AffineUnit_test.cpp)
target_link_libraries(AffineUnit_test libquant ${GTEST_LIBRARY})
add_test(AffineUnit_test AffineUnit_test)

#add_executable(BaseQuantity_test BaseQuantity_test.cpp)
#target_link_libraries(BaseQuantity_test libquant ${GTEST_LIBRARY})
#add_test(BaseQuantity_test BaseQuantity_test)

add_executable(Exponent_test Exponent_test.cpp)
target_link_libraries(Exponent_test libquant ${GTEST_LIBRARY})
add_test(Exponent_test Exponent_test)

add_executable(DerivedUnit_test DerivedUnit_test.cpp)
target_link_libraries(DerivedUnit_test libquant ${GTEST_LIBRARY})
add_test(DerivedUnit_test DerivedUnit_test)

#add_executable(DimFactor_test DimFactor_test.cpp)
#target_link_libraries(DimFactor_test libquant ${GTEST_LIBRARY})
#add_test(DimFactor_test DimFactor_test)

#add_executable(Dimensionality_test Dimensionality_test.cpp)
#target_link_libraries(Dimensionality_test libquant ${GTEST_LIBRARY})
#add_test(Dimensionality_test Dimensionality_test)