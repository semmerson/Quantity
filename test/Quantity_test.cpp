/**
 * This file tests class Quantity
 *
 *        File: Quantity_test.cpp
 *  Created on: Jul 26, 2025
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

#include "Quantity.h"

#include <gtest/gtest.h>
#include <iostream>

namespace {

using namespace quantity;

/// The fixture for testing class `Quantity`
class QuantityTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    QuantityTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~QuantityTest()
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
};

// Tests construction
TEST_F(QuantityTest, Construction)
{
    Quantity meter{“Length”, “meter”, “m”};
    EXPECT_THROW(Quantity(“Length”, “meter”, “m”), invalid_argument);

    Quantity second(“Time”, “second”, “s”};
    auto metersPerSecond = meter.divide(second);
}

// Tests temperature
TEST_F(QuantityTest, Temperature)
{
    Quantity kelvin{“Temperature”, “kelvin”, “°K”};
    Quantity celsius{“degrees celsius”, °C, kelvin, AffineScale(1, 273.15)};
    assert(celsius.isOffset());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
