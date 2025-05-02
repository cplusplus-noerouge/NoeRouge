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
#include "sheetSprite.h"
#include "customCamera.h"
#include "screenHandler.h"
#include "generateTileSprites.h"
#include "audio.h"

constexpr int FPS = 60;
constexpr int PLAYER_SPEED = 300;
const int NUM_OF_FLOORS = 4; //the number of floors in the game   

ScreenHandler screenHandler = ScreenHandler( );
// IMPORTANT! These are different versions of the camera with different zoom levels, uncomment the one you want.
CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 640.0f, 360.0f }, 2.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 1280, 720.0f }, 1.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

void changeFloor(std::vector<Sprite>& wallSprites, Floor* floors[NUM_OF_FLOORS], int& floorOn, int changeVal);  //changes the floor that the player is on

int main( )
{
    // Setting up graphics
    loadAllTextures( );
    screenHandler.cameras.push_back( &mainCamera );
    //  Audio
    InitAudioDevice();
    MusicPlayer musicPlayer = MusicPlayer();
    musicPlayer.setVolume( 0.5f );

    Floor* floors[NUM_OF_FLOORS];
    for (int i = 0; i < NUM_OF_FLOORS; i++) {
        floors[i] = new Floor;
    }
    int floorOn = 0;
   
    // Create a player so we can see it tick, and see it on screen
   //Vector2 playerSpawnPosition = floors[floorOn]->getPlayerSpawn( );
  // Vector2 enemySpawnPosition = floors[ floorOn ]->getEnemySpawn( );

    //// Set the player spawn position to the ladder up on the first floor
    Vector2 playerSpawnPosition = { 100, 100 }; // Example spawn position, change as needed
    //  // Set the enemy spawn position to the ladder down on the first floor
    Vector2 enemySpawnPosition = { 110, 110 }; // Example spawn position, change as needed
   
      // Create the player object in the object handler of the current floor
    floors[ floorOn ]->getObjHandler( )->createPlayer( playerSpawnPosition, { TILE_SIZE, TILE_SIZE }, PLAYER_SPEED );

    // Add enemies to the vector after creating them
    //change this "floorOn" to change the layer enemy spawns on 
    Enemy* enemy = floors[ floorOn ]->getObjHandler( )->createEnemy( enemySpawnPosition,
                                                                    { TILE_SIZE, TILE_SIZE}, 300 );  

    // Add the following declaration at the top of the file, near other global variables.  
    std::vector<Enemy*> enemies; // Declare the enemies vector to store enemy pointers.
    std::vector<Sprite> wallSprites = {};                    //is changed when player changes floors
    // Declare a vector to hold enemy pointers
    enemies.push_back( enemy );
    std::vector<Sprite> tileSprites = generateTileSprites( floors[ floorOn ] );

    while (!WindowShouldClose())

    { 
        //TEMPORARY testing changing floors
        //TODO changing floors needs to only be possible when player is on a ladder, up or down
        if (IsKeyPressed(KEY_RIGHT_BRACKET)) //up
        {
            changeFloor( tileSprites,floors,floorOn, 1);
        }
        if (IsKeyPressed(KEY_LEFT_BRACKET)) //down
        {
            changeFloor( tileSprites, floors, floorOn, -1);
        }
 
        floors[floorOn]->getObjHandler()->tickAll(floors[floorOn]->getWalls());
        floors[floorOn]->getObjHandler()->renderAll();

        for ( int i = 0; i < tileSprites.size( ); i++ )
        {
           mainCamera.addToBuffer( &tileSprites[ i ] );
        } 
        //**Reese** added player attack, outputs "ATTACKING" to console when space is pressed
        if ( IsKeyPressed( KEY_SPACE ) )  // player attacks when space is pressed
        {
           // created a pointer to the player object in the current floor's object handler
           Player* player = static_cast< Player* >( floors[ floorOn ]->getObjHandler( )->getObject( 0 ) );
  
           player->attack( enemies ); // Attack with a range of 50 and damage of 10
        }

        screenHandler.renderAll( );

        musicPlayer.onTick();
    }

    CloseAudioDevice();

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------
* changeFloor() changes the players current floor.
* - devon
* param vector<Sprite>& wallSprites: sprites of the walls. edited by this function
* param Floor* floors[NUM_OF_FLOORS]: array of all the floors in the game
* param int& floorOn: the index of the floor the player is currently on. edited by this function
* param int changeVal: the amount by which the floor index is changed. exe -1 is down a floor, and 1 is up a floor
* return: the data in wallSprites and floorOn is altered
------------------------------------------------------------------------------------------------------------------*/
void changeFloor(std::vector<Sprite>& tileSprites, Floor* floors[NUM_OF_FLOORS], int& floorOn, int changeVal)
{
    //check that the new floor exists
    if (floorOn + changeVal < 0 || floorOn + changeVal >= NUM_OF_FLOORS)
    {
        std::cout << "\nTried to change floors from " << floorOn << " to " << floorOn + changeVal
                  << " but didn't because floor " << floorOn + changeVal << " doesn't exist.";
        return;
    }

    //transfer player to new object handler
    ObjectHandler* oldHandler = floors[floorOn]->getObjHandler();
    floorOn+= changeVal;
    ObjectHandler* newHandler = floors[floorOn]->getObjHandler();
    oldHandler->transferObject(0, *newHandler); //player id is always 0

    //set player location to the new floors ladder
    Player* player = dynamic_cast<Player*>(newHandler->getObject(0));
    if (changeVal < 0) //going down, move player position to ladderup
    {
        Vector2 ladderPosition = floors[floorOn]->getLadderUpLocation();
        player->setPosition(ladderPosition);
    }
    if (changeVal > 0) //going up, move player position to ladderdown
    {
        Vector2 ladderPosition = floors[floorOn]->getLadderDownLocation();
        player->setPosition(ladderPosition);
    }

    //make new tile sprites
    tileSprites = generateTileSprites( floors[ floorOn ] );
    std::cout << "\n Moved from floor " << floorOn - changeVal << " to " << floorOn;
}