/**
 * This file tests class BaseQuantity.
 */

#include "BaseQuantity.h"

#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace quantity;

/// The fixture for testing the class
class BaseQuantityTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    BaseQuantityTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~BaseQuantityTest()
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
    Dimension mass{"Mass", "M"};
    Unit::Pimpl meter = Unit::getBase("meter", "m");
    Unit::Pimpl kilogram = Unit::getBase("kilogram", "kg");
};

// Tests construction
TEST_F(BaseQuantityTest, Construction)
{
    auto lengthQuant = BaseQuantity::get(length, meter);
    EXPECT_THROW(Unit::getBase(length, kilogram), std::invalid_argument);
    EXPECT_THROW(Unit::getBase(mass, meter), std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
