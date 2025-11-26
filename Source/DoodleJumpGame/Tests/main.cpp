#include "gtest/gtest.h"
#include "Types.h"
#include "Player.h"
#include "PlatformManager.h"


TEST(PlayerTest, JumpVelocityShouldBeSetCorrectly)
{
    const ScreenSize screenSize{500, 700};
    Player::Config config((40.0f, 40.0f, 300.0f, 100.5f, -700.0f, 50.0f));
    Player player(screenSize, config);
    player.jump();

    ASSERT_EQ(player.velocity(), -700.0f);
}

TEST(PlayerTest, PlayerShouldFallUnderTheGravity)
{
    const ScreenSize screenSize{500, 700};
    Player::Config config((40.0f, 40.0f, 300.0f, 100.5f, -700.0f, 50.0f));
    Player player(screenSize, config);

    player.update(1.0f);

    const float initialY = screenSize.height * 0.5 - config.initialOffsetY;
    ASSERT_EQ(player.y(), initialY + config.gravity);
}

TEST(PlatformManagerTest, PlatformPositionShouldBeSetCorrectly)
{
    const ScreenSize screenSize{500, 700};
    PlatformManager platformManager(screenSize);

    const float platformCount = 10;
    const auto platforms = platformManager.platforms();
    ASSERT_EQ(platforms.size(), platformCount);

    for (int i = 0; i < platforms.size(); ++i)
    {
        const float expectedX = 0.0f;
        const float expectedY = 0.0f;

        EXPECT_NEAR(platforms[i].x, expectedX, 0.001f);
        EXPECT_NEAR(platforms[i].y, expectedY, 0.001f);
    }

}