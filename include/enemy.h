/*
* NoeRogue
* Enemy Class (inherits from Character class)
* Kaleb Flowers, Reese Edens
*
* TO-DO :
* - Add attack functionality?
* - Add AI behavior?
* - Include more interaction with player?
*/

#pragma once

#include <cstdlib>
#include "character.h"

// Struct to hold various stat-related properties of an enemy
struct Stats
{
   int health;        // Health points of the enemy
   int attackDamage;  // Amount of damage enemy can deal per attack
   int attackRange;   // Distance at which the enemy can hit the player
};

// Enemy class that inherits from Character
class Enemy : public Character
{
   private:

   int world_position[ 2 ];     // Position in the game world [x, y]
   int id;                    // Unique ID for the enemy

   public:
   Stats stats; // Struct holding the enemy's stats
   // Constructor to initialize enemy with ID, position, and stats
   Enemy( int id, int x, int y, Stats stats );

   void onTick( const std::vector<Rectangle> collidables );

   // Movement methods to change enemy's position
   void moveLeft( int distance );   // Move left by given distance
   void moveRight( int distance );  // Move right by given distance
   void moveUp( int distance );     // Move up by given distance
   void moveDown( int distance );   // Move down by given distance

   // Unused alternate constructor and attack method (possibly for future use)
   // Enemy(int id, Vector2 position, Vector2 size, int speed ) : Character( id, position, size, speed) { }
   // void attack( std::vector<Enemy*>& enemies );

   // Renders the enemy on screen
   void render( );

   // Reduces health when damage is taken, accounting for defense
   void takeDamage( int damage );

   // Checks if a player's position is within attack range of the enemy
   bool checkCollision( Vector2 playerPos, float attackRange ) const;

   // Getter for position (likely inherited from Character)
   Vector2 getPosition( ) const { return position; }

   // Getter for current health
   int getHealth( ) const { return stats.health; }
};