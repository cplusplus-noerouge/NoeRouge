/*
* NoeRogue
* Enemy Cpp
* Kaleb Flowers, Reese Edens
*
* TO-DO :
* 
*/

#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "object.h"
#include "character.h"
#include "player.h"
#include "enemies.h"
#include <raymath.h>

// Constructor for Enemy class
// Initializes the enemy's ID, stats, and position in the world
Enemy::Enemy( int id, int x, int y, Stats stats )
   : Character( id, { static_cast< float >( x ), static_cast< float >( y ) }, { 50.0f, 50.0f }, stats.speed ), // Call Character constructor
   id( id ), stats( stats )
{
   world_position[ 0 ] = x;
   world_position[ 1 ] = y;
}


// Called every frame to update the enemy's logic and behavior
void Enemy::onTick( const std::vector<Rectangle> collidables )
{
   // Update movement direction (likely handled by inherited Character method)
   updateDirection( );

   // Calculate velocity based on direction and frame time
   velocity = Vector2Scale( direction, speed * GetFrameTime( ) );

   // Update position by adding velocity
   position = Vector2Add( position, velocity );

   // Check and resolve collisions with game world objects
   updateCollisions( collidables );
}

// Moves the enemy left by the specified distance
void Enemy::moveLeft( int distance )
{
   world_position[ 0 ] -= distance;
}

// Moves the enemy right by the specified distance
void Enemy::moveRight( int distance )
{
   world_position[ 0 ] += distance;
}

// Moves the enemy up by the specified distance
void Enemy::moveUp( int distance )
{
   world_position[ 1 ] -= distance;
}

// Moves the enemy down by the specified distance
void Enemy::moveDown( int distance )
{
   world_position[ 1 ] += distance;
}

// Draws the enemy on the screen
void Enemy::render( )
{
   // Draw the enemy as a red rectangle
   DrawRectangle( world_position[ 0 ], world_position[ 1 ], 50, 50, RED );

   // Draw the enemy's health above the rectangle
   DrawText( TextFormat( "HP: %d", stats.health ), world_position[ 0 ], world_position[ 1 ] - 20, 12, WHITE );
}

// Applies damage to the enemy, factoring in defense
void Enemy::takeDamage( int damage )
{
   // Reduce incoming damage by enemy's defense
   int effectiveDamage = damage - stats.defense;

   // Only apply damage if it's greater than zero
   if ( effectiveDamage > 0 )
   {
      stats.health -= effectiveDamage;
   }

   // Check for death
   if ( stats.health <= 0 )
   {
      std::cout << "Enemy defeated!" << std::endl;
   }

   // Draws the enemy's bounds in red (debug or visual feedback)
   Rectangle rectangle = bounds( );
   DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, RED );
}

// Checks if the player is within the enemy's attack range
bool Enemy::checkCollision( Vector2 playerPos, float attackRange ) const
{
   float dx = playerPos.x - world_position[ 0 ];
   float dy = playerPos.y - world_position[ 1 ];
   float distance = sqrt( dx * dx + dy * dy );

   // Returns true if the distance is less than the attack range
   return distance < attackRange;
}

// Returns the enemy's current position as a Vector2
Vector2 Enemy::getPosition( ) const
{
   return { static_cast< float >( world_position[ 0 ] ), static_cast< float >( world_position[ 1 ] ) };
}
