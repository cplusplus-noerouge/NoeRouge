/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Adam
* The player class is a child class of Character that represents the playable character.
----------------------------------------------------------------------------------------------------------------------------------------*/

#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include <iostream>
#include "enemy.h"

using namespace std;

extern CustomCamera mainCamera;   //Camera view of the map

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Class constructor based on object ID.
----------------------------------------------------------------------------------------------------------------------------------------*/
Player::Player( int id ) : Character( id ), attackRange( 20.0f ), attackDamage( 1 )
{
   sprite = Sprite( "player", position, position.y );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Parameterized Class constructor.
----------------------------------------------------------------------------------------------------------------------------------------*/
Player::Player( int id, Vector2 _position, Vector2 _size, int _speed )
   : Character( id, _position, _size, _speed ), attackRange( 20.0f ), attackDamage( 1 )
{
   sprite = Sprite( "player", position, position.y );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onRender( )
* @brief : Updates camera position, updates sprite, and renders the character on screen.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::onRender( )
{
   mainCamera.setPosition( position ); // Updating the camera position should be moved to its own class or function later on
   sprite.update( position, position.x );
   mainCamera.addToBuffer( &sprite );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* attack( )
* @brief : Updates camera position and updates sprite, renders the character on screen.
* @param vector<Enemy*>& enemies : The collection of enemies to check for collision with.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::attack( std::vector<Enemy*>& enemies )
{
   if ( IsKeyPressed( KEY_SPACE ) )

   {  // Attack with SPACE
      BeginDrawing( );  // Ensure you're inside a drawing context

      for ( Enemy* enemy : enemies )
      {
         if ( enemy->checkCollision( position, attackRange ) )
         {
            enemy->takeDamage( attackDamage );
            std::cout << "Hit enemy! Health: " << enemy->getHealth( ) << std::endl;

            //// Calculate the position to display the hit effect
            //Vector2 enemyPosition = enemy->getPosition( );
            //Vector2 position = { enemyPosition.x - 20, enemyPosition.y - 20 }; // Adjust as needed for centering text
            // Set the font size and color for the hit effect
            // Display hit effect
            Vector2 position = enemy->getPosition( );
            DrawText( "HIT!", position.x + 30, position.y + 30, 30, RAYWHITE );
         }
      }
      cout << "ATTACKING" << endl;
      EndDrawing( );
   }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* createPlayer( )
* By Ben Aguilon
* @brief : Object creation function defined in ObjectHandler.
* @param Vector2 position : Initial position of player.
* @param Vector2 size : Initial size of player.
* @param int speed : Initial speed of player.
* @return Player* : Pointer to the created Player object.
----------------------------------------------------------------------------------------------------------------------------------------*/
class Player* ObjectHandler::createPlayer( Vector2 position, Vector2 size, int speed )
{
   class Player* Player = new class Player( 0, position, size, speed ); //id for player is always 0
   allObjects[ Player->getId( ) ] = Player; //add <id, object*> to the map
   this->numberOfObjects++;
   return Player;
}