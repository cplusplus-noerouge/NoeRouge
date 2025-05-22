/* noeRouge - main.cpp
*  Worked on by: Devon, Reese, others */

#include <iostream>                 //Library for input and output streams
#include <vector>	                //Library for the vector data structure
#include <cstdlib>                  //Library with standard general utilities
#include <raylib.h>	                //Library with animation, rendering, interactive, and sound tools

#include "character.h" 		        //Class that enemy and player classes inherit from
#include "player.h"		            //Class that handles the player movement and functionality
#include "object.h"		            //Class that all game objects inherit from
#include "mapGen.h"		            //Class that creates the dungeon map
#include "textureLoader.h"      	//Class that loads textures from local directory
#include "sheetSprite.h"	        //Class that handles sprite sheets
#include "customCamera.h"	        //Class that handles rendering visual output to the screen
#include "screenHandler.h"          //Class that handles resolution and frame rate of the camera
#include "generateTileSprites.h"    //Class that generates sprites for every tile in the map
#include "audio.h"	                //Class that handles the functions needed to play audio
#include "globals.h"		        //Class that handles global variables
#include "mapHandler.h"             //Class that handles the map object

ScreenHandler screenHandler = ScreenHandler( );
// IMPORTANT! These are different versions of the camera with different zoom levels, 
//  uncomment the one you want.
CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 640.0f, 360.0f }, 2.0f );
//CustomCamera mainCamera = CustomCamera( Vector2 { 1280, 720.0f }, 1.0f );

MapHandler* mapHandler;
//Shows states for the screen. R.E
enum GameState {
   MENU,
   GAME,
   CREDITS
};
GameState gameState = MENU;

std::unordered_map<std::string, Texture2D> textureMap = {};

int main( )
{

   // Menu button properties R.E
   Rectangle startButton = { 430, 420, 380, 70 };  //x coord, y coord, length.x, and height of button
   Rectangle creditButton = { 520, 500, 200, 30 };

   bool playerDefeated = false;
   bool gameWin = false;
   bool gameEnd = false;
   bool closeWindow = false;
   bool gameStart = false;   //checks if the game has started or not R.E

   loadAllTextures( );
   screenHandler.cameras.push_back( &mainCamera );

   StaticSprite background( "spaceBackground", { 320, 180 }, -9999999 );
   InitAudioDevice( );
   MusicPlayer musicPlayer;
   musicPlayer.setVolume( 0.5f );


   std::vector<Sprite> tileSprites;

   while ( !WindowShouldClose( ) && !closeWindow )
   {
      if ( gameState == MENU )   //STATE ONE FOR GAME R.E
      {
         BeginDrawing( );
         ClearBackground( BLACK );
         // Creates image, as well as places it over hte title screen
         DrawTexturePro(                   
                         textureMap[ "planetTitle" ],
                         Rectangle { 0, 0, ( float ) textureMap[ "planetTitle" ].width, 
                                     ( float ) textureMap[ "planetTitle" ].height },
                         Rectangle { 0, 0, 1280, 720 },  // Destination = full window
                         Vector2 { 0, 0 },
                         0.0f,
                         WHITE
         );

         DrawRectangleRec( startButton, DARKPURPLE );   //drawing button for game start R.E
         // text, x offset, y offset, text size, color
         DrawText( "<START>", startButton.x + 40, startButton.y + 5,70, RAYWHITE ); 

         if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) 
              && CheckCollisionPointRec( GetMousePosition( ), startButton ) )
         {
            gameState = GAME;
         }
         DrawRectangleRec( creditButton, DARKPURPLE );    //drawing button for credits R.E
         DrawText( "<CREDITS>", creditButton.x+45 , creditButton.y + 5, 20, RAYWHITE );

         if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) 
              && CheckCollisionPointRec( GetMousePosition( ), creditButton ) )
         {
            std::cout << "Credits button pressed!" << std::endl;
            gameState = CREDITS;
         }
         EndDrawing( );
      }

      else if ( gameState == GAME )  //STATE TO START AND SHOW THE GAME R.E
      {
         if ( !gameStart )
         {

            mapHandler = new MapHandler;

            mapHandler->getCurrentFloor( )->getObjHandler( )
                ->createPlayer( mapHandler->getCurrentFloor( )->getLadderDownLocation( ) );
            

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

      else if ( gameState == CREDITS )  // shows credits page, hit m to retun to home to start the game. R.E
      {
         BeginDrawing( );
         ClearBackground( BLACK );
         // Creates image, as well as places it over the title screen
         DrawTexturePro(                   
                         textureMap[ "creditImage" ],
                         Rectangle { 0, 0, ( float ) textureMap[ "creditImage" ].width, 
                                     ( float ) textureMap[ "creditImage" ].height },
                         Rectangle { 0, 0, 1280, 720 },  // Destination = full window
                         Vector2 { 0, 0 },
                         0.0f,
                         WHITE
         );

         DrawText( "Press [M] to return to Main Menu", 420, 620, 27, RAYWHITE );

         if ( IsKeyPressed( KEY_M ) )
         {
            gameState = MENU;
         }
         EndDrawing( );
      }
   }

   CloseAudioDevice( );
   CloseWindow( );
   return 0;
}

          
