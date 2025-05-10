/*
NoeRouge main file
Devon, Reese, others
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

MapHandler* mapHandler;

std::unordered_map<std::string, Texture2D> textureMap = {};

int main( )
{
    // Setting up graphics
    loadAllTextures( );
    screenHandler.cameras.push_back( &mainCamera );
    //  Audio
    InitAudioDevice();
    MusicPlayer musicPlayer = MusicPlayer();
    musicPlayer.setVolume( 0.5f );
    bool playerDefeated = false;                             //manages whether or not the player has been defeated
    bool gameWin = false;                                    //manages whether or not the player has won the game
    bool gameEnd = false;                                    //manages whether or not either game over/win scenario has been checked and the respective screen is up
    bool closeWindow = false;                                //lcv

    mapHandler = new MapHandler;
    Floor* currentFloor = mapHandler->getCurrentFloor( );
    currentFloor->getObjHandler( )->createPlayer( currentFloor->getLadderDownLocation( ) );
    std::vector<Sprite> tileSprites = currentFloor->getTileSprites( );
    

    StaticSprite background = StaticSprite( "spaceBackground", { 320, 180 }, -9999999 );

    while (!WindowShouldClose() && !closeWindow)
    { 
       float dT = GetFrameTime( );

       currentFloor->getObjHandler( )->tickAll( currentFloor->getWalls( ) );
       currentFloor->getObjHandler( )->renderAll( );

        currentFloor = mapHandler->getCurrentFloor( );
        
        mapHandler->tickAndRender( );

        tileSprites = currentFloor->getTileSprites( );
      

        for ( int i = 0; i < tileSprites.size( ); i++ )
        {
           mainCamera.addToBuffer( &tileSprites[ i ] );
        }

        mainCamera.addToBuffer( &background );

        screenHandler.renderAll( );

        musicPlayer.onTick();
        
        //procedure for ending the game, either upon clearing the last floor or the player being defeated   -Andrew
        if ((gameWin || playerDefeated) && !gameEnd)
        {
            mapHandler->endGame(gameWin);
        }

        //check if the player presses the key to close the game from end screen after the game is over     -Andrew
        if (gameEnd)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                closeWindow = true;
            }
        }

        //temporary checks for win and lose conditions
        if (IsKeyPressed(KEY_X))
        {
            gameWin = true;
        }
        if (IsKeyPressed(KEY_Z))
        {
            playerDefeated = true;
        }
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

/*---------------------------------------------------------------------------------------------------------------------
* endGame() displays a game over/win screen
* - Andrew
* param bool win: whether or not the win condition has been met
* this function can only be reached by either of the win or lose conditions, or both, being true, 
*    so only one needs to be checked
* return: sets gameEnd to true after displaying game over screen
---------------------------------------------------------------------------------------------------------------------*/
//void endGame(bool win)
//{
//    if (win)
//    {
//        winScreen.render(Vector2{ 0,0 });
//    }
//    else
//    {
//        loseScreen.render(Vector2{ 0,0 });
//    }
//    gameEnd = true;
//}