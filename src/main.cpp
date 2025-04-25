/*
NoeRouge main file
Devon,Reese everyone else who worked on this file put ur names here too so Vicki can grade
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
const int NUM_OF_FLOORS = 4; //the number of floors in the game   

ScreenHandler screenHandler = ScreenHandler( );
// IMPORTANT! These are different versions of the camera with different zoom levels, uncomment the one you want.
//CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
CustomCamera mainCamera = CustomCamera( Vector2 { 640.0f, 360.0f }, 2.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 1280, 720.0f }, 1.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

void changeFloor(std::vector<Sprite>& wallSprites, Floor* floors[NUM_OF_FLOORS], int& floorOn, int changeVal);  //changes the floor that the player is on

int main( )
{
    // Setting up graphics
    loadAllTextures( );
    screenHandler.cameras.push_back( &mainCamera );

    // Make the floors
    Floor* floors[NUM_OF_FLOORS];
    for (int i = 0; i < NUM_OF_FLOORS; i++) {
        floors[i] = new Floor;
    }
    int floorOn = 0;
    std::vector<Enemy*> enemies;      //the floor the player is on
    floors[ floorOn ]->getObjHandler( )->createEnemy( );


    // Create a player so we can see it tick, and see it on screen
    Vector2 playerSpawnPosition = floors[floorOn]->getPlayerSpawn( );
    Vector2 enemySpawnPosition = floors[ floorOn ]->getEnemySpawn( );

    // Add enemies to the vector after creating them
    Enemy* enemy = floors[ floorOn ]->getObjHandler( )->createEnemy( enemySpawnPosition,
                                                                    { TILE_SIZE, TILE_SIZE }, 300 );
    enemies.push_back( enemy );

    floors[ floorOn ]->getObjHandler()->createPlayer(playerSpawnPosition, 
                                                      { TILE_SIZE, TILE_SIZE }, 300 );

    // Declare a vector to hold enemy pointers
    
    std::vector<Sprite> wallSprites = {};                    //is changed when player changes floors
    for (Rectangle wall : floors[floorOn]->getWalls())       //put the wall sprites for the starting floor
    {
        wallSprites.push_back(Sprite("wall", { wall.x, wall.y }, wall.y));
    }

    while (!WindowShouldClose())

    { 
        //TEMPORARY testing changing floors
        if (IsKeyPressed(KEY_RIGHT_ALT) && floorOn < NUM_OF_FLOORS-1)
        {
            /*
            the player object needs to also change floors. idk best way to do this.
            could be like: void ObjectHandler::transferObj(int objId, ObjectHandler* newHandler)
            but thats a problem with the Id system
            or the player could exist simultaneously in all object handlers if other objects don't need to move
            or just have one object handler for the whole game and do floors some other way

            also changing floors needs to only be possible when player is on a ladder, up or down
            */
            //floorOn += 1;
            changeFloor(wallSprites,floors,floorOn, 1);
            std::cout << "\n moved from floor " << floorOn -1 << " to " << floorOn;
        }
 
        floors[floorOn]->getObjHandler()->tickAll(floors[floorOn]->getWalls());
        floors[floorOn]->getObjHandler()->renderAll();

        for ( int i = 0; i < wallSprites.size( ); i++ )
        {
           mainCamera.addToBuffer( &wallSprites[ i ] );
        } 
        
        if ( IsKeyPressed( KEY_SPACE ) )  // player attacks when space is pressed
        {
           // created a pointer to the player object in the current floor's object handler
           Player* player = static_cast< Player* >( floors[ floorOn ]->getObjHandler( )->getObject( 0 ) );
  
           player->attack( enemies ); // Attack with a range of 50 and damage of 10
        }

        screenHandler.renderAll( );
    }

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------
* changeFloor() changes the players current floor
* - devon
* param vector<Sprite>& wallSprites: sprites of the walls. edited by this function
* param Floor* floors[NUM_OF_FLOORS]: array of all the floors in the game
* param int& floorOn: the index of the floor the player is currently on. edited by this function
* param int changeVal: the amount by which the floor index is changed. exe -1 is down a floor, and 1 is up a floor
* return: the data in wallSprites and floorOn is altered
------------------------------------------------------------------------------------------------------------------*/
void changeFloor(std::vector<Sprite>& wallSprites, Floor* floors[NUM_OF_FLOORS], int& floorOn, int changeVal)
{
    //transfer player to new object handler
    ObjectHandler* oldHandler = floors[floorOn]->getObjHandler();
    floorOn+= changeVal;
    ObjectHandler* newHandler = floors[floorOn]->getObjHandler();
    oldHandler->transferObject(0, *newHandler); //player id is always 0

    //TODO set player location to the new floors ladderUp

    //make new wall sprites
    wallSprites.clear();
    for (Rectangle wall : floors[floorOn]->getWalls())
    {
        wallSprites.push_back(Sprite("wall", { wall.x, wall.y }, wall.y));
    }
}