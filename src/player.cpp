/*
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan


* Reese Edens, Kaleb Flowers
* Player Class (inherits from Character class)
* Player class represents the player character in the game.
* It handles player movement, rendering, and attacking functionality.
*/


#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include <iostream>
#include "enemy.h"

using namespace std;


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
   sprite.update( position,position.x);
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
     // BeginDrawing( );  // Ensure you're inside a drawing context

      for ( Enemy* enemy : enemies )
      {
         if ( enemy->checkCollision( position, attackRange ) )
         {
            enemy->takeDamage( attackDamage );
            std::cout << "Hit enemy! Health: " << enemy->getHealth( ) << std::endl;
            
            //// Calculate the position to display the hit effect
            Vector2 enemyPosition = enemy->getPosition( );
            Vector2 position = { enemyPosition.x - 20, enemyPosition.y - 20 }; // Adjust as needed for centering text
            // Set the font size and color for the hit effect
            // Display hit effect
           // Vector2 position = enemy->getPosition( );
            DrawText( "HIT!", position.x + 30, position.y + 30,30,RAYWHITE);
         }
      }
      cout << "ATTACKING" << endl;
     EndDrawing( );
   }
}
 /*------------------------------------------------------------------------------------------------------------------
* defend() Allows the player to defend against enemy attacks.
* - Kaleb Flowers
* param
* return:
------------------------------------------------------------------------------------------------------------------*/
   void Player::defend( std::vector<Enemy*>&enemies )
   {

      if ( IsKeyDown( KEY_LEFT_SHIFT ) )
      {
         BeginDrawing( );  // remove ( leftover code) 
         for ( Enemy* enemy : enemies )
         {
            if ( enemy->checkCollision( position, attackRange ) )
            {
               //stop player movement
               //stop incoming damage from enemy 
            }
         }
         std::cout << "Defending against enemy attack!";
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
