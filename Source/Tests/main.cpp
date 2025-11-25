#include <cassert>
#include "Utils/Math.h"
#include "Game/Character.h"
#include <gtest/gtest.h>

using namespace LifeExe;

TEST(Math, Max)
{
    
    ASSERT_TRUE(max(3, 0) == 3);
    ASSERT_TRUE(max(-3, 0) == 0);
    
}

TEST(Character, Death)
{
    Character hero("Sonyk");
    ASSERT_TRUE(!hero.dead());
    hero.takeDamage(100);
    ASSERT_TRUE(hero.dead());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    const auto status = RUN_ALL_TESTS();
    std::cin.get();
    return status;
}

//int main()
//{
//    using namespace LifeExe;
//    assert(max(3, 0) == 3);
//    assert(max(-3, 0) == 0);
//
//    Character hero("Sonyk");
//
//    assert(!hero.dead());
//    hero.takeDamage(100);
//    assert(hero.dead());
//    return 0;
//}
