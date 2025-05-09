#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"


MapHandler::MapHandler( )
{
	_floorMap = generateFloors( );
	_floorIndex = 0;
	_currentFloor = _floorMap[ _floorIndex ];
}

//-- Building the Handler

std::map<int, Floor*> MapHandler::generateFloors( )
{
	std::map<int, Floor*> floorMap;
	for ( int i = 0; i < Settings::NUM_OF_FLOORS; i++ )
	{
		Floor* floor = new Floor;
		floorMap.insert( { i,floor } );
	}
	return floorMap;
}


//-- During Gameplay

void MapHandler::tickAndRender( ){}

void MapHandler::changeFloor( bool trueisup )
{
	Player* player = static_cast<Player*>(_currentFloor->getObjHandler( )->getObject( 0 ));

	int nextFloor = _floorIndex;
	( trueisup ) ? nextFloor++ : nextFloor--;

	//check that the new floor exists
	if ( nextFloor < 0 || nextFloor >= Settings::NUM_OF_FLOORS )
	{
		std::cout << "\nCurrent floor is " << _floorIndex << ", insert disc 2 to go to " << nextFloor << "!";
	}
	else
	{
		Floor* floorNext = _floorMap[ nextFloor ];
		ObjectHandler* handlerNext = floorNext->getObjHandler( );

		//float distanceToUpLadder = Vector2Distance( _currentFloor->getLadderUpLocation( ), player->getPosition( ) ); //not needed anymore
		//float distanceToDownLadder = Vector2Distance( _currentFloor->getLadderDownLocation( ), player->getPosition( ) );
		
		if ( trueisup ) //&& distanceToUpLadder < Settings::TILE_SIZE 
		{
			Vector2 goingUp = floorNext->getLadderDownLocation( );
			_currentFloor->getObjHandler( )->transferObject( 0, *handlerNext );
			player->setPosition( goingUp );
			std::cout << "\n Moved from floor " << _floorIndex << " to " << nextFloor;
			_floorIndex = nextFloor;
			_currentFloor = _floorMap[ _floorIndex ];
		}
		else
		{
			Vector2 goingDown = floorNext->getLadderUpLocation( );
			_currentFloor->getObjHandler( )->transferObject( 0, *handlerNext );
			player->setPosition( goingDown );
			std::cout << "\n Moved from floor " << _floorIndex << " to " << nextFloor;
			_floorIndex = nextFloor;
			_currentFloor = _floorMap[ _floorIndex ];
		}
	}
}

// returns all the interactables on the current floor -devon
std::vector<Interactable*> MapHandler::getInteractables()
{
	std::vector<Interactable*> interactables;
	Interactable* casted;

	std::map<int, GameObject*> objs = getCurrentFloor()->getObjHandler()->allObjects;
	for (auto it = objs.begin(); it != objs.end(); ++it)
	{
		casted = dynamic_cast<Interactable*>(it->second);
		if (casted)
			interactables.push_back(casted);
	}

	return interactables;
}