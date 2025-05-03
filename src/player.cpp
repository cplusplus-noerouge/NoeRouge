
/*
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Adam


* Reese Edens, Kaleb Flowers
* Player Class (inherits from Character class)
* Player class represents the player character in the game.
* It handles player movement, rendering, and attacking functionality.
*/

#include <iostream>
#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include "enemy.h"
#include "audio.h"

using namespace std;


extern CustomCamera mainCamera;   //Camera view of the map

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Class constructor based on object ID.
----------------------------------------------------------------------------------------------------------------------------------------*/
Player::Player( int id ) : Character( id ), attackRange( 20.0f ), attackDamage( 1 )
{
   sprite = Sprite( "player", position, position.y );
}


void Player::onTick(const std::vector<Rectangle> colliders)
{
    Character::onTick(colliders);

    walkTimer += GetFrameTime();

    if (walkTimer > WALK_TIMER_MAX && (direction.x != 0 || direction.y != 0))
    {
        PlaySound(sfx["walkLeft.wav"]);
        walkTimer = 0.0f;
    }
}

void Player::onRender()
{
   mainCamera.setPosition( position ); // Updating the camera position should be moved to its own class or function later on
      // Animating the player
   animation.onTick( );
      // Freezing the animation at frame 1 if the player isn't moving
      // WARNING! This logic will need to be revised when implementing other animations that aren't just for walking.
   if ( Vector2Equals( direction, { 0 , 0 } ) )
   {
      animation.reset( );
   }
   sprite.setTexture( "playerWalk" + std::to_string( animation.getFrame( ) ) );

      // Setting the position referenced on the sheet based on the direction the plaer is facing
   if ( direction.x < 0 )
   {
      sprite.setSourceRect( { 0, 0, 16, 16 } );
   }
   else if ( direction.x > 0 )
   {
      sprite.setSourceRect( { 32, 0, 16, 16 } );
   }
   else if ( direction.y >= 0 )
   {
      sprite.setSourceRect( { 16, 0, 16, 16 } );
   }
   else
   {
      sprite.setSourceRect( { 48, 0, 16, 16 } );
   }

   sprite.update( position, position.y );
   mainCamera.addToBuffer( &sprite );

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
     // BeginDrawing( );  // Ensure you're inside a drawing context

      for ( Enemy* enemy : enemies )
      {
         if ( enemy->checkCollision( position, attackRange ) )
         {
            cout << "ATTACKING" << endl;
            PlaySound(sfx["laserShoot.wav"]);
            enemy->takeDamage( attackDamage );

            

            //// Calculate the position to display the hit effect
            Vector2 enemyPosition = enemy->getPosition( );
            Vector2 position = { enemyPosition.x - 20, enemyPosition.y - 20 }; // Adjust as needed for centering text
            // Set the font size and color for the hit effect
            // Display hit effect

           // Vector2 position = enemy->getPosition( );
            DrawText( "HIT!", position.x + 30, position.y + 30,30,RAYWHITE);

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
   PlaySound(sfx["playerDamaged.mp3"]);

   health -= damage;
   std::cout << "Player taken damage!";
   if ( health <= 0 )
   {
      std::cout << "Player defeated!" << std::endl;
      playerDefeated = true;
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