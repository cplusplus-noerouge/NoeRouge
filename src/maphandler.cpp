#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"
#include "generateTileSprites.h"

class Floor;
	
int MapHandler::nextId = 0;

MapHandler::MapHandler( ) : floors {}, currentHandler ( nullptr ), player ( nullptr )
{
	genFloors( );
	this->currentFloor = 0;
	this->currentHandler = this->floors[ currentFloor ]->getObjHandler( );
}

int MapHandler::takeNextId( )
{
   return nextId++;
}

void MapHandler::genFloors( )
{
	for ( int i = 0; i < Settings::NUM_OF_FLOORS; i++ )
	{
		this->floors[ i ] = new Floor;
	}
}

Player* MapHandler::getPlayer( )
{
	return player;
}

//std::vector<Enemy*> MapHandler::getEnemies(int num = 3) //num in case we want to vary it per level.
//{
//	return null;
//}

//getKey() { }?

void MapHandler::changeFloor( bool trueisup )
{
	int nextFloor = currentFloor;
	( trueisup ) ? nextFloor++ : nextFloor--;

	//check that the new floor exists
	if ( nextFloor == -1 || nextFloor > Settings::NUM_OF_FLOORS )
	{
		std::cout << "\nCurrent floor is " << currentFloor << ", insert disc 2 to go to " << nextFloor << "!";
	}
	else
	{
		ObjectHandler* nextHandler = floors[ nextFloor ]->getObjHandler( );
		floors[ currentFloor ]->getObjHandler( )->transferObject( 0, *nextHandler );

		Player* player = dynamic_cast< Player* >( nextHandler->getObject( 0 ) );
		( trueisup ) ? player->setPosition( floors[ nextFloor ]->getLadderDownLocation( ) ) : player->setPosition( floors[ nextFloor ]->getLadderUpLocation( ) );

		tileSprites = generateTileSprites( floors[ nextFloor ] );
		std::cout << "\n Moved from floor " << currentFloor << " to " << nextFloor;
	}
}