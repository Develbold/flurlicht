#include "gtest/gtest.h"
#include "flurlicht_tools.h"

TEST(blaTest, test1) {
    //arrange
    //act
    //assert
    EXPECT_EQ (FLURLICHT_TOOLS::test (0),  0);
    EXPECT_EQ (FLURLICHT_TOOLS::test (10), 10);
    EXPECT_EQ (FLURLICHT_TOOLS::test (-10), -10);
}
