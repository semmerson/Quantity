/**
 * This file tests class BaseUnit.
 */

#include <BaseInfo.h>
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
    EXPECT_THROW(BaseInfo("", "m"), std::invalid_argument);
    EXPECT_THROW(BaseInfo("meter", ""), std::invalid_argument);

    BaseInfo meter{"meter", "m"};

    EXPECT_THROW(BaseInfo("meter", "s"), std::invalid_argument);
    EXPECT_THROW(BaseInfo("bar", "m"), std::invalid_argument);
}

// Tests to_string()
TEST_F(BaseUnitTest, to_string)
{
    BaseInfo meter{"meter", "m"};
    EXPECT_EQ("m", meter.to_string());
}

// Tests hashing
TEST_F(BaseUnitTest, Hashing)
{
    BaseInfo meter{"meter", "m"};
    BaseInfo second{"second", "s"};
    EXPECT_NE(meter.hash(), second.hash());
}

// Tests comparison
TEST_F(BaseUnitTest, Comparison)
{
    BaseInfo meter{"meter", "m"};
    EXPECT_EQ(0, meter.compare(meter));

    BaseInfo second{"second", "s"};
    EXPECT_GT(0, meter.compare(second));
    EXPECT_LT(0, second.compare(meter));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
