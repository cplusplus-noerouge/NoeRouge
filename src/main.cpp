// Includes
#include <iostream>
#include <vector>
#include <cstdlib>
#include <raylib.h>

// Local includes
#include "character.h"
#include "player.h"
#include "object.h"
#include "mapGen.h"

constexpr int SCREEN_WIDTH = 1280; //increased resolution & window size
constexpr int SCREEN_HEIGHT = 720;

constexpr int FPS = 60;

constexpr int PLAYER_SPEED = 300;

int main() 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "noeRouge alpha v0.1");
    SetTargetFPS(FPS);

        //seed the random number generator
    srand((unsigned int)time(0));
    int randomNumber = rand() % 3;
    Floor floor(randomNumber);

    std::vector<Rectangle> walls = floor.getWalls();
    Vector2 playerSpawnPosition = floor.getPlayerSpawn();

        // Create the objectHandler
    class ObjectHandler objectHandler;
    class gameObject *testObject;

        // Print version info
    std::cout << "noeRouge alpha v0.1\n";

        // Create a player so we can see it tick, and see it on screen
    objectHandler.createPlayer( playerSpawnPosition, {TILE_SIZE, TILE_SIZE}, 300);

    while (!WindowShouldClose())
    {
        objectHandler.tickAll(walls);

        BeginDrawing();
       
        ClearBackground(BLACK);

        objectHandler.renderAll();

        for (Rectangle wall : walls)
        {

            DrawRectangle(wall.x, wall.y, wall.width, wall.height, DARKBLUE);

        }
        EndDrawing();
    }

    return 0;
}
