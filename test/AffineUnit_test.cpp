/**
 * This file tests class AffineUnit.
 */

#include "Unit.h"
#include "Dimension.h"
#include "gtest/gtest.h"

#include <stdexcept>

namespace {

using namespace quantity;
using namespace std;

/// The fixture for testing class `AffineUnit`
class AffineUnitTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    AffineUnitTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~AffineUnitTest()
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
    BaseUnit meter{"meter", "m"};
    BaseUnit kilogram{"kilogram", "kg"};
};

/// Tests construction
TEST_F(AffineUnitTest, Construction)
{
    EXPECT_THROW(AffineUnit(meter, 0, 1), std::logic_error);

    AffineUnit unit1{meter, 3, 1};
    EXPECT_TRUE(unit1.isOffset());
    EXPECT_FALSE(unit1.isDimensionless());
}

/// Tests Unit::isConvertible()
TEST_F(AffineUnitTest, IsConvertible)
{
    AffineUnit unit{meter, 3, 5};
    ASSERT_TRUE(meter.isConvertible(unit));
    ASSERT_TRUE(unit.isConvertible(meter));
    ASSERT_FALSE(kilogram.isConvertible(unit));

    AffineUnit unit2{kilogram, 3, 5};
    ASSERT_FALSE(unit2.isConvertible(unit));
    ASSERT_FALSE(unit.isConvertible(unit2));
}

/// Tests conversion
TEST_F(AffineUnitTest, Convert)
{
    AffineUnit unit{meter, 3, 5};
    ASSERT_EQ(5, unit.convert(0));
    ASSERT_EQ(8, unit.convert(1));
}

#if 0

/// Tests division
TEST_F(AffineUnitTest, Division)
{
    AffineUnit unit1{meter, 4, 1};
    auto unit2 = unit1.divideBy(2);
    ASSERT_EQ(1, unit2.convert(0));
    ASSERT_EQ(3, unit2.convert(1));
}

/// Tests raising to a power
TEST_F(AffineUnitTest, Power)
{
    ASSERT_THROW(AffineUnit(meter, 2, 1).pow(2), std::domain_error);
    AffineUnit unit1{meter, 2, 0};
    auto unit2 = unit1.pow(2);
    ASSERT_EQ(0, unit2.convert(0));
    ASSERT_EQ(4, unit2.convert(1));
}

/// Tests taking a root
TEST_F(AffineUnitTest, Root)
{
    EXPECT_THROW(AffineUnit(meter, 2, 0).root(0), std::invalid_argument);
    EXPECT_THROW(AffineUnit(meter, 2, 0).root(-1), std::invalid_argument);
    AffineUnit unit1{meter, 2, 0};
    auto unit2 = unit1.pow(2);
    auto unit3 = unit2.root(2);
    EXPECT_EQ(0, unit3.convert(0));
    EXPECT_EQ(2, unit3.convert(1));
}
#endif

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
