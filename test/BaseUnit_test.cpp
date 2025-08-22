/**
 * This file tests class BaseUnit.
 */

#include "Unit.h"

#include "Dimension.h"

#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace quantity;

/// The fixture for testing the class
class BaseUnitTest : public ::testing::Test
{
protected:
    Dimension length;
    Dimension mass;

    // You can remove any or all of the following functions if its body
    // is empty.

    BaseUnitTest()
        : length(Dimension("Length", "L"))
        , mass(Dimension("Mass", "M"))
    {
        // You can do set-up work for each test here.
    }

    virtual ~BaseUnitTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
        Dimension::clear();
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

// Tests construction
TEST_F(BaseUnitTest, Construction)
{
    EXPECT_THROW(BaseUnit("", "m"), std::invalid_argument);
    EXPECT_THROW(BaseUnit("meter", ""), std::invalid_argument);

    BaseUnit meter{"meter", "m"};
    EXPECT_FALSE(meter.isDimensionless());
    EXPECT_FALSE(meter.isOffset());

    EXPECT_THROW(BaseUnit("meter", "s"), std::invalid_argument);
    EXPECT_THROW(BaseUnit("bar", "m"), std::invalid_argument);
}

// Tests convertibility
TEST_F(BaseUnitTest, Convertibility)
{
    BaseUnit meter{"meter", "m"};
    EXPECT_TRUE(meter.isConvertible(meter));

    BaseUnit kilogram{"kilogram", "kg"};
    EXPECT_FALSE(meter.isConvertible(kilogram));
    EXPECT_FALSE(kilogram.isConvertible(meter));
}

// Tests multiplication
TEST_F(BaseUnitTest, Multiplication)
{
    BaseUnit meter{"meter", "m"};
    BaseUnit kilogram{"kilogram", "kg"};
    EXPECT_THROW(meter.multiply(kilogram), std::logic_error);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
