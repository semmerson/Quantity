/**
 * This file tests class Dimensionality.
 */

#include "Dimensionality.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing the class
class DimensionalityTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    DimensionalityTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~DimensionalityTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Error.
    Dimension length{"Length", "L"};
    Dimension time{"Time", "T"};
};

// Tests construction
TEST_F(DimensionalityTest, Construction)
{
    EXPECT_EQ("", Dimensionality().to_string());
    EXPECT_EQ("Length", Dimensionality(length).to_string());
    EXPECT_EQ("Length^2", Dimensionality(length, 2).to_string());
    EXPECT_EQ("Length^-1", Dimensionality(length, -1).to_string());
    EXPECT_EQ("Length^(-2/3)", Dimensionality(length, -2, 3).to_string());
}

// Tests multiplication
TEST_F(DimensionalityTest, Multiplication)
{
    EXPECT_EQ("Length^2", Dimensionality(length).multiply(Dimensionality(length)).to_string());
#if 0
    EXPECT_EQ("Length^2", Dimensionality(length, 2).to_string());
    EXPECT_EQ("Length^-1", Dimensionality(length, -1).to_string());
    EXPECT_EQ("Length^(-2/3)", Dimensionality(length, -2, 3).to_string());
#endif
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
