/*
* NoeRogue
* Enemy Class (inherits from Character class)
* Kaleb Flowers, Reese Edens
*
* TO-DO :
* - Add attack functionality?
    // Add the missing method declaration in the Enemy class  
   
* - Add AI behavior?
* - Include more interaction with player?
*/

#pragma once
#include "character.h"

// Struct to hold various stat-related properties of an enemy
struct Stats
{
   int health;        // Health points of the enemy
   int attackDamage;  // Amount of damage enemy can deal per attack
   int attackRange;   // Distance at which the enemy can hit the player
   int speed;         //character speed
};

// Change the `world_position` array from private to public or provide a getter method for access.  
class Enemy : public Character  
{  
private:  
   int id; // Unique ID for the enemy  
   bool damageBlocked = false; // Tracks if damage is blocked

public:  
   int world_position[2]; // Make this public for accessibility  

   Stats stats; // Struct holding the enemy's stats  

   // Constructor to initialize enemy with ID, position, and stats  
   Enemy(int id, Vector2 _position,Vector2 _size, Stats stats) ;  

   Enemy( int id, int x, int y, Stats stats );



   void onTick(const std::vector<Rectangle> collidables);

   void updateDirection( Vector2 target );

   // Renders the enemy on screen  
   void onRender();  

   void setDamageBlocked( bool blocked )
   {
      damageBlocked = blocked;
   }

   bool isDamageBlocked( ) const
   {
      return damageBlocked;
   }
   //Reese. take damage method used on enemy to take dmg from player
   void takeDamage( int damage );
  
   // Checks if a player's position is within attack range of the enemy  
   bool checkCollision(Vector2 playerPos, float attackRange) const;  

   // Getter for position (likely inherited from Character)  
   Vector2 getPosition() const { return position; }  

   // Getter for current health  
   int getHealth() const { return stats.health; }  
};