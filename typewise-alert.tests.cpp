#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
TEST(InferBreachTest, TemperatureTooLow) {
  EXPECT_EQ(inferBreach(-1, 0, 35), TOO_LOW);
  EXPECT_EQ(inferBreach(5, 10, 35), TOO_LOW);
}
}
