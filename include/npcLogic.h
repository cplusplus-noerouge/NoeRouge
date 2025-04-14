#pragma once

#include "character.h"

class npcLogic : public Character
{
	void moveToPlayer( );
	void returnToSpawn( );
	void moveToTarget( );
	void maintainDistance( );
	void lineOfSight( );
};