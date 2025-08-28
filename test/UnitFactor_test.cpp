/**
 * This file tests class DimFactor.
 */

#include "DimFactor.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing the class
class DimFactorTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    DimFactorTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~DimFactorTest()
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
};

// Tests construction
TEST_F(DimFactorTest, Construction)
{
    EXPECT_EQ("Length", DimFactor(length).to_string());
    EXPECT_EQ("Length^2", DimFactor(length, 2).to_string());
    EXPECT_EQ("Length^-1", DimFactor(length, -1).to_string());
    EXPECT_EQ("Length^(-2/3)", DimFactor(length, -2, 3).to_string());
}

// Tests exponentiation
TEST_F(DimFactorTest, Exponentiation)
{
    EXPECT_THROW(DimFactor(length).pow(1, 0).to_string(), std::domain_error);
    EXPECT_EQ("Length^2", DimFactor(length).pow(2).to_string());
    EXPECT_EQ("Length^-1", DimFactor(length).pow(-1).to_string());
    EXPECT_EQ("Length^(-2/3)", DimFactor(length).pow(2, -3).to_string());
    EXPECT_EQ("Length^0", DimFactor(length).pow(0, -3).to_string());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
