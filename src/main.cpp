// Includes
#include <iostream>
#include <vector>
#include <cstdlib>
#include "raylib.h"

// Local includes
#include "character.h"
#include "player.h"
#include "object.h"
#include "mapGen.h"
#include "textureLoader.h"
#include "sprite.h"
#include "customCamera.h"
#include "screenHandler.h"

constexpr int SCREEN_WIDTH = 1280; //increased resolution & window size
constexpr int SCREEN_HEIGHT = 720;

constexpr int FPS = 60;

constexpr int PLAYER_SPEED = 300;

ScreenHandler screenHandler = ScreenHandler( );
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
    srand((unsigned int)time(0));
    int randomNumber = rand() % 3;
    Floor floor(randomNumber);

    std::vector<Rectangle> walls = floor.getWalls();
    Vector2 playerSpawnPosition = floor.getPlayerSpawn();
    std::vector<Sprite> wallSprites = {};
    for ( Rectangle wall : walls )
    {
       wallSprites.push_back( Sprite( "wall", { wall.x, wall.y }, wall.y ) );
    }

        // Create the objectHandler
    class ObjectHandler objectHandler;
    class gameObject *testObject;

        // Print version info
    std::cout << "noeRouge alpha v0.1\n";

        // Create a player so we can see it tick, and see it on screen
    objectHandler.createPlayer( playerSpawnPosition, {TILE_SIZE, TILE_SIZE}, 300);

    while ( !WindowShouldClose( ) )
    {
       objectHandler.tickAll( walls );

       objectHandler.renderAll( );

       for ( int i = 0; i < wallSprites.size( ); i++ )
       {
          mainCamera.addToBuffer( &wallSprites[ i ] );
       }

       screenHandler.renderAll( );
    }

    return 0;
}
