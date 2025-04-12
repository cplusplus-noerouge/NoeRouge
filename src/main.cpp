// noeRouge - Terminal rouge-like ascii dungeon crawler game

// Includes
#include <iostream>
#include <vector>
#include <cstdlib>
#include "raylib.h"

// Local includes
#include "object.h"
#include "globals.h"
#include "textureLoader.h"
#include "sprite.h"
#include "customCamera.h"
#include "screenHandler.h"
#include <mapGen.h>

/*
// TODO list (class voted it to be here)
// This list is worse than a todo at each thing because you have to just figure
// out where to work on each item listed here
//
// Doing it this way is objectivly worse in every way and has only
// disadvantages. I will comply but I beg that everyone agrees to 
// do it the other way instead
//
// 00 - Create a "game" class that holds deltatime, the map, the handlers, and
//      the game loop isRunning flag. This object will be global
// 01 - Game loop with time code
*/

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

constexpr int FPS = 60;

constexpr int PLAYER_SPEED = 300;

ScreenHandler screenHandler = ScreenHandler( );
CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

int main() {
        // Setting up graphics
   
   loadAllTextures( );
   screenHandler.cameras.push_back( &mainCamera );

        // TODO 00
    bool isGameRunning = true;
        // Create the objectHandler
    class objectHandler objectHandler;
    class gameObject *testObject;

        // Print version info
    std::cout << "noeRouge alpha v0.1\n";

        // Test object creation
    objectHandler.createObject();
    testObject = objectHandler.getObject(0);
    std::cout << testObject->getId() << std::endl;

        // Create a player so we can see it tick, and see it on screen
    objectHandler.createPlayer( { 0, 0 }, {30, 30}, 300);

    objectHandler.tickAll();

        // driver code - just for testing before real driver code
    Sprite sprite1 = Sprite( "player", Vector2 { 0, 0 }, 0, 0, 1, BLUE );
    while ( !WindowShouldClose( ) )
    {
       objectHandler.tickAll( );

       BeginDrawing( );

       ClearBackground( BLACK );

       objectHandler.renderAll( );

          // for testing purposes only
       for ( Rectangle rect : globals::GetCollisionRectangles( ) )
       {
          //DrawRectangle( rect.x, rect.y, rect.width, rect.height, DARKBLUE );
       }
       mainCamera.addToBuffer( &sprite1 );
       screenHandler.renderAll( );
    }

    unloadAllTextures( );

    // TODO 01
    /*
    while (isGameRunning) {
        time stuff

        if (tick) {
            objectHandler.tickAll();
        }
    }
    */

    return 0;
}
