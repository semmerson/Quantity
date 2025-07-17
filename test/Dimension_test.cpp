/**
 * This file tests class `Dimension`.
 *
 *       File: Dimension_test.cpp
 * Created On: 2025-07-13
 *     Author: Steven R. Emmerson
 *
 *    Copyright 2025 Steven R. Emmerson, All rights reserved
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
#include "Dimension.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing class `Dimension`
class DimensionTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    DimensionTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~DimensionTest()
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
TEST_F(DimensionTest, Construction)
{
    auto length{Dimension::create("length")};
    EXPECT_THROW(Dimension::create(""), invalid_argument);
    EXPECT_THROW(Dimension::create("length"), invalid_argument);
}

// Tests delayed reveal
/*
TEST_F(DimensionTest, DelayedReveal)
{
    Dimension<int, std::chrono::milliseconds> dq{};
    const int value = 1;
    dq.push(value, 100);
    EXPECT_FALSE(dq.empty());
    EXPECT_FALSE(dq.ready());
    EXPECT_EQ(value, dq.pop());
}
*/

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
