/**
 * This file tests class CanonicalUnit.
 */

#include "BaseInfo.h"
#include "Dimension.h"
#include "Unit.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing the class
class CanonicalUnitTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    CanonicalUnitTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~CanonicalUnitTest()
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
    //auto kilogram = Unit::getCanonical(BaseInfo("kilogram", "kg")); // Doesn't work
    Dimension mass{"Mass", "M"};
    Dimension length{"Length", "L"};
    Dimension time{"Time", "T"};
    const BaseInfo kgInfo{mass, "kilogram", "kg"};
    const BaseInfo mInfo{length, "meter", "m"};
    const BaseInfo sInfo{time, "second", "s"};
    // Replacing "Unit::Pimpl name{...}" in the following with "auto name = Unit::get(...)" doesn't
    // work
    const Unit::Pimpl kilogram{Unit::get(kgInfo)};
    const Unit::Pimpl meter{Unit::get(mInfo)};
    const Unit::Pimpl second{Unit::get(sInfo)};
};

// Tests multiplication
TEST_F(CanonicalUnitTest, Multiplication)
{
    const auto kg_m = kilogram->multiply(meter);
    EXPECT_EQ("kg·m", kg_m->to_string());
    EXPECT_EQ("kg·m^2", kg_m->multiply(meter)->to_string());
}

// Tests exponetiation
TEST_F(CanonicalUnitTest, Exponetiation)
{
    const auto perS = second->pow(Exponent(-1));
    EXPECT_EQ("s^-1", perS->to_string());
    const auto perS2 = perS->pow(Exponent(2));
    EXPECT_EQ("s^-2", perS2->to_string());
    const auto mPerS = meter->multiply(perS);
    EXPECT_EQ("m·s^-1", mPerS->to_string());
    EXPECT_EQ("m^2·s^-2", meter->multiply(second->pow(Exponent(-1)))->pow(Exponent(2))->to_string());
}

// Tests division
TEST_F(CanonicalUnitTest, Division)
{
    EXPECT_EQ("m·s^-1", meter->divideBy(second)->to_string());
}

// Tests conversion
TEST_F(CanonicalUnitTest, Conversion)
{
    auto converter = meter->getConverterTo(meter);
    EXPECT_EQ(0, converter.convert(0));
    EXPECT_EQ(1, converter.convert(1));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
