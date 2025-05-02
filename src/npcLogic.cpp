/*----------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* npcLogic class
* Matthew, Ethan
* The npcLogic class is used implement enemy AI procedures such as Line of Sight and Move to Target
----------------------------------------------------------------------------------------------------------------------------------------*/

#include "character.h"
#include "object.h"
#include "mapGen.h"
#include "raymath.h"

int HALF_SIZE = TILE_SIZE / 2;

/*---------------------------------------------------------------------------------------------------------------------------------------
* moveToTarget( )
* @brief : Moves character to the target's position but maintain a set distance.
* @param Vector 2 target : Target's map position.
* @param float distanceMaintained : The set distance the character maintains from the target.
* @param : vector<Rectangle> colliders : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::moveToTarget( Vector2 target, float distanceMaintained, std::vector<Rectangle> colliders )
{
	if ( Character::updateLOS( colliders ) && Character::getTargetDistance( ) > distanceMaintained )
	{
		updateDirection( target );
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* relationToTarget( )
* @brief : Calculates the line of sight from the character's position to the target.
* @param : none
* @return Ray : The line of sight from the character's position to the target.
----------------------------------------------------------------------------------------------------------------------------------------*/
Ray Character::relationToTarget( )
{
	Vector2 pos = position;
	Vector2 tar = target;
	Vector3 direction = Vector3Normalize( { tar.x - position.x, tar.y - position.y, 0 } );
	Ray lineOfSight = { { pos.x, pos.y, 0 }, direction };
	return lineOfSight;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateLOS( )
* @brief : Updates relation to target and creates line of sight by checking for collisions.
* @param vector<Rectangle> colliders : The collection of collidables to check for character collision.
* @return bool : True if the line of sight is obstructed, false otherwise.
----------------------------------------------------------------------------------------------------------------------------------------*/
bool Character::updateLOS( std::vector<Rectangle> colliders )
{
	Ray LOS = relationToTarget( );
	BoundingBox closestCollision = { { 0, 0, 0 },{ 0, 0, 0 } };
	float closestDistance = LONG_MAX;
	for ( Rectangle wall : colliders )
	{
		BoundingBox walltile = { {wall.x - HALF_SIZE, wall.y - HALF_SIZE, 0 },
										 {wall.x + HALF_SIZE, wall.y + HALF_SIZE, 0 } };

		//There are probably some weird angles where this wouldn't work, might need review.
		if ( GetRayCollisionBox( LOS, walltile ).hit )
		{
			float dx = position.x - wall.x;
			float dy = position.y - wall.y;
			if ( closestDistance > sqrt( dx * dx + dy * dy ) )
			{
				closestDistance = sqrt( dx * dx + dy * dy );
				closestCollision = walltile;
			}
		}
	}
	if ( closestDistance < getTargetDistance( ) )
	{
		return true;
	}
}
