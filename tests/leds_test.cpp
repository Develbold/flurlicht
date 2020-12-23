#include "gtest/gtest.h"
#include "leds.h"

TEST(leds, getAnimationRunning)
{
    LEDs buffer(18,240,SK6812_STRIP);

    EXPECT_EQ (buffer.getAnimationRunning(),  false);
}
