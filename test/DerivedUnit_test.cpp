/**
 * This file tests class DerivedUnit.
 */

#include "Unit.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing the class
class DimensionTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    DimensionTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~DimensionTest()
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
    Unit::Pimpl kilogram = Unit::getBase("kilogram", "kg");
    Unit::Pimpl meter = Unit::getBase("meter", "m");
    Unit::Pimpl second = Unit::getBase("second", "s");
};

// Tests construction
TEST_F(DimensionTest, Construction)
{
    const auto kg_m = kilogram->multiply(meter);
    EXPECT_EQ("kg·m", kg_m->to_string());
    EXPECT_EQ("kg·m^2", kg_m->multiply(meter)->to_string());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
