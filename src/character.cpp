/* noeRouge - character.cpp
*  Worked on by: Ben A, Kaleb, Reese, Ethan */

#include "Character.h"	//The .h file for this class
#include "globals.h"	//Class that handles global variables
#include <raylib.h>		//Library with animation, rendering, interactive, and sound tools
#include <raymath.h>	//Library for  Math functions to work with Vector2, Vector3, Matrix
#include <vector>		//Library for the vector data structure
#include <cmath>		//Library with a set of functions to compute common mathematical operations

/*-------------------------------------------------------------------------------------------------
*  The Character class is a parent class for any player or enemy character that is rendered on
*  screen and moves.
*
*  Character class (inherits from GameObject class)
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* Character( int id, Vector2 position ) : _target( { 0,0 } )
	* ---------------------------------------------------------------------------------------------
	* @names:  
	* @brief:  Parameterized Class constructor.
	* @param:  id - object ID number
	* @param:  position - characters map position
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Character::Character( int id, Vector2 position ) : _target( { 0,0 } )
{
	this->setId( id );
	_position = position;
	_size = Settings::TILE_DIMENSIONS;
	_speed = Settings::PLAYER_SPEED;
	velocity = { 0 };
	direction = { 0 };
}

	/*---------------------------------------------------------------------------------------------
	* Character( int id )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Class constructor based on object ID.
	* @param:  id - object ID number
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Character::Character( int id )
{
	this->setId( id );
	_position = { 0 };
	_size = Settings::TILE_DIMENSIONS;
	_speed = Settings::PLAYER_SPEED;
	velocity = { 0 };
	direction = { 0 };
	_target = { 0, 0 };
}

	/*---------------------------------------------------------------------------------------------
	* bounds( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Creates a Rectangle representing the character's current position and size.
	* @param:  none
	* @return: Rectangle - The Rectangle representing the character's current position and size.
	*--------------------------------------------------------------------------------------------*/
Rectangle Character::bounds( )
{
	return { _position.x, _position.y, _size.x, _size.y };
}

	/*---------------------------------------------------------------------------------------------
	* updateDirection( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Sets the movement direction of the character based on control input.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::updateDirection( )
{
	if ( Controls::moveLeft( ) )
	{
		direction.x = -1;
	}
	else if ( Controls::moveDown( ) )
	{
		direction.x = 1;
	}
	if ( Controls::moveRight( ) )
	{
		direction.y = 1;
	}
	else if ( Controls::moveUp( ) )
	{
		direction.y = -1;
	}
}

	/*---------------------------------------------------------------------------------------------
	* updateDirection( Vector2 target )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Sets the movement direction of the character based on a target position.
	* @param:  target - Target used to adjust character's position.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::updateDirection( Vector2 target )
{
	if ( target.x > _position.x )
	{
		direction.x = 1;
	}
	else if ( target.x < _position.x )
	{
		direction.x = -1;
	}
	if ( target.y < _position.y )
	{
		direction.y = -1;
	}
	else if ( target.y > _position.y )
	{
		direction.y = 1;
	}
}

	/*---------------------------------------------------------------------------------------------
	* onTick( const std::vector<Rectangle> collidables )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Updates the state of the character during a single frame.
	* @param:  collidables : The collection of collidables to check for character collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::onTick( const std::vector<Rectangle> collidables )
{
	direction = { 0, 0 };

	updateDirection( );

	   //direction is multiplied by speed, which makes velocity
	   //speed is multiplied by the time between frames, which forces speed to be the same 
	   //regardless of framerate.
	velocity = Vector2Scale( Vector2Normalize( direction ), _speed * GetFrameTime( ) );

	   //collisions must be done before velocity is added to position so that the character does 
	   //not go past a wall before collisions are checked, but that is
	   //only necessary for very high movement speed
	updateCollisions( collidables );

	_position = Vector2Add( _position, velocity );
}

	/*---------------------------------------------------------------------------------------------
	* onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Renders the character on screen.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::onRender( )
{
	Rectangle rectangle = bounds( );
	DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON );
}

	/*---------------------------------------------------------------------------------------------
	* Collision Methods
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Checks for collisions in cardinal directions.
	* @param:  Rectangle other - The Rectangle the character is potentially colliding with.
	* @return: bool - True if a collision is detected, false if otherwise.
	*--------------------------------------------------------------------------------------------*/
bool Character::collidingLeft( Rectangle other )
{
	Rectangle rect = bounds( );
	return rect.x + rect.width + velocity.x > other.x && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x < other.x;
}

bool Character::collidingRight( Rectangle other )
{
	Rectangle rect = bounds( );
	return rect.x + velocity.x < other.x + other.width && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x + rect.width > other.x + other.width;
}

bool Character::collidingTop( Rectangle other )
{
	Rectangle rect = bounds( );
	return rect.y + rect.height + velocity.y > other.y && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y < other.y;
}

bool Character::collidingBottom( Rectangle other )
{
	Rectangle rect = bounds( );
	return rect.y + velocity.y < other.y + other.height && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y + rect.height > other.y + other.height;
}

	/*---------------------------------------------------------------------------------------------
	* updateCollisions( const std::vector<Rectangle> colliders )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Detects and resolves collisions between the character and a list of colliders.
	* @param:  colliders - The collection of collidables to check for character collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::updateCollisions( const std::vector<Rectangle> colliders )
{
	Rectangle rect = bounds( );

	for ( Rectangle otherRect : colliders )
	{
		if ( collidingLeft( otherRect ) && velocity.x > 0 )
		{
			velocity.x = 0;
			_position.x = otherRect.x - rect.width;
		}
		else if ( collidingRight( otherRect ) && velocity.x < 0 )
		{
			velocity.x = 0;
			_position.x = otherRect.x + otherRect.width;
		}
		if ( collidingTop( otherRect ) && velocity.y > 0 )
		{
			velocity.y = 0;
			_position.y = otherRect.y - rect.height;
		}
		else if ( collidingBottom( otherRect ) && velocity.y < 0 )
		{
			velocity.y = 0;
			_position.y = otherRect.y + otherRect.height;
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* getPosition( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Getter for the character's position.
	* @param:  none
	* @return: Vector2 - The current position of the character.
	*--------------------------------------------------------------------------------------------*/
Vector2 Character::getPosition( )
{
	return _position;
}

	/*---------------------------------------------------------------------------------------------
	* setPosition( Vector2 newPos )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Setter for the character's position.
	* @param:  newPos - The new position to be assigned to the character.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::setPosition( Vector2 newPos )
{
	_position = newPos;
}

	/*---------------------------------------------------------------------------------------------
	* getTargetDistance( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Calculates the distance between the character and a target.
	* @param:  none
	* @return: float - The distance between the character and a target.
	*--------------------------------------------------------------------------------------------*/
float Character::getTargetDistance( )
{
	float dx = _position.x - _target.x;
	float dy = _position.y - _target.y;
	return sqrt( dx * dx + dy * dy );
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
* 
*	-Added @params to constructors
*/