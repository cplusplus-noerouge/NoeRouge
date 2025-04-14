#include "character.h"


bool Character::lineOfSight( Vector2 Target )
{
	return false;
}

void Character::moveToTarget( Vector2 target, float distanceMaintained )
{
	
	if ( Character::lineOfSight( target ) && getTargetDistance() > distanceMaintained)
	{
		updateDirection( target );
	}
		
}
