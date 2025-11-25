#include "Player.h"
#include <algorithm>

namespace
{
constexpr float c_width{40.0f};
constexpr float c_height{40.0f};
constexpr float c_speed{300.0f};
constexpr float c_gravity{100.5f};
constexpr float c_jumpVelocity{-700.0f};
}

Player::Player(const ScreenSize& screenSize) : c_screenSize{screenSize}, m_velocityY{0.0f}
{
    m_x = (screenSize.width - c_width) * 0.5f;
    m_y = screenSize.height * 0.5f - 50.f;
    m_previousY = m_y;
}

void Player::update(float deltaTime)
{
    m_previousY = m_y;
    m_velocityY += c_gravity * deltaTime;
    m_y +=m_velocityY * deltaTime;

    const float PlayerCenterX = m_x + c_width * 0.5f;
    if(PlayerCenterX >= c_screenSize.width)
    {
        m_x = 0.0f;
    } 
    else if (PlayerCenterX <= 0.0f)
    {
        m_x = c_screenSize.width - c_width;
    }
}

Rectangle Player::aabb() const
{
    return {m_x, m_y, c_width, c_height};
}

Rectangle Player::sweepAABB() const
{
    const float startY = std::min(m_previousY, m_y);
    const float endY = std::max(m_previousY, m_y);
    return {m_x, startY, c_width + 20.0f, endY - startY + c_height};
}

float Player::velocity() const
{
    return m_velocityY;
}

float Player::y() const
{
    return m_y;
}

void Player::moveLeft(float deltaTime) 
{
    m_x -=c_speed * deltaTime;
}

void Player::moveRight(float deltaTime) 
{
    m_x +=c_speed * deltaTime;
}

void Player::jump() 
{
    m_velocityY = c_jumpVelocity;
}

void Player::setY(float y) 
{
    m_y = y;
}
