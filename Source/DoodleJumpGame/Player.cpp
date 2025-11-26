#include "Player.h"
#include <algorithm>

Player::Player(const ScreenSize& screenSize, const Config& config) : c_screenSize{screenSize}, c_config{config}, m_velocityY{0.0f}
{
    m_x = (screenSize.width - c_config.width) * 0.5f;
    m_y = screenSize.height * 0.5f - c_config.initialOffsetY;
    m_previousY = m_y;
}

void Player::update(float deltaTime)
{
    m_previousY = m_y;
    m_velocityY += c_config.gravity * deltaTime;
    m_y +=m_velocityY * deltaTime;

    const float PlayerCenterX = m_x + c_config.width * 0.5f;
    if(PlayerCenterX >= c_screenSize.width)
    {
        m_x = 0.0f;
    } 
    else if (PlayerCenterX <= 0.0f)
    {
        m_x = c_screenSize.width - c_config.width;
    }
}

Rectangle Player::aabb() const
{
    return {m_x, m_y, c_config.width, c_config.height};
}

Rectangle Player::sweepAABB() const
{
    const float startY = std::min(m_previousY, m_y);
    const float endY = std::max(m_previousY, m_y);
    return {m_x, startY, c_config.width + 20.0f, endY - startY + c_config.height};
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
    m_x -= c_config.speed * deltaTime;
}

void Player::moveRight(float deltaTime) 
{
    m_x += c_config.speed * deltaTime;
}

void Player::jump() 
{
    m_velocityY = c_config.jumpVelocity;
}

void Player::setY(float y) 
{
    m_y = y;
}
