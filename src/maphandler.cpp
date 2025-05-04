#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"

class Floor;

MapHandler::MapHandler( )
{

	this->floors = genFloors( );
	this->currentFloor = 0;
}

Floor* MapHandler::genFloors( )
{
	Floor* floors[ Settings::NUM_OF_FLOORS ];
	for ( int i = 0; i < Settings::NUM_OF_FLOORS; i++ )
	{
		floors[ i ] = new Floor;
	}
	return floors;
}

Player* MapHandler::getPlayer( )
{
	return 
}

std::vector<Enemy*> MapHandler::getEnemies(int num = 3) //num in case we want to vary it per level.
{
	
}

//getKey() { }?

void MapHandler::changeFloor( )
{

}