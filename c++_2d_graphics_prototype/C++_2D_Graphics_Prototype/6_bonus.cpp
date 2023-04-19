#include <stdlib.h>
#include <time.h>

#include "include/raylib.h"
#include "include/raymath.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define SCREEN_SIZE CLITER(SCREEN_WIDTH, SCREEN_HEIGHT)

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C++ 2D Graphics Prototype");

    // Add player
    Texture2D player = LoadTexture("kenney_assets/Player/character_robot_idle.png");

    // Add background images
    Texture2D background = LoadTexture("kenney_assets/backgrounds/set1_background.png");
    Texture2D bg1hills = LoadTexture("kenney_assets/backgrounds/set1_hills.png");
    Texture2D bg1tiles = LoadTexture("kenney_assets/backgrounds/set1_tiles.png");

    // Add platforms
    Texture2D p2 = LoadTexture("kenney_assets/Tiles/tileBlue_02.png");
    Texture2D p3 = LoadTexture("kenney_assets/Tiles/tileBlue_03.png");
    Texture2D p4 = LoadTexture("kenney_assets/Tiles/tileBlue_04.png");
    Texture2D p5 = LoadTexture("kenney_assets/Tiles/tileBlue_05.png");
    Texture2D p6 = LoadTexture("kenney_assets/Tiles/tileBlue_06.png");
    Texture2D p9 = LoadTexture("kenney_assets/Tiles/tileBlue_09.png");
    Texture2D p10 = LoadTexture("kenney_assets/Tiles/tileBlue_10.png");
    Texture2D p13 = LoadTexture("kenney_assets/Tiles/tileBlue_13.png");
    Texture2D p14 = LoadTexture("kenney_assets/Tiles/tileBlue_14.png");
    Texture2D p15 = LoadTexture("kenney_assets/Tiles/tileBlue_15.png");
    Texture2D p16 = LoadTexture("kenney_assets/Tiles/tileBlue_16.png");
    Texture2D p24 = LoadTexture("kenney_assets/Tiles/tileBlue_24.png");
    Texture2D p25 = LoadTexture("kenney_assets/Tiles/tileBlue_25.png");

    // Add bonus items
    Texture2D g1 = LoadTexture("kenney_assets/Bonus/blueCrystal.png");
    Texture2D g2 = LoadTexture("kenney_assets/Bonus/blueGem.png");
    Texture2D g3 = LoadTexture("kenney_assets/Bonus/blueJewel.png");

    while (!WindowShouldClose())
    {
        // Update variables

        // Draw stuff
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background textures

        DrawTextureEx(background, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(bg1tiles, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(bg1hills, Vector2{0, 0}, 0.0f, 2.0f, WHITE);

        // Draw platforms
        DrawTextureEx(p3, Vector2{0, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{0, 896 - 128 - 64 / 2}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p14, Vector2{128, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p10, Vector2{128, 896 - 128 - 64 / 2}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{128 + 2 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p3, Vector2{128 + 3 * 64, 896 - 32 - 64}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p13, Vector2{128 + 3 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p4, Vector2{128 + 3 * 64, 896 - 32 - 128}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p3, Vector2{128 + 5 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p6, Vector2{128 + 5 * 64, 896 - 32 - 128}, 0.0f, 2.0f, WHITE);
        // Gap in ground
        DrawTextureEx(p4, Vector2{11 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{12 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{13 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p13, Vector2{14 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p9, Vector2{14 * 64, 896 - 128 - 64 / 2}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p3, Vector2{16 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p3, Vector2{18 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{16 * 64, 896 - 128 - 64 / 2}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p5, Vector2{18 * 64, 896 - 128 - 64 / 2}, 0.0f, 2.0f, WHITE);

        // Draw floating platforms
        DrawTextureEx(p2, Vector2{200, 400}, 0.0f, 2.0f, WHITE);

        DrawTextureEx(p15, Vector2{500, 400}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p16, Vector2{562 + 64, 400}, 0.0f, 2.0f, WHITE);

        DrawTextureEx(p24, Vector2{900, 200}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(p25, Vector2{962 + 64, 200}, 0.0f, 2.0f, WHITE);

        // Draw bonuses
        DrawTextureEx(g2, Vector2{200,360}, 0.0f, 1.5f, WHITE);
        DrawTextureEx(g2, Vector2{296, 360}, 0.0f, 1.5f, WHITE);

        DrawTextureEx(g1, Vector2{510, 360}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(g1, Vector2{510+96, 360}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(g1, Vector2{574+128, 360}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(g3, Vector2{910, 160}, 0.0f, 1.5f, WHITE);
        DrawTextureEx(g3, Vector2{910 + 96, 160}, 0.0f, 1.5f, WHITE);
        DrawTextureEx(g3, Vector2{974 + 128, 160}, 0.0f, 1.5f, WHITE);

        // Draw player
        DrawTextureEx(player, Vector2{0, 960 - 4 * 64 - 96}, 0.0f, 1.0f, WHITE);

        EndDrawing();

        // De-Initialization (memory management)
    }

    CloseWindow();

    return 0;
}