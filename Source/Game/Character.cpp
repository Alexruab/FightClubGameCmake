// Character.cpp
#include "Character.h"
#include "Weapon.h"
#include "Utils/Math.h"
#include <iostream>

Character::Character(const char* name) : m_name(name)
{
    const int bulletsCount = LifeExe::random(1, 10);
    m_weapon = new Weapon(bulletsCount);
}

Character::~Character()
{
    delete m_weapon;
    m_weapon = nullptr;
}

int Character::health() const
{
    return m_health;
}

bool Character::dead() const
{
    return m_health == 0;
}

bool Character::attack(Character& target)
{
    const bool fire = m_weapon->fire();
    if (fire) {
        const int damage = m_weapon->damage();
        std::cout << m_name << "is attacking, with damage: " << damage << std::endl;
        target.takeDamage(damage);
        return true;
    }
    else
    {
        std::cout << m_name << "has no more bullets. shit... bad day..." << std::endl;
    }

    return fire;
}

void Character::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }

    std::cout << m_name << "was attacked, current health: " << m_health << std::endl;
}

const char* Character::name() const
{
    return m_name;
}
