/**
 * This file tests class AffineUnit.
 */

#include "BaseInfo.h"
#include "AffineUnit.h"
#include "Dimension.h"
#include "Unit.h"

#include <gtest/gtest.h>
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
    const Unit::Pimpl meter{Unit::get(BaseInfo("meter", "m"))};
    const Unit::Pimpl kilogram{Unit::get(BaseInfo("kilogram", "kg"))};
    const Unit::Pimpl kelvin{Unit::get(BaseInfo("kelvin", "°K"))};
};

/// Tests construction
TEST_F(AffineUnitTest, Construction)
{
    EXPECT_THROW(Unit::get(meter, 0, 1), std::logic_error);

    Unit::Pimpl unit1 = Unit::get(meter, 3, 1);
    EXPECT_FALSE(unit1->type() == Unit::Type::base);
    EXPECT_TRUE(unit1->isOffset());
    EXPECT_FALSE(unit1->isDimensionless());
}

/// Tests Unit::isConvertible()
TEST_F(AffineUnitTest, IsConvertible)
{
    Unit::Pimpl unit = Unit::get(meter, 3, 5);
    ASSERT_TRUE(meter->isConvertible(unit));
    ASSERT_TRUE(unit->isConvertible(meter));
    ASSERT_FALSE(kilogram->isConvertible(unit));

    Unit::Pimpl unit2 = Unit::get(kilogram, 3, 5);
    ASSERT_FALSE(unit2->isConvertible(unit));
    ASSERT_FALSE(unit->isConvertible(unit2));
}

/// Tests conversion
TEST_F(AffineUnitTest, Convert)
{
    Unit::Pimpl unit = Unit::get(meter, 3, 5);
    ASSERT_EQ(5, unit->convertTo(0));
    ASSERT_EQ(8, unit->convertTo(1));

    Unit::Pimpl celsius = Unit::get(kelvin, 1, -273.15);
    EXPECT_EQ("°K - 273.150000", celsius->to_string());
    EXPECT_EQ(-273.15, celsius->convertTo(0));

    Unit::Pimpl rankine = Unit::get(kelvin, 1.8, 0.0);
    EXPECT_EQ("1.800000*°K", rankine->to_string());
    EXPECT_LE(491.66, rankine->convertTo(273.15));
    EXPECT_GE(491.68+.001, rankine->convertTo(273.15));

    Unit::Pimpl fahrenheit1 = Unit::get(rankine, 1.0, -459.67);
    EXPECT_EQ("1.800000*°K - 459.670000", fahrenheit1->to_string());
    EXPECT_LE(31.99, fahrenheit1->convertTo(491.67));
    EXPECT_GE(32.01, fahrenheit1->convertTo(491.67));

    Unit::Pimpl fahrenheit2 = Unit::get(celsius, 1.8, 32);
    EXPECT_EQ("1.800000*(°K - 273.150000) + 32.000000", fahrenheit2->to_string());
    EXPECT_LE(31.99, fahrenheit2->convertTo(0));
    EXPECT_GE(32.01, fahrenheit2->convertTo(0));
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
