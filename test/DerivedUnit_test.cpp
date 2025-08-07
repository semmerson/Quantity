/**
 * This file tests class DerivedUnit.
 */

#include "BaseUnit.h"
#include "DerivedUnit.h"

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
    BaseUnit kilogram{Dimension("Mass"), "kilogram", "kg"};
    BaseUnit meter{Dimension("Length"), "meter", "m"};
    BaseUnit second{Dimension("Time"), "second", "s"};
};

// Tests construction
TEST_F(DimensionTest, Construction)
{
    auto k_m = kilogram.multiply(meter);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
