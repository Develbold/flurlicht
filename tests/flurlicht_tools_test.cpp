#include "gtest/gtest.h"
#include "flurlicht_tools.h"

TEST(FlurlichtTools, test) {
    //arrange
    //act
    //assert
    EXPECT_EQ (FLURLICHT_TOOLS::test (0),  0);
    EXPECT_EQ (FLURLICHT_TOOLS::test (10), 10);
    EXPECT_EQ (FLURLICHT_TOOLS::test (-10), -10);
}

TEST(FlurlichtTools, checkRenderTimeValid)
{
    auto buffer = FLURLICHT_TOOLS::getTime();

    EXPECT_EQ (FLURLICHT_TOOLS::checkRenderTimeValid (buffer, 1000),  false);
    FLURLICHT_TOOLS::sleepPeriod(1000);
    EXPECT_EQ (FLURLICHT_TOOLS::checkRenderTimeValid (buffer, 1),  true);
}
