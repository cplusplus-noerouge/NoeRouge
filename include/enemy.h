/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Kaleb Flowers, Reese Edens, Ethan Sheffield
* The enemy class is a child class of Character that represents the enemy characters that populate the map.
*
* * TO-DO :
* - Add attack functionality?
* - Add AI behavior?
* - Include more interaction with player?
----------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "character.h"
#include <raylib.h>
#include <iostream>
#include <cmath>
#include <raymath.h>
#include <vector>
#include "globals.h"
#include "object.h"
#include "audio.h"
#include <animation.h>
#include "sheetSprite.h"
#include <customCamera.h>
#include "player.h"

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Struct to hold various stat-related properties of an enemy
----------------------------------------------------------------------------------------------------------------------------------------*/
struct Stats
{
	int health;                                                          //Health points of the enemy
	int attackDamage;                                                    //Amount of damage enemy can deal per attack
	int attackRange;                                                     //Distance at which the enemy can hit the player
	int speed;                                                           //Character speed
};

class Enemy : public Character
{
	private:
	bool damageBlocked = false; // Tracks if damage is blocked
	public:
	int world_position[ 2 ];                                             //Make this public for accessibility  
	Stats stats;                                                         //Struct holding the enemy's stats 
	SheetSprite sprite;                           //Set of 9 sprites for the enemy
	Animation animation = Animation( 4, 0.15 );   //Enemy's movement animation

	Enemy( int id, Vector2 position, Stats stats );                          //Parameterized Class constructor.

	void onTick( const std::vector<Rectangle> collidables );             //Updates the state of the enemy during a single frame.
	void updateDirection( Vector2 target );                              //Sets the movement direction of the character based on target position.
	void onRender( );                                                    //Renders the enemy on screen.
	void takeDamage( int damage );                                       //Reduces health when damage is taken, accounting for defense.
	bool checkCollision( Vector2 playerPos, float attackRange ) const;   //Checks if the player's position is within attack range of the enemy.   
	void setDamageBlocked( bool blocked ) { damageBlocked = blocked; }
	bool isDamageBlocked( ) const { return damageBlocked; }
	void attackPlayer( Player* player );
	float timeSinceLastAttack = 0.f;
	float attackInterval = 1.0f; // one attack per second

	/*--------------------------------------------------------------------------------------------------------------------------------------
	* getPosition( )
	* @brief : Getter for the enemy's position.
	* @param : none
	* @return Vector2 : The current position of the enemy.
	---------------------------------------------------------------------------------------------------------------------------------------*/
	//Vector2 getPosition( ) const { return position; }

	/*--------------------------------------------------------------------------------------------------------------------------------------
	* getHealth( )
	* @brief : Getter for the enemy's health.
	* @param : none
	* @return int : The current heatlh of the enemy.
	---------------------------------------------------------------------------------------------------------------------------------------*/
	int getHealth( ) const { return stats.health; }

};