/* noeRouge - enemy.h
*  Worked on by: Kaleb Flowers, Reese Edens, Ethan Sheffield */

#pragma once	//only include this .h once

#include <raylib.h>        //Library with animation, rendering, interactive, and sound tools		  
#include <raymath.h>       //Library for  Math functions to work with Vector2, Vector3, Matrix	   
#include <vector>          //Library for the vector data structure
#include <iostream>		   //Library for input and output streams
#include <cmath>		   //Library for functions to compute common mathematical operations		 
#include "animation.h"	   //Class that handles all on screen character and environmental animations
#include "audio.h"		   //Class that handles the functions needed to play audio
#include "character.h" 	   //Class that enemy and player classes inherit from
#include "customCamera.h"  //Class that handles rendering visual output to the screen
#include "globals.h"	   //Class that handles global variables
#include "object.h"		   //Class that all game objects inherit from
#include "player.h"	       //Class that handles the player movement and functionality
#include "sheetSprite.h"   //Class that handles sprite sheets
#include "enemy.h"		   //The .h file for this class


	//Struct to hold various stat-related properties of an enemy
struct Stats
{
	int health;          //Health points of the enemy
	int attackDamage;    //Amount of damage enemy can deal per attack
	int attackRange;     //Distance at which the enemy can hit the player
	int speed;           //Character speed
};

/*-------------------------------------------------------------------------------------------------
* The enemy class is a child class of Character that represents the enemy
* characters that populate the map.
*------------------------------------------------------------------------------------------------*/
class Enemy : public Character
{
	private:

	bool damageBlocked = false;        //Tracks if damage is blocked

	public:

	float timeSinceLastAttack = 0.f;   //Amount of time since the enemies last attack.                                     
	float attackInterval = 1.0f;       //One attack per second                                            
	bool wasHit = false;               //True if an enemy was hit, false otherwise.
	float hitDisplayTimer = 0.0f;      //Amount of time an enemy will show hit for
	Stats stats;                       //Struct holding the enemy's stats 
	SheetSprite sprite;                //Set of 9 sprites for the enemy
	Animation animation = Animation( 4, 0.15 );	//Enemy's movement animation
	Vector2 hpBarPosition = 
		Vector2Subtract( _position, { 25.0f, 20.0f } );   //The position of the enemy's hp bar. 
			
		/*-----------------------------------------------------------------------------------------
		* getNearestPosition( )
		* -----------------------------------------------------------------------------------------
		* @names:  Reese
		* @brief:  Calculates and returns the nearest position of the enemy relative to the player.
		* @param:  none
		* @return: Vector2  - the nearest position of the enemy.
		*----------------------------------------------------------------------------------------*/
	Vector2 Enemy::getNearestPosition( ) const
	{
		return _position; //Assuming _position is the current position of the enemy from the Character class.  
	}

		//Parameterized Class constructor.
	Enemy( int id, Vector2 position, Stats stats );  

		//Updates the state of the enemy during a single frame.
	void onTick( const std::vector<Rectangle> collidables );                  
	
		//Sets the movement direction of the character based on target position.
	void updateDirection( Vector2 target );                                   
	
		//Renders the enemy on screen.
	void onRender( );                                                         
	
		//Reduces health when damage is taken, accounting for defense.
	void takeDamage( int damage );                                            
	
		//Checks if the player's position is within attack range of the enemy.
	bool checkCollision( Vector2 playerPos, float attackRange ) const;           
	
		//Handles enemy behavior when engaging the player.
	void attackPlayer( Player* player );                                      
		
		//Accessor Methods for stats.health and damageBlocked
	int getHealth( ) const { return stats.health; }
	void setDamageBlocked( bool blocked ) { damageBlocked = blocked; }       
	bool isDamageBlocked( ) const { return damageBlocked; }                 

};

/*  Changes made during commenting by Evan:
*
*	-General formatting
*
*	-Added inline comments to #includes
*/