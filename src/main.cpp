// Includes
#include <iostream>
#include <vector>
#include <cstdlib>
#include <raylib.h>

// Local includes
#include "object.h"

#include "globals.h"
#include "textureLoader.h"
#include "sprite.h"
#include "customCamera.h"
#include "screenHandler.h"
#include "mapGen.h"

constexpr int SCREEN_WIDTH = 1280; //increased resolution & window size
constexpr int SCREEN_HEIGHT = 720;


constexpr int FPS = 60;

constexpr int PLAYER_SPEED = 300;

// <<<<<<< graphics
ScreenHandler screenHandler = ScreenHandler( );
CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

int main() {
//         Setting up graphics
   
   loadAllTextures( );
   screenHandler.cameras.push_back( &mainCamera );
// =======
// int main() 
// {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "noeRouge alpha v0.1");
    SetTargetFPS(FPS);
// >>>>>>> IntegratedMain-CombatCharacter

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
// <<<<<<< graphics
    objectHandler.createPlayer( { 0, 0 }, {30, 30}, 300);

    objectHandler.tickAll();

        // driver code - just for testing before real driver code
    Sprite sprite1 = Sprite( "player", Vector2 { 0, 0 }, 0, 0, 1, BLUE );
//     while ( !WindowShouldClose( ) )
//     {
//        objectHandler.tickAll( );
// =======
    objectHandler.createPlayer( playerSpawnPosition, {TILE_SIZE, TILE_SIZE}, 300);

    while (!WindowShouldClose())
    {
        objectHandler.tickAll(walls);
// >>>>>>> IntegratedMain-CombatCharacter

       BeginDrawing( );

       ClearBackground( BLACK );

       objectHandler.renderAll( );

// <<<<<<< graphics
          // for testing purposes only
//        for ( Rectangle rect : globals::GetCollisionRectangles( ) )
//        {
//           //DrawRectangle( rect.x, rect.y, rect.width, rect.height, DARKBLUE );
//        }
       mainCamera.addToBuffer( &sprite1 );
       screenHandler.renderAll( );
//     }

//     unloadAllTextures( );

    // TODO 01
    /*
    while (isGameRunning) {
        time stuff

        if (tick) {
            objectHandler.tickAll();
        }
    }
    */

// =======
        for (Rectangle wall : walls)
        {
            DrawRectangle(wall.x, wall.y, wall.width, wall.height, DARKBLUE);
        }

        EndDrawing();
        unloadAllTextures( ); //Added here for merge conflict resolution purposes.
    }

// >>>>>>> IntegratedMain-CombatCharacter
    return 0;
}
