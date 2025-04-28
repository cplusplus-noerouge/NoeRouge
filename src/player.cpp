/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Adam
----------------------------------------------------------------------------------------------------------------------------------------*/

#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include <iostream>
#include "enemy.h"

using namespace std;

extern CustomCamera mainCamera;

Player::Player( int id ) : Character( id ), attackRange( 20.0f ), attackDamage( 1 )
{
   sprite = Sprite( "player", position, position.y );
}

Player::Player( int id, Vector2 _position, Vector2 _size, int _speed )
   : Character( id, _position, _size, _speed ), attackRange( 20.0f ), attackDamage( 1 )
{
   sprite = Sprite( "player", position, position.y );
}

void Player::onRender( )
{
   mainCamera.setPosition( position ); // Updating the camera position should be moved to its own class or function later on
   sprite.update( position, position.x );
   mainCamera.addToBuffer( &sprite );
}

void Player::updateDirection()
{
    if (IsKeyDown(KEY_A))
    {
        direction.x = -1;
    }
    else if (IsKeyDown(KEY_D))
    {
        direction.x = 1;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y = 1;
    }
    else if (IsKeyDown(KEY_W))
    {
        direction.y = -1;
    }
}

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
            Vector2 world_position = enemy->getPosition( );
            DrawText( "HIT!", world_position.x, world_position.y,45,RAYWHITE);
         }
      }
      cout << "ATTACKING" << endl;
      EndDrawing( );
   }
}

// Define the Player create function in the object handler
class Player* ObjectHandler::createPlayer( Vector2 position, Vector2 size, int speed )
{
   class Player* Player = new class Player( 0, position, size, speed ); //id for player is always 0
   allObjects[ Player->getId( ) ] = Player; //add <id, object*> to the map
   this->numberOfObjects++;
   return Player;
}
