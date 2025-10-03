/**
 * This file tests class Dimensionality.
 */

#include "Dimensionality.h"
#include "Exponent.h"

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
};

// Tests invalid construction
TEST_F(DimensionalityTest, BadConstruction)
{
    EXPECT_THROW(Dimensionality::get("", "L"), std::invalid_argument);
    EXPECT_THROW(Dimensionality::get("Length", ""), std::invalid_argument);
    Dimensionality::get("Length", "L");
    EXPECT_THROW(Dimensionality::get("Length", "M"), std::invalid_argument);
    Dimensionality::get("Mass", "M");
    EXPECT_THROW(Dimensionality::get("Mass", "L"), std::invalid_argument);
}

// Tests valid construction
TEST_F(DimensionalityTest, Construction)
{
    EXPECT_EQ("", Dimensionality().to_string());

    auto length = Dimensionality::get("Length", "L");
    EXPECT_EQ("L", length.to_string());
}

// Tests multiplication
TEST_F(DimensionalityTest, Multiplication)
{
    auto length = Dimensionality::get("Length", "L");
    EXPECT_EQ("L^2", length.multiply(length).to_string());
    auto mass = Dimensionality::get("Mass", "M");
    EXPECT_EQ("L·M", length.multiply(mass).to_string());
}

// Tests exponentiation
TEST_F(DimensionalityTest, Exponentiation)
{
    auto length = Dimensionality::get("Length", "L");
    EXPECT_EQ("L^2", length.pow(2).to_string());
    EXPECT_EQ("L^-1", length.pow(-1).to_string());
    EXPECT_EQ("L^(-2/3)", length.pow(Exponent(-2, 3)).to_string());
}

// Tests division
TEST_F(DimensionalityTest, Division)
{
    auto length = Dimensionality::get("Length", "L");
    auto time = Dimensionality::get("Time", "T");
    EXPECT_EQ("L·T^-1", length.divideBy(time).to_string());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
