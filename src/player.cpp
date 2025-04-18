#include "player.h"
#include "object.h"
#include "enemy.h"
#include <iostream>

// Updates the player's movement direction based on key input
void Player::updateDirection( )
{
   // Move left when A is pressed
   if ( IsKeyDown( KEY_A ) )
   {
      direction.x = -1;
   }
   // Move right when D is pressed
   else if ( IsKeyDown( KEY_D ) )
   {
      direction.x = 1;
   }

   // Move down when S is pressed
   if ( IsKeyDown( KEY_S ) )
   {
      direction.y = 1;
   }
   // Move up when W is pressed
   else if ( IsKeyDown( KEY_W ) )
   {
      direction.y = -1;
   }
}

// Renders the player character on the screen
void Player::onRender( )
{
   // Get the player’s bounding box and draw a maroon rectangle
   Rectangle rectangle = bounds( );
   DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON );
}

// Creates a Player object and adds it to the object handler’s object list
class Player* ObjectHandler::createPlayer( Vector2 position, Vector2 size, int speed )
{
   // Create a new Player with a unique ID, position, size, and speed
   class Player* Player = new class Player( this->nextId++, position, size, speed );

   // Add the player to the list of all game objects
   this->allObjects.push_back( Player );
   this->numberOfObjects++;

   return Player;
}

// Defines the player's attack behavior
void Player::attack( std::vector<Enemy*>& enemies )
{
   // When SPACE key is pressed, attempt to attack nearby enemies
   if ( IsKeyPressed( KEY_SPACE ) )
   {
      for ( Enemy* enemy : enemies )
      {
         // If an enemy is within the player's attack range
         if ( enemy->checkCollision( position, attackRange ) )
         {
            // Apply damage to the enemy
            enemy->takeDamage( attackDamage );

            // Log the result
            std::cout << "Hit enemy! Health: " << enemy->getHealth( ) << std::endl;

            // Display a "HIT!" visual above the enemy
            Vector2 enemyPos = enemy->getPosition( );
            DrawText( "HIT!", enemyPos.x, enemyPos.y - 30, 20, RED );
         }
      }
   }
}
