#include "raylib.h"
#include "rcamera.h"

#define MAX_ENTITIES 8
#define MAX_COINS 8
#define MAX_COIN_MODELS 3

static void Init3DCamera();
static void Update3DCamera();

static void InitPlatforms();
static void InitCoins();

static void DrawBackground();
static void DrawPlatforms();
static void DrawCoins();

static void UnloadModels();

class Entity
{
public:
    Model model;
    Vector3 position;
    float scale;
};

class Coin
{
public:
    Model model;
    Vector3 position;
    float scale;
};

Model m1, m2, m3, m4, m5, m6, m7, m8;
Model c1, c2, c3;

Camera camera;
int cameraMode;

static Entity entities[MAX_ENTITIES] = {
    {m1, Vector3{10, 0, 10}, 2.0f},
    {m2, Vector3{-10, 0, 10}, 2.0f},
    {m3, Vector3{-10, 0, 2}, 2.0f},
    {m4, Vector3{22, 0, 5}, 2.0f},
    {m5, Vector3{-10, 0, 11.5}, 2.0f},
    {m6, Vector3{-10, 0, 6}, 2.0f},
    {m7, Vector3{-10, 0, -2}, 2.0f},
    {m8, Vector3{-10, 2, 0}, 2.0f},
};

static Coin coins[MAX_COINS] = {
    {c1, Vector3{-10, 1.1, 10}, 0.3f},
    {c1, Vector3{-10, 1.1, 9}, 0.3f},
    {c1, Vector3{-10, 1.1, 11}, 0.3f},
    {c2, Vector3{-10, 2.3, 2}, 0.3f},
    {c2, Vector3{-10, 2.3, 1}, 0.3f},
    {c3, Vector3{-10, 2.3, -2}, 0.3f},
    {c3, Vector3{-10, 2.3, -1}, 0.3f},
    {c3, Vector3{-10, 2.3, -3}, 0.3f},
};

int
main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "C++ 3D Graphics Prototype");
    Init3DCamera();
    InitPlatforms();
    InitCoins();

    DisableCursor(); // Limit cursor to relative movement inside the window
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        Update3DCamera();

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawBackground();
        DrawPlatforms();
        DrawCoins();

        // Draw player cube
        if (cameraMode == CAMERA_THIRD_PERSON)
        {
            DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
            DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
        }

        EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Uninitialize game
    UnloadModels();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

static void Init3DCamera()
{
    // Define the camera to look into our 3d world (position, target, up vector)
    camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera projection type
    cameraMode = CAMERA_FIRST_PERSON;
}

static void Update3DCamera()
{
    // Switch camera mode
    if (IsKeyPressed(KEY_ONE))
    {
        cameraMode = CAMERA_FREE;
        camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
    }

    if (IsKeyPressed(KEY_TWO))
    {
        cameraMode = CAMERA_FIRST_PERSON;
        camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
    }

    if (IsKeyPressed(KEY_THREE))
    {
        cameraMode = CAMERA_THIRD_PERSON;
        camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
    }

    if (IsKeyPressed(KEY_FOUR))
    {
        cameraMode = CAMERA_ORBITAL;
        camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
    }

    // Switch camera projection
    if (IsKeyPressed(KEY_P))
    {
        if (camera.projection == CAMERA_PERSPECTIVE)
        {
            // Create isometric view
            cameraMode = CAMERA_THIRD_PERSON;
            // Note: The target distance is related to the render distance in the orthographic projection
            camera.position = (Vector3){0.0f, 2.0f, -100.0f};
            camera.target = (Vector3){0.0f, 2.0f, 0.0f};
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
            camera.projection = CAMERA_ORTHOGRAPHIC;
            camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
            CameraYaw(&camera, -135 * DEG2RAD, true);
            CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
        }
        else if (camera.projection == CAMERA_ORTHOGRAPHIC)
        {
            // Reset to default view
            cameraMode = CAMERA_THIRD_PERSON;
            camera.position = (Vector3){0.0f, 2.0f, 10.0f};
            camera.target = (Vector3){0.0f, 2.0f, 0.0f};
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
            camera.projection = CAMERA_PERSPECTIVE;
            camera.fovy = 60.0f;
        }
    }

    UpdateCamera(&camera, cameraMode); // Update camera
}

static void InitPlatforms()
{
    // Initialize String Array for model filenames
    const char * filenames[MAX_ENTITIES] = {"Models/kenney_space-kit/Models/OBJ format/barrels.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/platform_low.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/platform_high.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/satelliteDish_detailed.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/stairs_short.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/pipe_rampLarge.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/platform_high.obj",
                                           "Models/kenney_space-kit/Models/OBJ format/platform_long.obj"};
    
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        entities[i].model = LoadModel(filenames[i]);
    }
}

static void InitCoins()
{
    const char *filenames[MAX_COIN_MODELS] = {"Models/kenney_space-kit/Models/OBJ format/meteor.obj",
                                              "Models/kenney_space-kit/Models/OBJ format/meteor_half.obj",
                                              "Models/kenney_space-kit/Models/OBJ format/meteor_detailed.obj"};

    coins[0].model = LoadModel(filenames[0]);
    coins[1].model = LoadModel(filenames[0]);
    coins[2].model = LoadModel(filenames[0]);

    coins[3].model = LoadModel(filenames[1]);
    coins[4].model = LoadModel(filenames[1]);

    coins[5].model = LoadModel(filenames[2]);
    coins[6].model = LoadModel(filenames[2]);
    coins[7].model = LoadModel(filenames[2]);
}

static void DrawBackground()
{
    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){64.0f, 64.0f}, LIGHTGRAY); // Draw ground
    DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 64.0f, BLUE);           // Draw a blue wall
    DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 64.0f, LIME);            // Draw a green wall
    DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 64.0f, 5.0f, 1.0f, GOLD);            // Draw a yellow wall
    DrawCube((Vector3){0.0f, 2.5f, -16.0f}, 64.0f, 5.0f, 1.0f, GRAY);           // Draw a gray
}

static void DrawPlatforms()
{
    for (int i = 0; i < MAX_ENTITIES; i++)
        DrawModel(entities[i].model, entities[i].position, entities[i].scale, WHITE);
}

static void DrawCoins()
{
    for (int i = 0; i < MAX_COINS; i++)
        DrawModel(coins[i].model, coins[i].position, coins[i].scale, WHITE);
}

static void UnloadModels()
{
    for (int i = 0; i < MAX_ENTITIES; i++)
        UnloadModel(entities[i].model);

    for (int i = 0; i < MAX_COINS; i++)
        UnloadModel(coins[i].model);
}