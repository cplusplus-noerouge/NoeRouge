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
#include "globals.h"
#include "maphandler.h"

ScreenHandler screenHandler = ScreenHandler( );
// IMPORTANT! These are different versions of the camera with different zoom levels, uncomment the one you want.
CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 640.0f, 360.0f }, 2.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 1280, 720.0f }, 1.0f );

std::unordered_map<std::string, Texture2D> textureMap = {};

int main( )
{
    // Setting up graphics
    loadAllTextures( );
    screenHandler.cameras.push_back( &mainCamera );
    //  Audio
    InitAudioDevice();
    MusicPlayer musicPlayer = MusicPlayer();


    MapHandler* mapHandler = new MapHandler;
    Floor* currentFloor = mapHandler->getCurrentFloor( );
    currentFloor->getObjHandler( )->createPlayer( currentFloor->getLadderDownLocation( ) );
    std::vector<Sprite> tileSprites = currentFloor->getTileSprites( );
    

    StaticSprite background = StaticSprite( "spaceBackground", { 320, 180 }, -9999999 );

    while (!WindowShouldClose())
    { 
       float dT = GetFrameTime( );

       if ( Controls::ladderUp( ) ) //up
       {
          mapHandler->changeFloor( true );
       }
       if ( Controls::ladderDown( ) ) //down
       {
          mapHandler->changeFloor( false );
       }

       currentFloor->getObjHandler( )->tickAll( currentFloor->getWalls( ) );
       currentFloor->getObjHandler( )->renderAll( );

        currentFloor = mapHandler->getCurrentFloor( );
        currentFloor->getObjHandler( )->tickAll( currentFloor->getWalls( ) );
        currentFloor->getObjHandler( )->renderAll( );
        tileSprites = currentFloor->getTileSprites( );

        for ( int i = 0; i < tileSprites.size( ); i++ )
        {
           mainCamera.addToBuffer( &tileSprites[ i ] );
        }

        mainCamera.addToBuffer( &background );

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
//void changeFloor(std::vector<Sprite>& tileSprites, Floor* floors[Settings::NUM_OF_FLOORS], int& floorOn, int changeVal)
//{
//    //check that the new floor exists
//    if (floorOn + changeVal < 0 || floorOn + changeVal >= Settings::NUM_OF_FLOORS)
//    {
//        std::cout << "\nTried to change floors from " << floorOn << " to " << floorOn + changeVal
//                  << " but didn't because floor " << floorOn + changeVal << " doesn't exist.";
//        return;
//    }
//
//    //transfer player to new object handler
//    ObjectHandler* oldHandler = floors[floorOn]->getObjHandler();
//    floorOn+= changeVal;
//    ObjectHandler* newHandler = floors[floorOn]->getObjHandler();
//    oldHandler->transferObject(0, *newHandler); //player id is always 0
//
//    //set player location to the new floors ladder
//    Player* player = dynamic_cast<Player*>(newHandler->getObject(0));
//    if (changeVal < 0) //going down, move player position to ladderup
//    {
//        Vector2 ladderPosition = floors[floorOn]->getLadderUpLocation();
//        player->setPosition(ladderPosition);
//    }
//    if (changeVal > 0) //going up, move player position to ladderdown
//    {
//        Vector2 ladderPosition = floors[floorOn]->getLadderDownLocation();
//        player->setPosition(ladderPosition);
//    }
//
//    //make new tile sprites
//    tileSprites = generateTileSprites( floors[ floorOn ] );
//    std::cout << "\n Moved from floor " << floorOn - changeVal << " to " << floorOn;
//}