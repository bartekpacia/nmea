#include "gtest/gtest.h"

#include <iostream>
#include "nmea/nmea.h"

TEST(SmokeTest, ReturnsHelloWorld) {
  EXPECT_EQ(nmea::nmea_stuff(), "nmea_stuff");
}
