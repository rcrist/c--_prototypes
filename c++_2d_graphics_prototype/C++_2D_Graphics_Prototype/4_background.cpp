#include "include/raylib.h"

int main(void)
{
    InitWindow(1280, 960, "C++ 2D Graphics Prototype");

    // Add background images
    Image background = LoadImage("kenney_assets/backgrounds/set1_background.png");
    Texture2D texture1 = LoadTextureFromImage(background);
    UnloadImage(background); // Unload image from RAM

    Image bg1hills = LoadImage("kenney_assets/backgrounds/set1_hills.png");
    Texture2D texture2 = LoadTextureFromImage(bg1hills);
    UnloadImage(bg1hills); // Unload image from RAM

    Image bg1tiles = LoadImage("kenney_assets/backgrounds/set1_tiles.png");
    Texture2D texture3 = LoadTextureFromImage(bg1tiles);
    UnloadImage(bg1tiles); // Unload image from RAM

    while (!WindowShouldClose())
    {
        // Update variables

        // Draw stuff
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(texture1, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture3, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture2, Vector2{0, 0}, 0.0f, 2.0f, WHITE);

        EndDrawing();

        // De-Initialization (memory management)
    }

    CloseWindow();

    return 0;
}