/* noeRouge - npcLogic.cpp
*  Worked on by: Matthew, Ethan */

#include "character.h" 	//Class that enemy and player classes inherit from
#include "object.h"		//Class that all game objects inherit from
#include "globals.h"	//Class that handles global variables
#include <raymath.h>	//Library for  Math functions to work with Vector2, Vector3, Matrix

int HALF_SIZE = Settings::TILE_SIZE / 2;

/*-------------------------------------------------------------------------------------------------
* The NpcLogic class implements enemy AI procedures such as Line of Sight and Move to Target
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* moveToTarget( Vector2 target, float distanceMaintained, std::vector<Rectangle> colliders )
	* ---------------------------------------------------------------------------------------------
	* @names:  Matthew, Ethan
	* @brief:  Moves character to the target's position but maintain a set distance.
	* @param:  target - Target's map position.
	* @param:  distanceMaintained - The set distance the character maintains from the target.
	* @param:  colliders - The collection of collidables to check for character collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Character::moveToTarget( Vector2 target, float distanceMaintained, 
							  std::vector<Rectangle> colliders )
{
	if ( !Character::updateLOS( colliders, target ) 
		 && Character::getTargetDistance( ) > distanceMaintained )
	{
		updateDirection( target );
	}
}

	/*---------------------------------------------------------------------------------------------
	* relationToTarget( Vector2 target )
	* ---------------------------------------------------------------------------------------------
	* @names:  Matthew, Ethan
	* @brief:  Calculates the line of sight from the character's position to the target
	* @param:  none
	* @return: Ray - The line of sight from the character's position to the target
	*--------------------------------------------------------------------------------------------*/
Ray Character::relationToTarget( Vector2 target )
{
	Vector2 pos = _position;
	Vector3 direction = Vector3Normalize( { target.x - _position.x, target.y - _position.y, 0 } );
	Ray lineOfSight = { { pos.x, pos.y, 0 }, direction };
	return lineOfSight;
}

	/*---------------------------------------------------------------------------------------------
	* updateLOS( std::vector<Rectangle> colliders, Vector2 target )
	* ---------------------------------------------------------------------------------------------
	* @names:  Matthew, Ethan
	* @brief:  Updates relation to target and creates line of sight by checking for collisions.
	* @param:  colliders - The collection of collidables to check for character collision.
	* @return: bool - True if the line of sight is obstructed, false otherwise.
	*--------------------------------------------------------------------------------------------*/
bool Character::updateLOS( std::vector<Rectangle> colliders, Vector2 target )
{
	Ray LOS = relationToTarget( target );
	BoundingBox closestCollision = { { 0, 0, 0 },{ 0, 0, 0 } };
	float closestDistance = LONG_MAX;
	for ( Rectangle wall : colliders )
	{
		BoundingBox walltile = { {wall.x - HALF_SIZE, wall.y - HALF_SIZE, 0 },
										 {wall.x + HALF_SIZE, wall.y + HALF_SIZE, 0 } };

			//There are probably some weird angles where this wouldn't work, might need review.
		if ( GetRayCollisionBox( LOS, walltile ).hit )
		{
			float dx = _position.x - wall.x;
			float dy = _position.y - wall.y;
			if ( closestDistance > sqrt( dx * dx + dy * dy ) )
			{
				closestDistance = sqrt( dx * dx + dy * dy );
				closestCollision = walltile;
			}
		}
	}
	if ( closestDistance < Vector2Distance( _position, target ) )
	{
		return true;
	}
	return false;
}

/*  Changes made during commenting by Evan:
*
*	-Added inline comments to #includes
*
*	-General formatting
*/