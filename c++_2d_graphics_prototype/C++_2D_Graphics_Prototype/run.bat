@REM Accepts up to 3 file names

@REM Compile
g++ 10_platform_collisions.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
@REM gcc collision_example.c -o game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

@REM Run
game.exe