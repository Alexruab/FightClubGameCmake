#pragma once
#include "Types.h"
#include "raylib.h"
#include <vector>

class PlatformManager
{
public:
    PlatformManager(const ScreenSize& screenSize);
    void applyScroll(float offset);

    struct Config
    {
        const int platformCount{10};
        const float platformWidth{100.0f};
        const float platformHeight{10.0f};
    };
    

    const std::vector<Rectangle>& platforms() const;

private:
    const ScreenSize c_screenSize;
    const float c_verticalSpacing;
    std::vector<Rectangle> m_platforms;

    void regeneratePlatform(Rectangle& platform);
};