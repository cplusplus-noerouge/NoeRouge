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
#include "enemy.h"
#include <raymath.h>
using namespace std;

// Constructor for Enemy class
// Initializes the enemy's ID, stats, and position in the world
Enemy::Enemy( int id, int x, int y, Stats stats )
   : Character( id, { static_cast< float >( x ), static_cast< float >( y ) }, { 50.0f, 50.0f }, stats.speed ), // Call Character constructor
   id( id ), stats( stats )
{
   world_position[ 0 ] = x;
   world_position[ 1 ] = y;
}

Enemy* ObjectHandler::createEnemy( Vector2 world_position, Vector2 size, int speed )
{
   Stats enemyStats = { 3, 1, 25, 5}; // stats: hp, damage, range, speed
   Enemy* newEnemy = new Enemy( nextId++, world_position.x, world_position.y, enemyStats );
   allObjects[ newEnemy->getId( ) ] = newEnemy; // Add <id, object*> to the map
   this->numberOfObjects++;
   return newEnemy;

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
   // Reduce health by damage amount, ensuring it doesn't go below zero
   stats.health -= damage;
   if ( stats.health < 0 )
   {
      stats.health = 0; // Ensure health doesn't go below zero
   }
   
   // Check for death
   if ( stats.health <= 0 )
   {
      stats.health = 0; // Ensure health doesn't go below zero
      std::cout << "Enemy is dead!" << std::endl;
      return; // Exit if the enemy is already dead
   }
   cout << "Enemy took " << damage << " damage!" << endl;
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

//// Returns the enemy's current position as a Vector2
//Vector2 Enemy::getPosition( ) const
//{
//   return { static_cast< float >( world_position[ 0 ] ), static_cast< float >( world_position[ 1 ] ) };
//}