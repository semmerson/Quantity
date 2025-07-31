/**
 * This file tests class AffineScale.
 */

#include "AffineScale.h"
#include "gtest/gtest.h"

#include <stdexcept>

namespace {

using namespace quantity;
using namespace std;

/// The fixture for testing class `AffineScale`
class AffineScaleTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    AffineScaleTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~AffineScaleTest()
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

/// Tests construction
TEST_F(AffineScaleTest, Construction)
{
    AffineScale scale1{3, 0};
    EXPECT_FALSE(scale1.isOffset());

    AffineScale scale2{3, 5};
    EXPECT_TRUE(scale2.isOffset());
}

/// Tests conversion
TEST_F(AffineScaleTest, Conversion)
{
    AffineScale scale{3, 5};
    ASSERT_EQ(5, scale.convert(0));
    ASSERT_EQ(8, scale.convert(1));
}

/// Tests multiplication
TEST_F(AffineScaleTest, Multiplication)
{
    AffineScale scale1{2, 1};
    auto scale2 = scale1.multiply(3);
    ASSERT_EQ(1, scale2.convert(0));
    ASSERT_EQ(7, scale2.convert(1));
}

/// Tests division
TEST_F(AffineScaleTest, Division)
{
    AffineScale scale1{4, 1};
    auto scale2 = scale1.divide(2);
    ASSERT_EQ(1, scale2.convert(0));
    ASSERT_EQ(3, scale2.convert(1));
}

/// Tests raising to a power
TEST_F(AffineScaleTest, Power)
{
    ASSERT_THROW(AffineScale(2, 1).pow(2), std::domain_error);
    AffineScale scale1{2, 0};
    auto scale2 = scale1.pow(2);
    ASSERT_EQ(0, scale2.convert(0));
    ASSERT_EQ(4, scale2.convert(1));
}

/// Tests taking the root
TEST_F(AffineScaleTest, Root)
{
    EXPECT_THROW(AffineScale(2, 0).root(0), std::invalid_argument);
    EXPECT_THROW(AffineScale(2, 0).root(-1), std::invalid_argument);
    AffineScale scale1{2, 0};
    auto scale2 = scale1.pow(2);
    auto scale3 = scale2.root(2);
    EXPECT_EQ(0, scale3.convert(0));
    EXPECT_EQ(2, scale3.convert(1));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
