#pragma once
#include <raylib.h>
#include "Types.h"

class Player
{
public:
    Player(const ScreenSize& screenSize);
    void update(float deltaTime);
    
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void setY(float y);

    Rectangle aabb() const;
    Rectangle sweepAABB() const;
    float y() const;
    float velocity() const;
    
private:
    const ScreenSize c_screenSize;
    float m_x;
    float m_y;
    float m_previousY;
    float m_velocityY;
};