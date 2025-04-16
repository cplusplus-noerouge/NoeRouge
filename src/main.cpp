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
<<<<<<< Updated upstream
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
=======
// IMPORTANT! These are different versions of the camera with different zoom levels, uncomment the one you want.
//CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 640.0f, 360.0f }, 2.0f );
CustomCamera mainCamera = CustomCamera( Vector2 { 1280, 720.0f }, 1.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

int main( )
{
   // Setting up graphics
   loadAllTextures( );
   screenHandler.cameras.push_back( &mainCamera );

   //seed the random number generator
   srand( ( unsigned int ) time( 0 ) );
   int randomNumber = rand( ) % 3;
   Floor floor( randomNumber );

   std::vector<Rectangle> walls = floor.getWalls( );
   Vector2 playerSpawnPosition = floor.getPlayerSpawn( );
   std::vector<Sprite> wallSprites = {};
   for ( Rectangle wall : walls )
   {
      wallSprites.push_back( Sprite( "wall", { wall.x, wall.y }, wall.y ) );
   }

>>>>>>> Stashed changes

   // Create the objectHandler
   class ObjectHandler objectHandler;
   class gameObject* testObject;

<<<<<<< Updated upstream
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
=======
   // Print version info
   std::cout << "noeRouge alpha v0.1\n";

   // Create a player so we can see it tick, and see it on screen
   objectHandler.createPlayer( playerSpawnPosition, { TILE_SIZE, TILE_SIZE }, 300 );

   while ( !WindowShouldClose( ) )
   {
      objectHandler.tickAll( walls );

      objectHandler.renderAll( );

      for ( int i = 0; i < wallSprites.size( ); i++ )
      {
         mainCamera.addToBuffer( &wallSprites[i] );
      }
      
      screenHandler.renderAll( );
   }

   return 0;
>>>>>>> Stashed changes
}
