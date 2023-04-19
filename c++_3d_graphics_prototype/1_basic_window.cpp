#include "raylib.h"
#include "raymath.h"

int main(void)
{
    // Initialize game
    InitWindow(1280, 960, "C++ 3D Graphics Prototype");

    while (!WindowShouldClose())
    {
        // Update variables

        // Draw stuff
        BeginDrawing();
        ClearBackground(RAYWHITE);


        EndDrawing();

    }

    // Uninitialize game
    CloseWindow();

    return 0;
}