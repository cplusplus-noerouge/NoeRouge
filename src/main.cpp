/*
NoeRouge main file
Devon, everyone else who worked on this file put ur names here too so Vicki can grade
*/
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

void changeFloor(std::vector<Sprite>& wallSprites, Floor* floors[NUM_OF_FLOORS], int floorOn);  //loads the wall sprites for the new floor

int main( )
{
    // Setting up graphics
    loadAllTextures( );
    screenHandler.cameras.push_back( &mainCamera );

    Floor* floors[NUM_OF_FLOORS];
    for (int i = 0; i < NUM_OF_FLOORS; i++) {
        floors[i] = new Floor;
    }
    int floorOn = 0;                                         //the floor the player is on

    // Create a player so we can see it tick, and see it on screen
    Vector2 playerSpawnPosition = floors[floorOn]->getPlayerSpawn();
    floors[floorOn]->getObjHandler()->createPlayer(playerSpawnPosition, {TILE_SIZE, TILE_SIZE}, 300);

    std::vector<Sprite> wallSprites = {};                    //is changed when player changes floors
    for (Rectangle wall : floors[floorOn]->getWalls())       //put the wall sprites for the starting floor
    {
        wallSprites.push_back(Sprite("wall", { wall.x, wall.y }, wall.y));
    }

    while (!WindowShouldClose())
    {
        //TEMPORARY testing changing floors
        if (IsKeyPressed(KEY_SPACE) && floorOn < NUM_OF_FLOORS-1)
        {
            /*
            the player object needs to also change floors. idk best way to do this.
            could be like: void ObjectHandler::transferObj(int objId, ObjectHandler* newHandler)
            but thats a problem with the Id system
            or the player could exist simultaneously in all object handlers if other objects don't need to move
            or just have one object handler for the whole game and do floors some other way

            also changing floors needs to only be possible when player is on a ladder, up or down
            */
            floorOn += 1;
            changeFloor(wallSprites,floors,floorOn);
            std::cout << "\n moved from floor " << floorOn -1 << " to " << floorOn;
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

//loads the wall sprites for the new floor. prob will be added to -devon
void changeFloor(std::vector<Sprite>& wallSprites, Floor* floors[NUM_OF_FLOORS], int floorOn)
{
    wallSprites.clear();
    for (Rectangle wall : floors[floorOn]->getWalls())
    {
        wallSprites.push_back(Sprite("wall", { wall.x, wall.y }, wall.y));
    }
}