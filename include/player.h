/* noeRouge - player.h
*  Worked on by: Ben A, Kaleb, Reese, Ethan, Thomas, Adam, Devon */

#pragma once	//only include this .h once

#include <raylib.h>	        //Library with animation, rendering, interactive, and sound tools
#include "character.h" 		//Class that enemy and player classes inherit from
#include "sheetSprite.h"	//Class that handles sprite sheets
#include "animation.h"		//Class that handles all on screen character and environmental animations
#include "enemy.h"		    //Class that represents the enemy characters that populate the map
#include "globals.h"		//Class that handles global variables

const float WALK_TIMER_MAX = 0.5f;                       //Maximum allowed time between "walking" sound effect triggers
const int INTERACTION_RANGE = Settings::TILE_SIZE * 2;   //The range the player can interact with interactables, in pixels
	
/*-------------------------------------------------------------------------------------------------
*  The Player class represents the player character in the game and handles player movement, 
*  rendering, and attacking functionality.
* 
*  Inherits sprite functionality from Sprite class.
*  Inherits character functionality from Character class.
*------------------------------------------------------------------------------------------------*/
class Player : public Character
{
	private:

	float attackRange;                            //Attack radius
	int attackDamage;                             //Damage per hit
	int health;                                   //Player health
	int dodgeCooldown;                            //Cooldown length of dodge ability
	float walkTimer;                              //Time between steps
	SheetSprite sprite;                           //Set of 4 sprites for the player
	Animation animation = Animation( 4, 0.15 );   //Players movement animation
	bool isInvincible = false;                    //Tracks if the player is invincible-KF
	float invincibilityTimer = 0.0f;              //Timer for invincibility frames-KF
	const float invincibilityDuration = 0.7f;     //Duration of invincibility in seconds-KF

	void interactWithNearest( );                  //Interacts with the nearest Interactable if there is one in range -devon

	public:

	const static int maxHp = 5;                   //The max and starting value for player hp

		/*-----------------------------------------------------------------------------------------
		* Player( int id, Vector2 position )
		* -----------------------------------------------------------------------------------------
		* @names:  
		* @brief:  Parameterized Class constructor.
		* @param:  id -  GameObject identification number
		* @param:  position - starting position in the map for this object
		* @return: none
		*----------------------------------------------------------------------------------------*/
	Player( int id, Vector2 position )
		: Character( id, position ), attackRange( 25.0f ), attackDamage( 1 ), 
		  health( maxHp ), dodgeCooldown( 0 )
	{
		Animation animation = Animation( 4, 0.1 );
		sprite = SheetSprite( "playerWalk1", { 16, 0, 16, 16 }, position, position.y );
		walkTimer = 0.0f;
	}

		//Accessors for Invicibility Frame
	void setInvincible( bool invincible );   //Sets the invincibility state and resets the timer if invincible.
	void updateInvincibility( );
	bool getIsInvincible( ) const
	{
		return isInvincible;
	}
		
		//Getter for the Player object's health
	int getHealth( )
	{
		return health;
	}

		 //Sets the movement direction of the character based on control input.
	void updateDirection( ) override;                                

		//Updates the state of the player during a single frame.
	void onTick( const std::vector<Rectangle> colliders ) override;   

		//Renders the player on screen.
	void onRender( ) override;                                        
	
		//Attacks enemy objects if within range and key is pressed.
	void attack( std::vector<Enemy*>& enemies );                      

		//Allows the player to defend against enemy attacks.
	void defend( std::vector<Enemy*>& enemies );                     
	
		//Decrements player health based off enemy damage and checks for player death.
	void takeDamage( int damage );                                    
	
		//Heals the player by hp amount, up until the max hp
	void healHp( int hp );                                            
	
		//Increases players speed by 1.4 times for 1 second, then cools down for 2 seconds
	void dodge( );                                                 
};

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/
