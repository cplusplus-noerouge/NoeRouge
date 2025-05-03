/*
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Thomas
*/

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

    dodge();
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

/*-----------------------------------------------------------------------------------------------------------------------------
* takeDamage( )
* Ethan Sheffield
* @brief : Decrements player health based off enemy damage and checks for player death.
* @param int damage : amount of incoming damage to decrement from health
* @param bool &playerDefeated : reference to a bool value, if player has been defeated or not.
* @return : none
* -----------------------------------------------------------------------------------------------------------------------------
*/
void Player::takeDamage( int damage, bool &playerDefeated )
{
   health -= damage;
   std::cout << "Player taken damage!";
   if ( health <= 0 )
   {
      std::cout << "Player defeated!" << std::endl;
      playerDefeated = true;
   }
}

/*-----------------------------------------------------------------------------------------------------------------------------
**dodge()
**Thomas Orozco
**Increases players speed by 1.4 times for 1 second when left shift is pressed and prevents user from doing it for another 2 seconds
** int dodgeCooldown, decriments each frame and is used to measure cooldown
**-----------------------------------------------------------------------------------------------------------------------------
*/
void Player::dodge()
{
   if(IsKeyPressed(KEY_LEFT_SHIFT))
   {
      if(dodgeCooldown <= 0)
      {
         dodgeCooldown = 3 * GetFPS(); //Change what dodgeCooldown get set to alter cooldown length, remember it is decrimented each frame.
      }
   }

   if (dodgeCooldown > 2 * GetFPS()) // Change lenght of time dodging happens by altering what dodgeCooldown is compared to, lower is longer.
      {
         direction.x = direction.x * 1.4; //Alter speed of dodging by changing numbers direction is multiplied by, * 1 is base walking speed
         direction.y = direction.y * 1.4;
      }


   if(dodgeCooldown > 0)
   {
      dodgeCooldown--;
   }
   
}
