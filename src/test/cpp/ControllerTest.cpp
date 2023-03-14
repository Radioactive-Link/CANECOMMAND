#include <gtest/gtest.h>

#include "RobotContainer.hpp"

class ControllerTest : public testing::Test {
 protected:
  RobotContainer container;
};

TEST_F(ControllerTest, DpadAnglesWork) {
  /**
   * TODO: Write a unit test to make sure that Dpad angles can actually be read.
   */
  EXPECT_EQ(true,true);
}