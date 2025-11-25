#include "Utils/Math.h"
#include "Game/Character.h"   //FightClubGame/
#include <gtest/gtest.h>


TEST(Math, MaxShouldBeCalculatedCorrectly)
{
    using namespace LifeExe;
    ASSERT_TRUE(max(3, 0) == 3);
    ASSERT_TRUE(max(-3, 0) == 0);
}

TEST(Character, CharacterCanBeKilled)
{
    Character hero("Pacman");
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10);
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10000);
    ASSERT_TRUE(hero.dead());
}

/*
int main()
{
    using namespace LifeExe;
    assert(max(3, 0) == 3);
    assert(max(-3, 0) == 0);

    Character hero("Sonyk");

    assert(!hero.dead());
    hero.takeDamage(100);
    assert(hero.dead());
    return 0;
}*/