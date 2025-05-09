/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Thomas, Adam
* Inherits from Character class.
* Inherits sprite functionality from Sprite class.
* Inherits character functionality from Character class.
* Player class represents the player character in the game.
----------------------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include "player.h"
#include "object.h"
#include "customCamera.h"
#include "sprite.h"
#include "enemy.h"
#include "audio.h"
#include "globals.h"



extern CustomCamera mainCamera;   //Camera view of the map

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateDirection( )
* @brief : Sets the movement direction of the player based on control input. Implements dodge ability.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::updateDirection( )
{
	if ( Controls::moveLeft() )
	{
		direction.x = -1;
	}
	else if ( Controls::moveRight() )
	{
		direction.x = 1;
	}
	if ( Controls::moveDown() )
	{
		direction.y = 1;
	}
	else if ( Controls::moveUp() )
	{
		direction.y = -1;
	}

	dodge( );
}


/*---------------------------------------------------------------------------------------------------------------------------------------
* onTick( )
* @brief : Updates the state of the player during a single frame.
* @param vector<Rectangle> colliders : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::onTick( const std::vector<Rectangle> colliders )
{
	Character::onTick( colliders );

	walkTimer += GetFrameTime( );

	if ( walkTimer > WALK_TIMER_MAX && ( direction.x != 0 || direction.y != 0 ) )
	{
		PlaySound( sfx[ "walkLeft.wav" ] );
		walkTimer = 0.0f;
	}
	//**Reese** added player attack, outputs "ATTACKING" to console when space is pressed
	if ( Controls::attack( ) )  // player attacks when space is pressed
	{
		//this->attack( enemies ); // Attack with a range of 50 and damage of 10
	}
	if ( Controls::defend( ) ) // player defends when left shift is pressed
	{
		//this->defend( enemies ); // Defend against enemy attacks
	}

	
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onRender( )
* @brief : Renders the player on screen.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::onRender( )
{
	mainCamera.setPosition( _position );   //Updating the camera position should be moved to its own class or function later on
	   //Animating the player
	animation.onTick( );
	   //Freezing the animation at frame 1 if the player isn't moving
	   //WARNING! This logic will need to be revised when implementing other animations that aren't just for walking.
	if ( Vector2Equals( direction, { 0 , 0 } ) )
	{
		animation.reset( );
	}
	sprite.setTexture( "playerWalk" + std::to_string( animation.getFrame( ) ) );

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

/*---------------------------------------------------------------------------------------------------------------------------------------
* attack( )
* @brief : Updates camera position and updates sprite, renders the character on screen.
* @param vector<Enemy*>& enemies : The collection of enemies to check for collision with.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::attack( std::vector<Enemy*>& enemies )
{
	if ( Controls::attack() )
	{  
		for ( Enemy* enemy : enemies )
		{
			if ( enemy->checkCollision( _position, attackRange ) )
			{
				std::cout << "ATTACKING" << std::endl;
				PlaySound( sfx[ "laserShoot.wav" ] );
				enemy->takeDamage( attackDamage );

				   //Calculate the position to display the hit effect
				Vector2 enemyPosition = enemy->getPosition( );
				Vector2 position = { enemyPosition.x - 20, enemyPosition.y - 20 };   //Adjust as needed for centering text
				   //Set the font size and color for the hit effect
				   //Display hit effect
			      //Vector2 position = enemy->getPosition( );
				DrawText( "HIT!", position.x + 30, position.y + 30, 30, RAYWHITE );
			}
		}
		EndDrawing( );
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* defend()
* Kaleb Flowers
* @brief : Allows the player to defend against enemy attacks.
* @param vector<Enemy*>& enemies : The collection of enemies to check for collision with.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::defend( std::vector<Enemy*>& enemies )
{

	if ( Controls::defend() )
	{
		BeginDrawing( );  // remove ( leftover code) 
		for ( Enemy* enemy : enemies )
		{
			if ( enemy->checkCollision( _position, attackRange ) )
			{
				//stop player movement
				//stop incoming damage from enemy 
			}
		}
		std::cout << "Defending against enemy attack!";
		EndDrawing( );
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------
* takeDamage( )
* Ethan Sheffield, Ben Aguilon
* @brief : Decrements player health based off enemy damage and checks for player death.
* @param int damage : amount of incoming damage to decrement from health
* @param bool &playerDefeated : reference to a bool value, if player has been defeated or not.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::takeDamage( int damage, bool& playerDefeated )
{
	PlaySound( sfx[ "playerDamaged.mp3" ] );

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
* Ben Aguilon
* @brief : Object creation function defined in ObjectHandler.
* @param Vector2 position : Initial position of player.
* @param Vector2 size : Initial size of player.
* @param int speed : Initial speed of player.
* @return Player* : Pointer to the created Player object.
----------------------------------------------------------------------------------------------------------------------------------------*/
class Player* ObjectHandler::createPlayer( Vector2 position )
{
	class Player* Player = new class Player( 0, position);   //id for player is always 0
	allObjects[ Player->getId( ) ] = Player;                 //add <id, object*> to the map
	this->numberOfObjects++;
	return Player;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* dodge()
* Thomas Orozco
* @brief : Increases players speed by 1.4 times for 1 second when left shift is pressed and prevents user from doing it for another 2 seconds
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Player::dodge( )
{
	if ( Controls::dodge() )
	{
		if ( dodgeCooldown <= 0 )
		{
			dodgeCooldown = 3 * GetFPS( ); //Change what dodgeCooldown get set to alter cooldown length, remember it is decrimented each frame.
		}
	}

	if ( dodgeCooldown > 2 * GetFPS( ) ) // Change lenght of time dodging happens by altering what dodgeCooldown is compared to, lower is longer.
	{
		direction.x = direction.x * 1.4; //Alter speed of dodging by changing numbers direction is multiplied by, * 1 is base walking speed
		direction.y = direction.y * 1.4;
	}

	if ( dodgeCooldown > 0 )
	{
		dodgeCooldown--; //Decriments dodgeCooldown each frame
	}
}
