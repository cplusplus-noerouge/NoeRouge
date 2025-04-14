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

constexpr int FPS = 60;
constexpr int PLAYER_SPEED = 300;
const int NUM_OF_FLOORS = 4;

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

    //make the floors
    Floor* floors[NUM_OF_FLOORS];
    for (int i = 0; i < NUM_OF_FLOORS; i++) {
        floors[i] = new Floor;
    }
    int floorOn = 0;                 //the floor the player is on. when the player moves floors this changes

    // Create a player so we can see it tick, and see it on screen
    Vector2 playerSpawnPosition = floors[floorOn]->getPlayerSpawn();
    floors[floorOn]->getObjHandler()->createPlayer(playerSpawnPosition, {TILE_SIZE, TILE_SIZE}, 300);

    //TODO these really should not be recalculated every frame, fix this
    std::vector<Sprite> wallSprites = {};

    while (!WindowShouldClose())
    {
        //TEMPORARY testing changing floors. needs to only be possible when player is on the ladder down
        if (IsKeyPressed(KEY_SPACE) && floorOn < NUM_OF_FLOORS-1)
        {
            //the player object needs to also change floors. idk best way to do this.
            //could be like: void ObjectHandler::transferObj(int objId, ObjectHandler* newHandler)
            //but thats a problem with the Id system
            //or the player could exist simultaneously in all object handlers if other objects don't need to move
            //or just have one object handler for the whole game and do floors some other way
            floorOn += 1;
        }

        wallSprites.clear(); //weird and inefficient. fix this
        for (Rectangle wall : floors[floorOn]->getWalls())
        {
            wallSprites.push_back(Sprite("wall", { wall.x, wall.y }, wall.y));
        }

        floors[floorOn]->getObjHandler()->tickAll(floors[floorOn]->getWalls());
        floors[floorOn]->getObjHandler()->renderAll();

        for ( int i = 0; i < wallSprites.size( ); i++ )
        {
           mainCamera.addToBuffer( &wallSprites[ i ] );
        }

        screenHandler.renderAll( );
    }

    return 0;
}
