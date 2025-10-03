add_executable(Exponent_test Exponent_test.cpp)
target_link_libraries(Exponent_test libquant ${GTEST_LIBRARY})
add_test(Exponent_test Exponent_test)

#add_executable(Dimension_test Dimension_test.cpp)
#target_link_libraries(Dimension_test libquant ${GTEST_LIBRARY})
#add_test(Dimension_test Dimension_test)

add_executable(Dimensionality_test Dimensionality_test.cpp)
target_link_libraries(Dimensionality_test libquant ${GTEST_LIBRARY})
add_test(Dimensionality_test Dimensionality_test)

add_executable(Calendar_test Calendar_test.cpp)
target_link_libraries(Calendar_test libquant ${GTEST_LIBRARY})
add_test(Calendar_test Calendar_test)

#add_executable(Timestamp_test Timestamp_test.cpp)
#target_link_libraries(Timestamp_test libquant ${GTEST_LIBRARY})
#add_test(Timestamp_test Timestamp_test)

add_executable(BaseInfo_test BaseInfo_test.cpp)
target_link_libraries(BaseInfo_test libquant ${GTEST_LIBRARY})
add_test(BaseInfo_test BaseInfo_test)

add_executable(CanonicalUnit_test CanonicalUnit_test.cpp)
target_link_libraries(CanonicalUnit_test libquant ${GTEST_LIBRARY})
add_test(CanonicalUnit_test CanonicalUnit_test)

add_executable(AffineUnit_test AffineUnit_test.cpp)
target_link_libraries(AffineUnit_test libquant ${GTEST_LIBRARY})
add_test(AffineUnit_test AffineUnit_test)

add_executable(RefLogUnit_test RefLogUnit_test.cpp)
target_link_libraries(RefLogUnit_test libquant ${GTEST_LIBRARY})
add_test(RefLogUnit_test RefLogUnit_test)

add_executable(UnrefLogUnit_test UnrefLogUnit_test.cpp)
target_link_libraries(UnrefLogUnit_test libquant ${GTEST_LIBRARY})
add_test(UnrefLogUnit_test UnrefLogUnit_test)

#add_executable(BaseQuantity_test BaseQuantity_test.cpp)
#target_link_libraries(BaseQuantity_test libquant ${GTEST_LIBRARY})
#add_test(BaseQuantity_test BaseQuantity_test)
