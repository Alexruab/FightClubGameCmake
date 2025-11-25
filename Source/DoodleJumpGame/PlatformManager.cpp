#include "PlatformManager.h"
#include "./Utils/Math.h"
#include <algorithm>

namespace
{
    constexpr int c_platformCount{10};
    constexpr float c_platformWidth{100.0f};
    constexpr float c_platformHeight{10.0f};
}

PlatformManager::PlatformManager(const ScreenSize& screenSize) : c_screenSize{screenSize}, c_verticalSpacing{static_cast<float>(screenSize.height) / c_platformCount}
{
    m_platforms.reserve(c_platformCount);

    for(int i = 0; i < c_platformCount; ++i)
    {
        const float x = LifeExe::randomFloat(0.0f, c_screenSize.width - c_platformWidth);
        const float y = i * c_verticalSpacing + LifeExe::randomFloat(0.0f, c_verticalSpacing * 0.5f);
        m_platforms.push_back({x, y, c_platformWidth, c_platformHeight});
    }
}

void PlatformManager::applyScroll(float offset) 
{
    for(auto& platform : m_platforms)
    {
        platform.y += offset;
        if(platform.y > c_screenSize.height)
        {
            regeneratePlatform(platform);
        }
    }
}

void PlatformManager::regeneratePlatform(Rectangle& platform)
{
    const auto minPlatform = std::min_element(m_platforms.begin(), m_platforms.end(), [](const auto& a, const auto& b){return a.y < b.y;});
    platform.x = LifeExe::randomFloat(0.0f, c_screenSize.width - c_platformWidth);
    platform.y = minPlatform->y - (c_verticalSpacing + LifeExe::randomFloat(0.0f, c_verticalSpacing * 0.5f));
}

const std::vector<Rectangle>& PlatformManager::platforms() const
{
    return m_platforms;
}
