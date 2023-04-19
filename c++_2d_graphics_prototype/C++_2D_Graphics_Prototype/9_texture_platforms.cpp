#include <iostream>
#include "include/raylib.h"

#define MAX_COINS 8

static void InitGame(void);
static void UpdateGame(void);
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

static void InitCoins(void);
static void DrawCoins(void);
static void UpdateCoins(void);

static void UnloadTextures(void);

Texture2D background;
Texture2D bg1hills;
Texture2D bg1tiles;
Texture2D p2_tex, p3_tex, p4_tex, p5_tex, p6_tex, p9_tex, p10_tex, p13_tex, p14_tex, p15_tex, p16_tex, p24_tex, p25_tex;
Texture2D c1_tex, c2_tex, c3_tex;
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
    Texture2D tex;
    Vector2 position;
    Rectangle rect;
};

class Coin
{
public:
    Texture2D tex;
    Vector2 position;
    float scale;
    bool visible;    
};

Player player;
Platform ground, rwall, lwall;
Platform p2, p3, p4, p5, p6, p9, p10, p13, p14, p15, p16, p24, p25;

// Create coin instances
static Coin coins[MAX_COINS] = {
    {c2_tex, Vector2{210, 360}, 1.5f, true},
    {c2_tex, Vector2{210 + 76, 360}, 1.5f, true},
    {c1_tex, Vector2{510, 350}, 1.2f, true},
    {c1_tex, Vector2{510 + 100, 350}, 1.2f, true},
    {c1_tex, Vector2{510 + 2 * 100, 350}, 1.2f, true},
    {c3_tex, Vector2{910, 160}, 1.5f, true},
    {c3_tex, Vector2{910 + 100, 160}, 1.5f, true},
    {c3_tex, Vector2{910 + 2 * 100, 160}, 1.5f, true},
};

bool collision = false;       // Collision detection
Rectangle boxCollision = {0}; // Collision rectangle
static float delta;
static bool win = false;
static int score = 0;

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

        UpdateGame();

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
    InitCoins();
}

static void InitPlayer()
{
    player_texture = LoadTexture("kenney_assets/Player/character_robot_idle.png");
    player.tex = player_texture;
    player.position = Vector2{55, 600};
    player.collider.x = player.position.x + 12;
    player.collider.y = player.position.y + 28;
    player.speed.x = 0.1;
    player.speed.y = 0.1;
    player.gravity = 0.363281f * 60 * 60;
}

static void InitBackground(void)
{
    // Add background images
    background = LoadTexture("kenney_assets/backgrounds/set1_background.png");
    bg1hills = LoadTexture("kenney_assets/backgrounds/set1_hills.png");
    bg1tiles = LoadTexture("kenney_assets/backgrounds/set1_tiles.png");
}

static void InitPlatforms(void)
{
    // ground.position = Vector2{0, GetScreenHeight() / 1.0f - 50};
    // ground.rect = Rectangle{0, GetScreenHeight() / 1.0f - 50, GetScreenWidth() / 1.0f, 50};
    // Add platforms
    p2_tex = LoadTexture("kenney_assets/Tiles/tileBlue_02.png");
    p3_tex = LoadTexture("kenney_assets/Tiles/tileBlue_03.png");
    p4_tex = LoadTexture("kenney_assets/Tiles/tileBlue_04.png");
    p5_tex = LoadTexture("kenney_assets/Tiles/tileBlue_05.png");
    p6_tex = LoadTexture("kenney_assets/Tiles/tileBlue_06.png");
    p9_tex = LoadTexture("kenney_assets/Tiles/tileBlue_09.png");
    p10_tex = LoadTexture("kenney_assets/Tiles/tileBlue_10.png");
    p13_tex = LoadTexture("kenney_assets/Tiles/tileBlue_13.png");
    p14_tex = LoadTexture("kenney_assets/Tiles/tileBlue_14.png");
    p15_tex = LoadTexture("kenney_assets/Tiles/tileBlue_15.png");
    p16_tex = LoadTexture("kenney_assets/Tiles/tileBlue_16.png");
    p24_tex = LoadTexture("kenney_assets/Tiles/tileBlue_24.png");
    p25_tex = LoadTexture("kenney_assets/Tiles/tileBlue_25.png");

    lwall.position = Vector2{0, 0};
    lwall.rect = Rectangle{0, 0, 50, GetScreenHeight() / 1.0f};

    rwall.position = Vector2{GetScreenWidth() / 1.0f - 50, GetScreenHeight() / 1.0f};
    rwall.rect = Rectangle{GetScreenWidth() / 1.0f - 50, 0.0f, 50, GetScreenHeight() / 1.0f};
}

static void InitCoins(void)
{
    c1_tex = LoadTexture("kenney_assets/Bonus/blueCrystal.png");
    c2_tex = LoadTexture("kenney_assets/Bonus/blueGem.png");
    c3_tex = LoadTexture("kenney_assets/Bonus/blueJewel.png");

    for (int i = 0; i < MAX_COINS; i++)
    {
        coins[i].visible = true;

        if (i >= 0 && i <= 1)
            coins[i].tex = c2_tex;
        else if (i >= 2 && i <= 4)
            coins[i].tex = c1_tex;
        else if (i >= 5 && i <= 7)
            coins[i].tex = c3_tex;
    }
}

static void UpdateGame(void)
{
    UpdatePlayer();
    UpdatePlatforms();
    UpdateCoins();
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
    if ((float)(IsKeyDown('A') || IsKeyDown(KEY_LEFT))) // Move left
    {
        player.position.x -= player.speed.x;
        player.collider.x = player.position.x + 12;
    }
    if ((float)(IsKeyDown('W') || IsKeyDown(KEY_UP))) // Move up
    {
        player.position.y -= player.speed.y;
        player.collider.y = player.position.y + 28;
    }
    if ((float)(IsKeyDown('S') || IsKeyDown(KEY_DOWN))) // Move down
    {
        player.position.y += player.speed.y;
        player.collider.y = player.position.y + 28;
    }

    if (IsKeyPressed(KEY_SPACE)) // Jump
    {
        player.position.y -= 300;
        player.collider.y = player.position.y + 28;
    }
}

static void UpdatePlatforms(void)
{
    // Add platform animation here
}

static void UpdateCoins(void)
{
    Rectangle playerRect = player.collider;

    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].visible)
        {
            Rectangle coinRect = (Rectangle){coins[i].position.x, coins[i].position.y, 4.0, 4.0};

            if (CheckCollisionRecs(playerRect, coinRect))
            {
                coins[i].visible = false;
                score += 1;
            }
        }
    }

    win = score == MAX_COINS;
}

static void DrawGame(void)
{
    DrawBackground();
    DrawPlayer();
    DrawPlatforms();
    DrawCoins();

    DrawText(TextFormat("SCORE: %i", score), GetScreenWidth() / 2 - MeasureText(TextFormat("SCORE: %i", score), 40) / 2, 50, 40, BLACK);

    if (win)
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 350, 20, GRAY);
}

static void DrawBackground(void)
{
    DrawTextureEx(background, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(bg1tiles, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(bg1hills, Vector2{0, 0}, 0.0f, 2.0f, WHITE);
}

static void DrawPlayer()
{
    DrawTextureEx(player.tex, player.position, 0.0f, 0.75f, WHITE); // Draw player
    DrawRectangleLines(player.collider.x, player.collider.y, player.collider.width, player.collider.height, BLUE); // Draw player collider
}

static void DrawPlatforms(void)
{
    // DrawRectangleRec(ground.rect, GRAY);
    DrawTextureEx(p3_tex, Vector2{0, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{0, 896 - 160}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p14_tex, Vector2{128, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{128 + 2 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p6_tex, Vector2{128, 896 - 160}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{128 + 3 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p3_tex, Vector2{128 + 4 * 64, 896 - 32 - 64}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p13_tex, Vector2{128 + 4 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p4_tex, Vector2{128 + 4 * 64, 896 - 32 - 128}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p3_tex, Vector2{128 + 6 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p6_tex, Vector2{128 + 6 * 64, 896 - 32 - 128}, 0.0f, 2.0f, WHITE);
    // Gap in ground
    DrawTextureEx(p4_tex, Vector2{12 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{13 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{14 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p13_tex, Vector2{16 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p4_tex, Vector2{16 * 64, 896 - 160}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p3_tex, Vector2{18 * 64, 896 - 32}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p5_tex, Vector2{18 * 64, 896 - 160}, 0.0f, 2.0f, WHITE);

    // Draw floating platforms
    DrawTextureEx(p2_tex, Vector2{200, 400}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(p15_tex, Vector2{500, 400}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p16_tex, Vector2{500 + 126, 400}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(p24_tex, Vector2{900, 200}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(p25_tex, Vector2{900 + 126, 200}, 0.0f, 2.0f, WHITE);

    DrawRectangleRec(rwall.rect, GRAY);
    DrawRectangleRec(lwall.rect, GRAY);
}

static void DrawCoins(void)
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].visible)
            DrawTextureEx(coins[i].tex, coins[i].position, 0.0f, coins[i].scale, WHITE);
        // DrawRectangle((int)coins[i].position.x, (int)coins[i].position.y, 4.0, 4.0, GOLD);
    }
}

static void CheckCollision()
{
    // Check collision with ground
    collision = CheckCollisionRecs(player.collider, ground.rect);
    if (collision)
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
    // player.position.y += 0.1f;
    player.position.y += 0.0f;
    player.collider.y = player.position.y + 28;
}

static void UnloadTextures()
{
    // Unload background textures
    UnloadTexture(background);
    UnloadTexture(bg1hills);
    UnloadTexture(bg1tiles);

    // Unload platform textures
    UnloadTexture(p2_tex);
    UnloadTexture(p3_tex);
    UnloadTexture(p4_tex);
    UnloadTexture(p5_tex);
    UnloadTexture(p6_tex);
    UnloadTexture(p9_tex);
    UnloadTexture(p10_tex);
    UnloadTexture(p13_tex);
    UnloadTexture(p14_tex);
    UnloadTexture(p15_tex);
    UnloadTexture(p16_tex);
    UnloadTexture(p24_tex);
    UnloadTexture(p25_tex);

    // Unload coin textures
    UnloadTexture(c1_tex);
    UnloadTexture(c2_tex);
    UnloadTexture(c3_tex);

    // Unload player texture
    UnloadTexture(player_texture);
}