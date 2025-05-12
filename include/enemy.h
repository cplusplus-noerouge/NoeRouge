/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Kaleb Flowers, Reese Edens, Ethan Sheffield
* The enemy class is a child class of Character that represents the enemy characters that populate the map.
----------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "character.h" 
#include "enemy.h" 
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
	int health;                      //Health points of the enemy
	int attackDamage;                //Amount of damage enemy can deal per attack
	int attackRange;                 //Distance at which the enemy can hit the player
	int speed;                       //Character speed
};

class Enemy : public Character
{
	private:

	bool damageBlocked = false;      //Tracks if damage is blocked

	public:

	/*---------------------------------------------------------------------------------------------------------------------------------------
	* getNearestPosition( )
	* Reese
	* @brief : Calculates and returns the nearest position of the enemy relative to the player.
	* @param : none
	* @return Vector2 : The nearest position of the enemy.
	----------------------------------------------------------------------------------------------------------------------------------------*/
	Vector2 Enemy::getNearestPosition( ) const
	{
		return _position; //Assuming _position is the current position of the enemy from the Character class.  
	}

	Stats stats;                                                              //Struct holding the enemy's stats 
	SheetSprite sprite;                                                       //Set of 9 sprites for the enemy
	Animation animation = Animation( 4, 0.15 );                               //Enemy's movement animation

	Enemy( int id, Vector2 position, Stats stats );                           //Parameterized Class constructor.
	
	void onTick( const std::vector<Rectangle> collidables );                  //Updates the state of the enemy during a single frame.
	void updateDirection( Vector2 target );                                   //Sets the movement direction of the character based on target position.
	void onRender( );                                                         //Renders the enemy on screen.
	void takeDamage( int damage );                                            //Reduces health when damage is taken, accounting for defense.
	bool checkCollision( Vector2 playerPos, float attackRange ) const;        //Checks if the player's position is within attack range of the enemy.   
	void attackPlayer( Player* player );                                      //Handles enemy behavior when engaging the player.
	float timeSinceLastAttack = 0.f;                                          //Amount of time since the enemies last attack.
	float attackInterval = 1.0f;                                              //One attack per second
	bool wasHit = false;                                                      //True if an enemy was hit, false otherwise.
	float hitDisplayTimer = 0.0f;                                             //Amount of time an enemy will show hit for
	Vector2 hpBarPosition = Vector2Subtract( _position, { 25.0f, 20.0f } );   //The position of the enemy's hp bar. 

	/*--------------------------------------------------------------------------------------------------------------------------------------
	* @brief : Accessor Methods for stats.health and damageBlocked
	---------------------------------------------------------------------------------------------------------------------------------------*/
	int getHealth( ) const { return stats.health; }
	void setDamageBlocked( bool blocked ) { damageBlocked = blocked; }       
	bool isDamageBlocked( ) const { return damageBlocked; }                 

};