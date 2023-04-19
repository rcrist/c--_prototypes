#include <iostream>
#include "include/raylib.h"

static void InitGame(void);
static void DrawGame(void);

static void InitBackground(void);
static void DrawBackground(void);

static void InitPlayer(void);
static void DrawPlayer(void);
static void UpdatePlayer(void);
static void CheckCollision(void);
static void GravityCalc(void);

static void InitPlatforms(void);
static void DrawPlatforms(void);
static void UpdatePlatforms(void);

static void UnloadTextures(void);

Texture2D background;
Texture2D bg1hills;
Texture2D bg1tiles;
Texture2D player_texture;

class Player
{
    public:
        Texture2D tex;
        Vector2 position;
        Vector2 speed;
        Rectangle collider = Rectangle{position.x + 32, position.y + 16, 48, 70};
        float gravity;
};

class Platform
{
    public:
        Rectangle rect;
        Vector2 position;
};

Player player;
Platform ground, rwall, lwall;
bool collision = false; // Collision detection
Rectangle boxCollision = {0}; // Collision rectangle
static float delta;

int main(void)
{
    InitWindow(1280, 960, "C++ 2D Graphics Prototype");

    InitGame();

    // SetTargetFPS(120); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())
    {
        // Update variables
        // Get time since last frame
        delta = GetFrameTime();

        UpdatePlayer();
        UpdatePlatforms();

        // Draw stuff
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawGame();
        }

        DrawFPS(60, 10);
        EndDrawing();
    }

    // Uninitialize game
    UnloadTextures();
    CloseWindow();

    return 0;
}

static void InitGame(void)
{
    InitPlayer();
    InitBackground();
    InitPlatforms();
}

static void InitBackground(void)
{
    // Add background images
    background = LoadTexture("kenney_assets/backgrounds/set1_background.png");
    bg1hills = LoadTexture("kenney_assets/backgrounds/set1_hills.png");
    bg1tiles = LoadTexture("kenney_assets/backgrounds/set1_tiles.png");
}

static void DrawGame(void)
{
    DrawBackground();
    DrawPlayer();
    DrawPlatforms();
}

static void DrawBackground(void)
{
    DrawTextureEx(background, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(bg1tiles, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(bg1hills, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
}

static void InitPlayer()
{
    player_texture = LoadTexture("kenney_assets/Player/character_robot_idle.png");
    player.tex = player_texture;
    player.position = Vector2{1280 / 2, 960 / 2};
    player.collider.x = player.position.x + 12;
    player.collider.y = player.position.y + 28;
    player.speed.x = 0.1;
    player.speed.y = 0.1;
    player.gravity = 0.363281f * 60 * 60;
}

static void DrawPlayer()
{
    DrawTextureEx(player.tex, player.position, 0.0f, 0.75f, WHITE);
    DrawRectangleLines(player.collider.x, player.collider.y, player.collider.width, player.collider.height, BLUE);
}

static void UpdatePlayer()
{
    GravityCalc();
    CheckCollision();

    if ((float)(IsKeyDown('D') || IsKeyDown(KEY_RIGHT))) // Move right
    {
        player.position.x += player.speed.x;
        player.collider.x = player.position.x + 12;
    }
    if ((float)(IsKeyDown('A') || IsKeyDown(KEY_LEFT)))  // Move left
    {
        player.position.x -= player.speed.x;
        player.collider.x = player.position.x + 12;
    }
    if ((float)(IsKeyDown('W') || IsKeyDown(KEY_UP)))    // Move up
    {
        player.position.y -= player.speed.y;
        player.collider.y = player.position.y + 28;
    }
    if ((float)(IsKeyDown('S') || IsKeyDown(KEY_DOWN)))  // Move down
    {
        player.position.y += player.speed.y;
        player.collider.y = player.position.y + 28;
    }

    if (IsKeyPressed(KEY_SPACE))                        // Jump
    {
        player.position.y -= 300;
        player.collider.y = player.position.y + 28;
    }
}

static void CheckCollision()
{
    // Check collision with ground
    collision = CheckCollisionRecs(player.collider, ground.rect);
    if(collision)
        boxCollision = GetCollisionRec(player.collider, ground.rect);
    else
    {
        player.speed.x = 0.1f;
        player.speed.y = 0.1f;
    }

    if (collision)
    {
        if (boxCollision.width > 0 || boxCollision.height > 0)
        {
            player.speed.y = 0.0f;
            player.position.y -= 2.0;
        }
    }

    // Check collision with left wall
    collision = CheckCollisionRecs(player.collider, lwall.rect);
    if (collision)
        boxCollision = GetCollisionRec(player.collider, lwall.rect);

    if (collision)
    {
        if (boxCollision.width > 0 || boxCollision.height > 0)
        {
            player.speed.x = 0.0f;
            player.position.x += 2.0;
        }
    }

    // Check collision with right wall
    collision = CheckCollisionRecs(player.collider, rwall.rect);
    if (collision)
        boxCollision = GetCollisionRec(player.collider, rwall.rect);

    if (collision)
    {
        if (boxCollision.width > 0 || boxCollision.height > 0)
        {
            player.speed.x = 0.0f;
            player.position.x -= 2.0;
        }
    }
}

static void GravityCalc(void)
{
    // Add enough gravity to prevent move in up direction
    player.position.y += 0.1f;
    player.collider.y = player.position.y + 28;
}

static void InitPlatforms(void)
{
    ground.position = Vector2 { 0, GetScreenHeight() / 1.0f - 50 };
    ground.rect = Rectangle{0, GetScreenHeight() / 1.0f - 50, GetScreenWidth() / 1.0f, 50};

    lwall.position = Vector2{0, 0};
    lwall.rect = Rectangle{0, 0, 50, GetScreenHeight() / 1.0f};
 
    rwall.position = Vector2{GetScreenWidth() / 1.0f - 50, GetScreenHeight() / 1.0f};
    rwall.rect = Rectangle{GetScreenWidth() / 1.0f - 50, 0.0f, 50, GetScreenHeight() / 1.0f};
}

static void DrawPlatforms(void)
{
    DrawRectangleRec(ground.rect, GRAY);
    DrawRectangleRec(rwall.rect, GRAY);
    DrawRectangleRec(lwall.rect, GRAY);
}

static void UpdatePlatforms(void)
{

}

static void UnloadTextures()
{
    UnloadTexture(background); // Unload image from RAM
    UnloadTexture(bg1hills);   // Unload image from RAM
    UnloadTexture(bg1tiles);   // Unload image from RAM
    UnloadTexture(player_texture);
}