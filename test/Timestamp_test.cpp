/**
 * This file tests class Timestamp.
 *
 *        File: Timestamp_test.cpp
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
#include "Timestamp.h"

#include "BaseInfo.h"
#include "Dimension.h"
#include "Unit.h"

#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using namespace quantity;

/// The fixture for testing class `Timestamp`
class TimestampTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    TimestampTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~TimestampTest()
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
TEST_F(TimestampTest, Construction)
{
    // Bad months
    EXPECT_THROW(Timestamp::getGregorian(1970, 0, 1, 0, 0, 0, 0).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 13, 1, 0, 0, 0, 0).to_string(),
            std::invalid_argument);

    // Bad days
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, -1, 0, 0, 0, 0).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 32, 0, 0, 0, 0).to_string(),
            std::invalid_argument);

    // Bad hours
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, -1, 0, 0, 0).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 24, 0, 0, 0).to_string(),
            std::invalid_argument);

    // Bad minutes
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, -1, 0, 0).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, 60, 0, 0).to_string(),
            std::invalid_argument);

    // Bad seconds
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, 0, -1, 0).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, 0, 62, 0).to_string(),
            std::invalid_argument);

    // Bad timezones
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, 0, -1, -721).to_string(),
            std::invalid_argument);
    EXPECT_THROW(Timestamp::getGregorian(1970, 1, 1, 0, 0, 62, 721).to_string(),
            std::invalid_argument);

    // Zulu timezones
    EXPECT_EQ("1970-01-01T00:00:00.000000Z",
            Timestamp::getGregorian(1970, 1, 1, 0, 0, 0).to_string());
    EXPECT_EQ("1970-01-01T00:00:00.000000Z",
            Timestamp::getGregorian(1970, 1, 1, 0, 0, 0, 0).to_string());

    // Non-Zulu timezones
    EXPECT_EQ("1970-01-01T00:00:00.000000-6:00",
            Timestamp::getGregorian(1970, 1, 1, 0, 0, 0, -360).to_string());
    EXPECT_EQ("1970-01-01T00:00:00.000000+6:00",
            Timestamp::getGregorian(1970, 1, 1, 0, 0, 0, 360).to_string());
}

// Tests isConvertible()
TEST_F(TimestampTest, Convertability)
{
    const auto timestamp = Timestamp::getGregorian(1970, 1, 1, 0, 0, 0, 0);
    // Not implemented yet
    EXPECT_THROW(timestamp.isConvertible(timestamp), std::logic_error);
}

// Tests subtract()
TEST_F(TimestampTest, Subtraction)
{
    Dimension time{"Second", "T"};
    const auto second = Unit::get(BaseInfo(time, "second", "s"));

    const auto timestamp = Timestamp::getGregorian(1970, 1, 1, 0, 0, 0, 0);
    // Not implemented yet
    EXPECT_THROW(timestamp.subtract(timestamp, second), std::logic_error);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
