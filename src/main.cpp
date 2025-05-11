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
//Shows states for the screen. R.E
enum GameState {
   MENU,
   GAME
};
GameState gameState = MENU;

std::unordered_map<std::string, Texture2D> textureMap = {};

int main( )
{

   // Menu button properties R.E
   Rectangle startButton = { 540, 600, 200, 50 };

   bool playerDefeated = false;
   bool gameWin = false;
   bool gameEnd = false;
   bool closeWindow = false;
   bool gameStart = false;   //checks if the game has started or not R.E

   loadAllTextures( );
   screenHandler.cameras.push_back( &mainCamera );

   MusicPlayer musicPlayer;
   StaticSprite background( "spaceBackground", { 320, 180 }, -9999999 );

   std::vector<Sprite> tileSprites;

   while ( !WindowShouldClose( ) && !closeWindow )
   {
      if ( gameState == MENU )   //STATE ONE FOR GAME R.E
      {
         BeginDrawing( );
         ClearBackground( BLACK );
         DrawTexturePro(                   // Creates image, as well as places it over hte title screen
            textureMap[ "planetTitle" ],
            Rectangle { 0, 0, ( float ) textureMap[ "planetTitle" ].width, ( float ) textureMap[ "planetTitle" ].height },
            Rectangle { 0, 0, 1280, 720 },  // Destination = full window
            Vector2 { 0, 0 },
            0.0f,
            WHITE
         );
        
         DrawRectangleRec( startButton, DARKPURPLE );
         DrawText( "START", startButton.x + 45, startButton.y + 10, 30, RAYWHITE );

         if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition( ), startButton ) )
         {
            gameState = GAME;
         }

         EndDrawing( );
      }
      else if ( gameState == GAME )  //STATE TO START AND SHOW THE GAME R.E
      {
         if ( !gameStart )
         {
            InitAudioDevice( );
            musicPlayer.setVolume( 0.5f );

            mapHandler = new MapHandler;
           
            mapHandler->getCurrentFloor( )->getObjHandler( )->createPlayer( mapHandler->getCurrentFloor( )->getLadderDownLocation( ) );
            

            gameStart = true;
         }

         float dT = GetFrameTime( );

         tileSprites = mapHandler->getCurrentFloor( )->getTileSprites( );

         mapHandler->tickAndRender( );

         for ( auto& tile : tileSprites )
         {
            mainCamera.addToBuffer( &tile );
         }

         mainCamera.addToBuffer( &background );

         screenHandler.renderAll( ); // <- this already wraps Begin/EndDrawing()

         musicPlayer.onTick( );

         //procedure for ending the game, either upon clearing the last floor or the player being defeated   -Andrew
         if ( ( gameWin || playerDefeated ) && !gameEnd )
         {
            mapHandler->endGame( gameWin );
            gameEnd = true;
         }

         //check if the player presses the key to close the game from end screen after the game is over     -Andrew
         if ( gameEnd )
         {
            if ( IsKeyPressed( KEY_P ) )
            {
               closeWindow = true;
            }
         }
         if ( IsKeyPressed( KEY_X ) ) gameWin = true;
         if ( IsKeyPressed( KEY_Z ) ) playerDefeated = true;
      }

   }

   CloseAudioDevice( );
   CloseWindow( );
   return 0;
}

          
