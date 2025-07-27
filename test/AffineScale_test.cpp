/**
 * This file tests class AffineScale.
 */

#include "AffineScale.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;
using namespace std;

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

/// Tests construction
TEST_F(DimensionTest, Construction)
{
    AffineScale scale1{2, 0};
    EXPECT_EQ(0, scale1.convert(0));
    EXPECT_EQ(2, scale1.convert(1));

    AffineScale scale2{3, 5};
    ASSERT_EQ(5, scale2.convert(0));
    ASSERT_EQ(8, scale2.convert(1));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
