/* noeRouge - player.cpp
*  Worked on by: Ben A, Kaleb, Reese, Ethan, Thomas, Adam, Devon */

#include <iostream>			//Library for input and output streams
#include <cmath>			//Library for functions to compute common mathematical operations
#include "player.h"			//Class that handles the player movement and functionality
#include "object.h"			//Class that all game objects inherit from
#include "customCamera.h"	//Class that handles rendering visual output to the screen
#include "sprite.h"         //Class that handles sprite objects
#include "enemy.h"			//Class that represents the enemy characters that populate the map
#include "audio.h"	        //Class that handles the functions needed to play audio
#include "globals.h"		//Class that handles global variables
#include "mapHandler.h"     //Class that handles the map object

extern MapHandler* mapHandler;    //The game's mapHandler object
extern CustomCamera mainCamera;   //Camera view of the map

/*-------------------------------------------------------------------------------------------------
*  The Player class represents the player character in the game and handles player movement,
*  rendering, and attacking functionality.
*
*  Inherits sprite functionality from Sprite class.
*  Inherits character functionality from Character class.
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* updateDirection( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Sets the movement direction of the player based on control input.
	*          Implements dodge ability.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::updateDirection( )
{
	if ( Controls::moveLeft( ) )
	{
		direction.x = -1;
	}
	else if ( Controls::moveRight( ) )
	{
		direction.x = 1;
	}
	if ( Controls::moveDown( ) )
	{
		direction.y = 1;
	}
	else if ( Controls::moveUp( ) )
	{
		direction.y = -1;
	}
	dodge( );
}

	/*---------------------------------------------------------------------------------------------
	* onTick( const std::vector<Rectangle> colliders )
	* ---------------------------------------------------------------------------------------------
	* @names:  Reese, Kaleb, Ben A, Devon
	* @brief:  Updates the state of the player during a single frame.
	* @param:  colliders - The collection of collidables to check for character collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::onTick( const std::vector<Rectangle> colliders )
{
	if ( isDead )
	{
		return;
	}
	Character::onTick( colliders );

	walkTimer += GetFrameTime( );

	if ( walkTimer > WALK_TIMER_MAX && ( direction.x != 0 || direction.y != 0 ) )
	{
		( sfx[ "walkLeft.wav" ] );
		walkTimer = 0.0f;
	}

	   //Get current floors objhandler.
	   //Parse through it and make a subset of enemies, created after ladders and doors.
	std::vector<Enemy*> enemies = mapHandler->getEnemies( );

	   //**Reese** added player attack, outputs "ATTACKING" to console when space is pressed
	if ( Controls::attack( ) )     //Player attacks when space is pressed
	{
		this->attack( enemies );   //Attack with a range of 50 and damage of 10
	}
	if ( Controls::defend( ) )     //Player defends when left shift is pressed
	{
		this->defend( enemies );   //Defend against enemy attacks
	}
	if ( Controls::interact( ) )   //Try to interact with nearest interactable object -Devon
	{
		interactWithNearest( );
	}
}

	/*---------------------------------------------------------------------------------------------
	* onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb, Reese, Adam
	* @brief:  Renders the player on screen.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::onRender( )
{
	mainCamera.setPosition( _position );
	   //Animating the player
	animation.onTick( );
	if ( isDead )
	{
		sprite.setTexture( "playerDead" );          //Optional: static 'dead' texture
		sprite.setSourceRect( { 0, 0, 16, 16 } );   //Make sure it's valid
	}
	else
	{
			//Freezing the animation at frame 1 if the player isn't moving
			//WARNING! This logic will need to be revised when implementing other animations 
			//that aren't just for walking.
		animation.onTick( );
		if ( Vector2Equals( direction, { 0, 0 } ) )
			animation.reset( );
		sprite.setTexture( "playerWalk" + std::to_string( animation.getFrame( ) ) );
		if ( direction.x < 0 )
			sprite.setSourceRect( { 0, 0, 16, 16 } );
		else if ( direction.x > 0 )
			sprite.setSourceRect( { 32, 0, 16, 16 } );
		else if ( direction.y >= 0 )
			sprite.setSourceRect( { 16, 0, 16, 16 } );
		else
			sprite.setSourceRect( { 48, 0, 16, 16 } );
	}
	sprite.setTexture( "playerWalk" + std::to_string( animation.getFrame( ) ) );
	   //Show text on screen when player attacks
	DrawText( "ATTACKING", _position.x, _position.y, 20, RAYWHITE );
	   //Setting the position referenced on the sheet based on the direction the plaer is facing
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

	sprite.update( _position, _position.y );
	mainCamera.addToBuffer( &sprite );
}

	/*---------------------------------------------------------------------------------------------
	* attack( std::vector<Enemy*>& enemies )
	* ---------------------------------------------------------------------------------------------
	* @names:  Reese Edens
	* @brief:  Updates camera position and updates sprite, renders the character on screen.
	* @param:  enemies : The collection of enemies to check for collision with.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::attack( std::vector<Enemy*>& enemies )
{
	if ( Controls::attack( ) )
	{
		std::cout << "ATTACKING" << std::endl;
		for ( Enemy* enemy : enemies )
		{
			if ( enemy->checkCollision( _position, attackRange ) )
			{

				PlaySound( sfx[ "laserShoot.wav" ] );
				Vector2 enemyPosition = enemy->getNearestPosition( );
				enemy->takeDamage( attackDamage );
				DrawText( "HIT!", _position.x, _position.y - 20, 20, RAYWHITE );
			}
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* defend( std::vector<Enemy*>& enemies )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Allows the player to defend against enemy attacks.
	* @param:  enemies : The collection of enemies to check for collision with.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::defend( std::vector<Enemy*>& enemies )
{
	if ( Controls::defend( ) )
	{
		std::cout << "Defending against enemy attack!";
		if ( !isInvincible )
		{
			setInvincible( true );
		}
		for ( Enemy* enemy : enemies )
		{
			if ( enemy->checkCollision( _position, attackRange ) )
			{
				enemy->setDamageBlocked( true );
			}
		}
	}
	else
	{
		for ( Enemy* enemy : enemies )
		{
			enemy->setDamageBlocked( false );   //Reset damage block
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* setInvincible( bool invincible )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Sets the invincibility state and resets the timer if invincible.
	* @param:  invincible - True if the player is invincible, false if not.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::setInvincible( bool invincible )
{
	isInvincible = invincible;
	if ( invincible )
	{
		invincibilityTimer = invincibilityDuration; // Reset the timer
	}
}

	/*---------------------------------------------------------------------------------------------
	* updateInvincibility( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Updates the invincibility timer and disables invincibility when the timer expires.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::updateInvincibility( )
{
	if ( isInvincible )
	{
		invincibilityTimer -= GetFrameTime( );   //Decrease timer by frame time
		if ( invincibilityTimer <= 0.0f )
		{
			isInvincible = false;                 //Disable invincibility
			invincibilityTimer = 0.0f;
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* takeDamage( int damage )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ethan Sheffield, Ben Aguilon
	* @brief:  Decrements player health based off enemy damage and checks for player death.
	* @param:  damage - amount of incoming damage to decrement from health
	* @param:  playerDefeated - reference to a bool value, if player has been defeated or not.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::takeDamage( int damage )
{
	PlaySound( sfx[ "playerDamaged.mp3" ] );

	health -= damage;
	std::cout << "Player taken damage!";

	if ( health <= 0 && !isDead )
	{
		isDead = true;
		std::cout << "Player defeated!" << std::endl;
		mapHandler->endGame( false );
	}
}

	/*---------------------------------------------------------------------------------------------
	* healHp( int healAmount )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon Johnson
	* @brief:  Heals the player by hp amount, up until the max hp
	* @param:  healAmount - Amount to increase hp by.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::healHp( int healAmount )
{
	health = std::min( maxHp, health + healAmount );
	std::cout << "Player healed " << healAmount << " hp";
}

	/*---------------------------------------------------------------------------------------------
	* createPlayer( Vector2 position )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Object creation function defined in ObjectHandler.
	* @param:  position - Initial position of player
	* @return: Player* - Pointer to the created Player object.
	*--------------------------------------------------------------------------------------------*/
class Player* ObjectHandler::createPlayer( Vector2 position )
{
	class Player* Player = new class Player( 0, position );   //id for player is always 0
	allObjects[ Player->getId( ) ] = Player;                 //add <id, object*> to the map
	this->numberOfObjects++;
	return Player;
}

	/*---------------------------------------------------------------------------------------------
	* dodge( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Thomas Orozco
	* @brief:  Increases players speed by 1.4 times for 1 second when left shift is pressed and
	*          prevents user from doing it for another 2 seconds
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::dodge( )
{
	if ( Controls::dodge( ) )
	{
		if ( dodgeCooldown <= 0 )
		{
			dodgeCooldown = 3 * GetFPS( );   //Change what dodgeCooldown get set to alter cooldown 
		}										//length, remember it is decrimented each frame.
	}

	if ( dodgeCooldown > 2 * GetFPS( ) )   //Change lenght of time dodging happens by altering what
	{											//dodgeCooldown is compared to, lower is longer.
		direction.x = direction.x * 1.4;   //Alter speed of dodging by changing numbers direction 
		direction.y = direction.y * 1.4;		//is multiplied by, * 1 is base walking speed.
	}

	if ( dodgeCooldown > 0 )
	{
		dodgeCooldown--;   //Decriments dodgeCooldown each frame
	}
}

	/*---------------------------------------------------------------------------------------------
	* interactWithNearest( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon Johnson
	* @brief:  Interacts with the nearest Interactable if there is one in range
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Player::interactWithNearest( )
{
	Interactable* closestInteractable = NULL;
	int distToClosest = INT_MAX;

	   //Get closest interactable
	float dist;
	for ( Interactable* i : mapHandler->getInteractables( ) )
	{
		dist = Vector2Distance( i->getPos( ), getPosition( ) );
		if ( dist < distToClosest )
		{
			distToClosest = dist;
			closestInteractable = i;
		}
	}

	   //Check if the closest interactable is in range
	if ( distToClosest < INTERACTION_RANGE )
	{
		closestInteractable->interact( );
	}
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/