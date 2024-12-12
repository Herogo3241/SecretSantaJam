#include "src/raylib.h"
#include "src/raymath.h"
#include <math.h>
#include "src/Enemy.h"
#include "src/Player.h"
#include "src/Monitor.h"
#include <vector>
#include <iostream>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#define MAX_POSTPRO_SHADERS 12

#define HEIGHT 720
#define WIDTH 960

int main()
{

    InitWindow(WIDTH, HEIGHT, "Secret Santa Jam");
    SetTargetFPS(60);

    // Player creation
    Player player({WIDTH / 2, HEIGHT / 2});

    Monitor level1mon("$$ Level 1 $$", {WIDTH/2, HEIGHT/2});

    // Enemies creation
    int count = 6;
    std::vector<Enemy> enemies;
    for (int i = 0; i < count; i++)
    {
        enemies.emplace_back(Vector2{(float)GetRandomValue(50, WIDTH - 50), (float)GetRandomValue(50, HEIGHT - 50)}, GetRandomValue(0, 1));
    }

    while (!WindowShouldClose())
    {
        player.update(GetFrameTime());
        for (auto &enemy : enemies)
        {
            enemy.update(GetFrameTime());
        }

        if(IsKeyPressed(KEY_E)) level1mon.toggleOpen();
        if(IsKeyPressed(KEY_ESCAPE)) level1mon.toggleClose();

        level1mon.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        for (auto &enemy : enemies)
        {
            enemy.draw();
        }
        player.draw();
        level1mon.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}