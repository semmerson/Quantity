/**
 * This file tests class RefLogUnit.
 *
 *        File: RefLogUnit_test.cpp
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
#include "Dimensionality.h"
#include "RefLogUnit.h"

#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace quantity;

/// The fixture for testing class `RefLogUnit`
class RefLogUnitTest : public ::testing::Test
{
protected:
    Dimensionality length;

    // You can remove any or all of the following functions if its body
    // is empty.

    RefLogUnitTest()
        : length(Dimensionality::get("Length", "L"))
    {
        // You can do set-up work for each test here.
    }

    virtual ~RefLogUnitTest()
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
    Unit::Pimpl meter{Unit::get(BaseInfo(length, "meter", "m"))};
};

// Tests construction
TEST_F(RefLogUnitTest, Construction)
{
    const auto affineMeter = Unit::get(meter, 3, 5);
    EXPECT_THROW(Unit::get(Unit::BaseEnum::E, affineMeter), std::logic_error);

    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    const auto lnMeter = Unit::get(Unit::BaseEnum::E, meter);
    const auto lgMeter = Unit::get(Unit::BaseEnum::TEN, meter);
}

// Tests string representation
TEST_F(RefLogUnitTest, StringRepresentation)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_EQ("ln(re 1000.000000 m)", Unit::get(Unit::BaseEnum::E, affineMeter)->to_string());
}

// Tests type
TEST_F(RefLogUnitTest, Type)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_EQ(Unit::Type::REF_LOG, Unit::get(Unit::BaseEnum::E, affineMeter)->type());
}

// Tests offset
TEST_F(RefLogUnitTest, Offset)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_FALSE(Unit::get(Unit::BaseEnum::E, affineMeter)->isOffset());
}

// Tests dimensionless
TEST_F(RefLogUnitTest, Dimensionless)
{
    const auto affineMeter = Unit::get(meter, 1000, 0);
    EXPECT_TRUE(Unit::get(Unit::BaseEnum::E, affineMeter)->isDimensionless());
}

// Tests multiplication
TEST_F(RefLogUnitTest, Multiplication)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    const auto lgMeter = Unit::get(Unit::BaseEnum::TEN, meter);
    EXPECT_THROW(lbMeter->multiply(lbMeter), std::logic_error);
    EXPECT_THROW(lbMeter->multiply(lgMeter), std::logic_error);
}

// Tests exponentiation
TEST_F(RefLogUnitTest, Exponentiation)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    EXPECT_THROW(lbMeter->pow(2), std::logic_error);
}

// Tests conversion
TEST_F(RefLogUnitTest, Conversion)
{
    const auto lbMeter = Unit::get(Unit::BaseEnum::TWO, meter);
    const auto lgMeter = Unit::get(Unit::BaseEnum::TEN, meter);
    const auto lgMToLbM = lgMeter->getConverterTo(lbMeter);
    EXPECT_LE(3.32192, lgMToLbM(1));
    EXPECT_GE(3.32194, lgMToLbM(1));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
