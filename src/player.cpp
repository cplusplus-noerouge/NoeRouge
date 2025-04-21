#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include <iostream>
#include "enemy.h"


//class Player *objectHandler::createPlayer(Vector2 position, Vector2 size, int speed )
//{
//   Player* newPlayer = new Player( this->nextId++, position, size, speed );
//   this->allObjects.push_back( newPlayer );
//   this->numberOfObjects++;
//   return newPlayer;
//}

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

extern CustomCamera mainCamera;

void Player::onRender()
{
   mainCamera.setPosition( position ); // Updating the camera position should be moved to its own class or function later on
   sprite.update( position, position.y );
   mainCamera.addToBuffer( &sprite );
}

// Define the Player create function in the object handler
class Player* ObjectHandler::createPlayer( Vector2 position, Vector2 size, int speed )
{
   class Player* Player = new class Player( 0, position, size, speed ); //id for player is always 0
   allObjects[Player->getId()] = Player; //add <id, object*> to the map
   this->numberOfObjects++;
   return Player;
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

            // Display hit effect
            Vector2 enemyPos = enemy->getPosition( );
            DrawText( "HIT!", enemyPos.x, enemyPos.y - 30, 20, RED );
         }
      }

      EndDrawing( );
   }
}
