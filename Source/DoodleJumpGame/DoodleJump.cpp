#include "DoodleJump.h"
#include "raylib.h"
#include "Types.h"
#include "Player.h"
#include "PlatformManager.h"

namespace
{
    constexpr ScreenSize c_screenSize{950, 1300};

    bool isPlatformGropund(const Rectangle& player, const Rectangle& priviousPlayer, const Rectangle& platform, float yTreshold = 10.0f)
    {
        // priviousPlayer here is the sweep AABB (covering previous -> current vertical motion)
        // We want to detect landing on the platform only when the player moved downward through
        // the platform's Y and there is horizontal overlap.

        // Quick horizontal overlap check
        const bool horizOverlap = true;//!(player.x + player.width < platform.x || player.x > platform.x + platform.width);

        // If the sweep doesn't intersect the platform at all, we can't have landed on it this frame

        // Derive previous Y from the sweep rect. sweep.y is min(previousY, currentY).
        const float prevY = (priviousPlayer.y < player.y) ? priviousPlayer.y : player.y;
        const float prevBottom = prevY + player.height;
        const float currBottom = player.y + player.height;

        

        // We consider it a ground collision if:
        //  - there was a swept intersection with the platform
        //  - horizontal overlap exists
        //  - player was above (or near) the platform in the previous frame
        //  - player is now at or below the platform Y (i.e. moved down onto it)
        return horizOverlap && CheckCollisionRecs(priviousPlayer, platform) && (prevBottom <= platform.y + yTreshold) && (currBottom >= platform.y - yTreshold);
    }
}

DoodleJump::DoodleJump() 
{
    reset();
}

DoodleJump::~DoodleJump() {}

void DoodleJump::reset() 
{
    m_isGameOver = false;
    m_score = 0;
    m_player.reset(new Player(c_screenSize));
    m_platforms.reset(new PlatformManager(c_screenSize));
}

void DoodleJump::run() 
{
    const char* windowsTitle = "Doodle Jump";
    InitWindow(c_screenSize.width, c_screenSize.height, windowsTitle);
    SetTargetFPS(10);

    

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        SetWindowTitle(TextFormat("%s - %d FPS", windowsTitle, GetFPS()));

        if(!m_isGameOver)
        {
            handalInput();
            updata();
            draw();
        }
        else
        {
            drawGemaOver();

            if(IsKeyDown(KEY_ENTER))
            {
                reset();
            }
        }
        
        // if(IsKeyPressed(KEY_ENTER))
        // {
            
        // }
        

        // BeginDrawing();
        // ClearBackground(DARKPURPLE);
        // DrawText("Hello World!", 190, 200, 20, LIGHTGRAY);
        // EndDrawing();

    }
    CloseWindow();
}



void DoodleJump::handalInput() 
{
    if(IsKeyDown(KEY_A))
    {
        m_player->moveLeft(GetFrameTime());
    }

    if(IsKeyDown(KEY_D))
    {
        m_player->moveRight(GetFrameTime());
    }
}

void DoodleJump::updata() 
{
    m_player->update(GetFrameTime());
    if(m_player->velocity() > 0.0f)
    {
        m_isGameOver = m_player->y() > c_screenSize.height;

        for(const auto& platform : m_platforms->platforms())
        {
            if(isPlatformGropund(m_player->aabb(), m_player->sweepAABB(), platform))
            {
                m_player->jump();
                break;
            }
        }
    }

    const float screenCenterY = c_screenSize.height * 0.5f;

    if(m_player->y() < screenCenterY)
    {
        const float offsetY =screenCenterY - m_player->y();
        m_player->setY(screenCenterY);
        m_platforms->applyScroll(offsetY);
        m_score += static_cast<int>(offsetY);
    }
    
}

void DoodleJump::draw() 
{
    BeginDrawing();
    ClearBackground(WHITE);

    for(const auto& platform : m_platforms->platforms())
    {
        DrawRectangleRec(platform, DARKGREEN);
        DrawRectangleLinesEx(platform, 2, BLACK);
    }

    DrawRectangleRec(m_player->sweepAABB(), RED);
    DrawRectangleRec(m_player->aabb(), GREEN);
    
    DrawRectangleLinesEx(m_player->aabb(), 2, BLACK);

    DrawText(TextFormat("Score: %d", m_score), 10, 10, 20, BLACK);
    
    EndDrawing();
}

void DoodleJump::drawGemaOver() 
{
    const int gameOverTextWidth= MeasureText("GAME OVER!!!!!!!!", 80);
    const int gameOverCenterX = (c_screenSize.width - gameOverTextWidth) / 2;
    const char* scoreText = TextFormat("Score: %d", m_score);
    const int scoreTextWidth= MeasureText(scoreText, 50);
    const int scoreCenterX = (c_screenSize.width - scoreTextWidth) / 2;
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("GAME OVER!!!!!!!!", gameOverCenterX, c_screenSize.height * 0.5f - 100, 80, RED);
    DrawText(scoreText, scoreCenterX, c_screenSize.height * 0.5f, 50, RED);
    EndDrawing();
}
