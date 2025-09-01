/**
 * This file tests class BaseUnit.
 */

#include "Unit.h"

#include "BaseUnit.h"
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
    EXPECT_TRUE(meter.isBase());
    EXPECT_FALSE(meter.isDimensionless());
    EXPECT_FALSE(meter.isOffset());

    EXPECT_THROW(BaseUnit("meter", "s"), std::invalid_argument);
    EXPECT_THROW(BaseUnit("bar", "m"), std::invalid_argument);
}

// Tests convertibility
TEST_F(BaseUnitTest, Convertibility)
{
    auto meter = Unit::getBase("meter", "m");
    EXPECT_TRUE(meter->isConvertible(meter));

    auto kilogram = Unit::getBase("kilogram", "kg");
    EXPECT_FALSE(meter->isConvertible(kilogram));
    EXPECT_FALSE(kilogram->isConvertible(meter));
}

// Tests multiplication
TEST_F(BaseUnitTest, Multiplication)
{
    auto meter = Unit::getBase("meter", "m");
    auto kilogram = Unit::getBase("kilogram", "kg");
    auto kg_m = meter->multiply(kilogram);
    EXPECT_EQ("kg·m", kg_m->to_string());
    EXPECT_FALSE(kg_m->type() == Unit::Type::base);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
