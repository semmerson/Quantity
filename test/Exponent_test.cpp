/**
 * This file tests class Exponent.
 */

#include "Exponent.h"

#include "gtest/gtest.h"

namespace {

using namespace quantity;

/// The fixture for testing the class
class ExponentTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    ExponentTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~ExponentTest()
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
TEST_F(ExponentTest, Construction)
{
    EXPECT_TRUE(Exponent().isOne());
    EXPECT_THROW(Exponent(1, 0).to_string(), std::invalid_argument);
    EXPECT_EQ("1", Exponent().to_string());
    EXPECT_EQ("1", Exponent(1).to_string());
    EXPECT_EQ("2", Exponent(2).to_string());
    EXPECT_EQ("-1", Exponent(-1).to_string());
    EXPECT_EQ("(-2/3)", Exponent(2, -3).to_string());
}

// Tests comparison
TEST_F(ExponentTest, Comparison)
{
    EXPECT_EQ(0, Exponent(1).compare(Exponent(1)));
    EXPECT_EQ(0, Exponent(-1).compare(Exponent(-1)));

    EXPECT_EQ(-1, Exponent(1).compare(Exponent(-1)));
    EXPECT_EQ(1, Exponent(-1).compare(Exponent(1)));

    EXPECT_EQ(0, Exponent(2, 3).compare(Exponent(2, 3)));

    EXPECT_EQ(-1, Exponent(2, 3).compare(Exponent(3, 4)));
    EXPECT_EQ(1, Exponent(3, 4).compare(Exponent(2, 3)));

    EXPECT_EQ(1, Exponent(-2, 3).compare(Exponent(3, 4)));
    EXPECT_EQ(-1, Exponent(3, 4).compare(Exponent(-2, 3)));

    EXPECT_EQ(-1, Exponent(-2, 3).compare(Exponent(-3, 4)));
    EXPECT_EQ(1, Exponent(-3, 4).compare(Exponent(-2, 3)));
}

// Tests multiplication
TEST_F(ExponentTest, Multiplication)
{
    EXPECT_EQ("2", Exponent().multiply(Exponent(2)).to_string());
    EXPECT_EQ("-1", Exponent().multiply(Exponent(-1)).to_string());
    EXPECT_EQ("(-2/3)", Exponent().multiply(Exponent(2, -3)).to_string());
    EXPECT_EQ("0", Exponent().multiply(Exponent(0, -3)).to_string());
}

// Tests addition
TEST_F(ExponentTest, Addition)
{
    EXPECT_EQ("3", Exponent().add(Exponent(2)).to_string());
    EXPECT_EQ("0", Exponent().add(Exponent(-1)).to_string());
    EXPECT_EQ("(1/3)", Exponent().add(Exponent(2, -3)).to_string());
    EXPECT_EQ("(-1/3)", Exponent(-1).add(Exponent(2, 3)).to_string());
    EXPECT_EQ("1", Exponent().add(Exponent(0, -3)).to_string());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
