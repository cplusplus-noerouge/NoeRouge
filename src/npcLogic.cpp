#include "character.h"
#include "object.h"
#include "mapGen.h"
#include "raymath.h"

int HALF_SIZE = TILE_SIZE / 2;


// Creates a ray from user to the target. ex. enemy to player.
Ray Character::relationToTarget(  )
{
	Vector2 pos = position;
	Vector2 tar = target;
	Vector3 direction = Vector3Normalize( { tar.x - position.x, tar.y - position.y, 0 } );
	Ray lineOfSight = { { pos.x, pos.y, 0 }, direction };
	return lineOfSight;
}

// Updates the relation to the target and creates line of sight by checking for collision with walls or target.
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
			if ( closestDistance > sqrt( dx * dx + dy * dy ))
			{
				closestDistance = sqrt( dx * dx + dy * dy );
				closestCollision = walltile;
			}
		}
	}
	if ( closestDistance < getTargetDistance() )
	{
		return true;
	}
}

// NPC will move to their target's position but maintain a set distance.
// this can be used to keep melee enemies from stacking on the player, and to keep ranged enemies at range.
void Character::moveToTarget( Vector2 target, float distanceMaintained, std::vector<Rectangle> colliders )
{
	
	if ( Character::updateLOS( colliders ) && Character::getTargetDistance() > distanceMaintained)
	{
		updateDirection( target );
	}
		
}
