// main.cpp

#include "Game/Character.h"
#include <iostream>
#include "thread"

int main() {

    #ifdef SKIP_GAME
    std::cout << "================================" << std::endl;
        return 0;
    #endif
    
    Character hero1("Durden");
    Character hero2("Angel Face");

    Character* attacker = &hero1;
    Character* defender = &hero2;

    int roundNum = 1;
    bool lastFireStatus = true;

    while (true)
    {
        std::cout << "============= Round: " << roundNum++ << " =============" << std::endl;
        const bool fired = attacker->attack(*defender);
        if (lastFireStatus == fired && !fired)
        {
            std::cout << std::endl;
            std::cout << "============= Game Over =============" << std::endl;
            std::cout << " Friendship wins! " << std::endl;
            break;
        }

        lastFireStatus = fired;

        if (defender->dead())
        {
            std::cout << std::endl;
            std::cout << "============= Game Over =============" << std::endl;
            std::cout << defender->name() << " is dead " << std::endl;
            std::cout << attacker->name() << " wins " << std::endl;
            break;
        }
        else
        {
            std::swap(attacker, defender);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cin.get();

    return 0;
}
