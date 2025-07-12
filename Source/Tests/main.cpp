#include <cassert>
#include "Utils/Math.h"
#include "Game/Character.h"

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
}