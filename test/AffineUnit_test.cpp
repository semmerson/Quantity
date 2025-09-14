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
    Dimension temperature{"Temperature", "Θ"};
    Dimension time{"Time", "T"};
    Unit::Pimpl meter{Unit::get(BaseInfo(length, "meter", "m"))};
    Unit::Pimpl kilogram{Unit::get(BaseInfo(mass, "kilogram", "kg"))};
    Unit::Pimpl kelvin{Unit::get(BaseInfo(temperature, "kelvin", "°K"))};
    Unit::Pimpl second{Unit::get(BaseInfo(time, "second", "s"))};
};

/// Tests construction
TEST_F(AffineUnitTest, Construction)
{
    EXPECT_THROW(Unit::get(meter, 0, 1), std::logic_error);

    const auto unit1 = Unit::get(meter, 3, 1);
    EXPECT_FALSE(unit1->type() == Unit::Type::BASE);
    EXPECT_TRUE(unit1->isOffset());
    EXPECT_FALSE(unit1->isDimensionless());
}

/// Tests Unit::isConvertible()
TEST_F(AffineUnitTest, IsConvertible)
{
    const auto unit = Unit::get(meter, 3, 5);
    ASSERT_TRUE(meter->isConvertible(unit));
    ASSERT_TRUE(unit->isConvertible(meter));
    ASSERT_FALSE(kilogram->isConvertible(unit));

    const auto unit2 = Unit::get(kilogram, 3, 5);
    ASSERT_FALSE(unit2->isConvertible(unit));
    ASSERT_FALSE(unit->isConvertible(unit2));
}

/// Tests conversion
TEST_F(AffineUnitTest, Convert)
{
    const auto unit = Unit::get(meter, 3, 5);
    ASSERT_EQ(1, unit->getConverterTo(unit).convert(1));
    ASSERT_EQ(0, unit->getConverterTo(meter).convert(5));
    ASSERT_EQ(5, meter->getConverterTo(unit).convert(0));
    ASSERT_EQ(1, unit->getConverterTo(meter).convert(8));
    ASSERT_EQ(8, meter->getConverterTo(unit).convert(1));

    const auto rankine = Unit::get(kelvin, 1.8, 0.0);
    EXPECT_EQ("1.800000*°K", rankine->to_string());
    EXPECT_LE(273.14, rankine->getConverterTo(kelvin).convert(491.67));
    EXPECT_GE(273.16, rankine->getConverterTo(kelvin).convert(491.67));
    EXPECT_LE(491.66, kelvin->getConverterTo(rankine).convert(273.15));
    EXPECT_GE(491.68, kelvin->getConverterTo(rankine).convert(273.15));

    const auto celsius = Unit::get(kelvin, 1, -273.15);
    EXPECT_EQ("°K - 273.150000", celsius->to_string());
    EXPECT_EQ(0, celsius->getConverterTo(kelvin).convert(-273.15));
    EXPECT_EQ(-273.15, kelvin->getConverterTo(celsius).convert(0));

    const auto fahrenheit1 = Unit::get(rankine, 1.0, -459.67);
    EXPECT_EQ("1.800000*°K - 459.670000", fahrenheit1->to_string());
    EXPECT_LE(491.66, fahrenheit1->getConverterTo(rankine).convert(32));
    EXPECT_GE(491.68, fahrenheit1->getConverterTo(rankine).convert(32));
    EXPECT_LE(31.99, rankine->getConverterTo(fahrenheit1).convert(491.67));
    EXPECT_GE(32.01, rankine->getConverterTo(fahrenheit1).convert(491.67));

    const auto fahrenheit2 = Unit::get(kelvin, 1.8, -459.67);
    EXPECT_EQ("1.800000*°K - 459.670000", fahrenheit2->to_string());
    EXPECT_LE(273.14, fahrenheit2->getConverterTo(kelvin).convert(32));
    EXPECT_GE(273.16, fahrenheit2->getConverterTo(kelvin).convert(32));
    EXPECT_LE(31.99, kelvin->getConverterTo(fahrenheit2).convert(273.15));
    EXPECT_GE(32.01, kelvin->getConverterTo(fahrenheit2).convert(273.15));

    const auto fahrenheit3 = Unit::get(celsius, 1.8, 32);
    EXPECT_EQ("1.800000*(°K - 273.150000) + 32.000000", fahrenheit3->to_string());
    EXPECT_LE(-0.01, fahrenheit3->getConverterTo(celsius).convert(32));
    EXPECT_GE(+0.01, fahrenheit3->getConverterTo(celsius).convert(32));
    EXPECT_LE(31.99, celsius->getConverterTo(fahrenheit3).convert(0));
    EXPECT_GE(32.01, celsius->getConverterTo(fahrenheit3).convert(0));
}

/// Tests Unit::Multiply()
TEST_F(AffineUnitTest, Multiplication)
{
    const auto unit1 = Unit::get(meter, 3, 1);
    EXPECT_THROW(unit1->multiply(meter), logic_error);
    EXPECT_THROW(meter->multiply(unit1), logic_error);

    const auto km = Unit::get(meter, 1.0/1000.0, 0);
    EXPECT_EQ("0.001000*m", km->to_string());
    EXPECT_LE(1999, km->convertToCanonical(2));
    EXPECT_GE(2001, km->convertToCanonical(2));

    EXPECT_EQ("0.001000*m·°K", km->multiply(kelvin)->to_string());
}

/// Tests Unit::pow()
TEST_F(AffineUnitTest, Exponentiation)
{
    const auto unit1 = Unit::get(meter, 3, 1);
    EXPECT_THROW(unit1->pow(Exponent(2)), logic_error);

    const auto km = Unit::get(meter, 1.0/1000.0, 0);
    const auto km2 = km->pow(2);
    EXPECT_EQ("0.000001*m^2", km2->to_string());
    EXPECT_LE(1999999, km2->convertToCanonical(2));
    EXPECT_GE(2000001, km2->convertToCanonical(2));
}

/// Tests Unit::divide()
TEST_F(AffineUnitTest, Division)
{
    const auto km = Unit::get(meter, 1.0/1000.0, 0);
    const auto hr = Unit::get(second, 1.0/3600.0, 0);
    const auto kmPerHr = km->divideBy(hr);
    EXPECT_EQ("3.600000*m·s^-1", kmPerHr->to_string());
    EXPECT_LE(27.76, kmPerHr->convertToCanonical(100));
    EXPECT_GE(27.78, kmPerHr->convertToCanonical(100));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
