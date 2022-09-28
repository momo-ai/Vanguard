#include <gtest/gtest.h>
#include "unittests_config.h" 

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(vanguardtest, BasicAssertions) {
  ASSERT_STRNE(UNITTESTS_SRC, ""); 
}