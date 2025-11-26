#pragma once
#include <raylib.h>
#include "Types.h"

class Player
{
public:
    struct Config
    {
        const float width{40.0f};
        const float height{40.0f};
        const float speed{300.0f};
        const float gravity{100.5f};
        const float jumpVelocity{-700.0f};
        const float initialOffsetY{50.0f};
    };

    Player(const ScreenSize& screenSize, const Config& config = {});

    


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
    const Config c_config;
    float m_x;
    float m_y;
    float m_previousY;
    float m_velocityY;
};