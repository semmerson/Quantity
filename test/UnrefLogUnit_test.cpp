/**
 * This file tests class UnrefLogUnit.
 *
 *        File: UnrefLogUnit_test.cpp
 *  Created on: Jul 19, 2025
 *      Author: Steven R. Emmerson
 *
 * Copyright 2025 Steven R. Emmerson. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "BaseInfo.h"
#include "Dimension.h"
#include "Dimensionality.h"
#include "Exponent.h"
#include "UnrefLogUnit.h"

#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace quantity;

/// The fixture for testing class `UnrefLogUnit`
class UnrefLogUnitTest : public ::testing::Test
{
protected:
    Dimensionality length;
    Dimensionality time;
    Dimensionality temp;

    // You can remove any or all of the following functions if its body
    // is empty.

    UnrefLogUnitTest()
        : length(Dimensionality::get("Length", "L"))
        , time(Dimensionality::get("Time", "T"))
        , temp(Dimensionality::get("Temperature", "Θ"))
    {
        // You can do set-up work for each test here.
    }

    virtual ~UnrefLogUnitTest()
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
    BaseInfo       meterInfo{length, "meter", "m"};
    Unit::Pimpl    meter = Unit::get(meterInfo);

    BaseInfo       timeInfo{time, "second", "s"};
    Unit::Pimpl    second = Unit::get(timeInfo);

    BaseInfo       tempInfo{temp, "kelvin", "°K"};
    Unit::Pimpl    kelvin = Unit::get(tempInfo);

    Unit::Pimpl    mPerS = meter->divideBy(second);
};

// Tests construction
TEST_F(UnrefLogUnitTest, Construction)
{
    const auto lbLength  = Unit::get(Unit::BaseEnum::TWO, length);
    const auto lnLength  = Unit::get(Unit::BaseEnum::E,   length);
    const auto lgLength  = Unit::get(Unit::BaseEnum::TEN, length);

    const auto lnMPerS   = Unit::get(Unit::BaseEnum::E, length.divideBy(time));

    // A scaled (but not offset) unit can be the basis for an unreferenced logarithmic unit
    const auto rankine   = Unit::get(kelvin, 9.0/5.0, 0.0);
    const auto lnRankine = Unit::get(Unit::BaseEnum::E, rankine);
}

// Tests string representation
TEST_F(UnrefLogUnitTest, StringRepresentation)
{
    const auto noDim = Unit::get(Unit::BaseEnum::E, Dimensionality());
    EXPECT_EQ("ln(^0)", noDim->to_string());

    const auto lbLength = Unit::get(Unit::BaseEnum::TWO, length);
    EXPECT_EQ("lb(L^0)", lbLength->to_string());

    const auto lnLength = Unit::get(Unit::BaseEnum::E, length);
    EXPECT_EQ("ln(L^0)", lnLength->to_string());

    const auto lgLength = Unit::get(Unit::BaseEnum::TEN, length);
    EXPECT_EQ("lg(L^0)", lgLength->to_string());

    const auto lnMPerS = Unit::get(Unit::BaseEnum::E, length.divideBy(time));
    EXPECT_EQ("ln((L·T^-1)^0)", lnMPerS->to_string());
}

#if 0
// Tests type
TEST_F(UnrefLogUnitTest, Type)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_EQ(Unit::Type::REF_LOG, Unit::get(Unit::BaseEnum::E, affineMeter)->type());
}

// Tests offset
TEST_F(UnrefLogUnitTest, Offset)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_FALSE(Unit::get(Unit::BaseEnum::E, affineMeter)->isOffset());
}

// Tests dimensionless
TEST_F(UnrefLogUnitTest, Dimensionless)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_TRUE(Unit::get(Unit::BaseEnum::E, affineMeter)->isDimensionless());
}

// Tests multiplication
TEST_F(UnrefLogUnitTest, Multiplication)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    const auto lgMeter = Unit::get(Unit::BaseEnum::TEN, meter);
    EXPECT_THROW(lbMeter->multiply(lbMeter), std::logic_error);
    EXPECT_THROW(lbMeter->multiply(lgMeter), std::logic_error);
}

// Tests exponentiation
TEST_F(UnrefLogUnitTest, Exponentiation)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    EXPECT_THROW(lbMeter->pow(2), std::logic_error);
}

// Tests conversion
TEST_F(UnrefLogUnitTest, Conversion)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    const auto lgMeter = Unit::get(Unit::BaseEnum::TEN, meter);
    const auto lgMToLbM = lgMeter->getConverterTo(lbMeter);
    EXPECT_LE(3.32192, lgMToLbM(1));
    EXPECT_GE(3.32194, lgMToLbM(1));
}
#endif

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
