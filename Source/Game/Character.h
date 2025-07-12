// Character.h
#pragma once
#ifdef WIN32 || _WINDOWS
    #ifdef _EXPORTING
        #define GAME_API    __declspec(dllexport)
    #elif _IMPORTING
        #define GAME_API    __declspec(dllimport)
    #else
        #define GAME_API
    #endif
#else
    #define GAME_API __attribute__ ((visibility ("default")))
#endif



class Weapon;

class GAME_API Character
{
public:
    Character(const char* name);
    ~Character();

    const char* name() const;

    int health() const;
    bool dead() const;
    bool attack(Character& target);
    void takeDamage(int damage);

private:
    const char* m_name;
    Weapon* m_weapon;
    int m_health{ 100 };
};

