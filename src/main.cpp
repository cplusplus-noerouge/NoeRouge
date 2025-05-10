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
    //MusicPlayer musicPlayer = MusicPlayer();
    //musicPlayer.setVolume( 0.5f );
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


       // musicPlayer.onTick();
      

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