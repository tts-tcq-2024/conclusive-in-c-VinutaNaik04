#include <gtest/gtest.h>
#include "typewise-alert.h"


TEST(InferBreachTest, TemperatureTooLow) {
  EXPECT_EQ(inferBreach(-1, 0, 40), TOO_LOW);
  EXPECT_EQ(inferBreach(5, 9, 40), TOO_LOW);
}

