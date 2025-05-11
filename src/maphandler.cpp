#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"


Sprite winScreen = Sprite( "Placeholder slash particle.png", Vector2 { 0, 0 }, 200000 );       //TEMPORARY sprite/texture for player win display, both need actual sprite
Sprite loseScreen = Sprite( "Placeholder block tile.png", Vector2 { 0, 0 }, 200000 );      //TEMPORARY sprite/texture for game over display


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

void MapHandler::tickAndRender( )
{
	std::vector<Rectangle> boundaries;
	std::vector<Enemy*> enemies = getEnemies( );
	std::vector<Interactable*> interactables = getInteractables( );
	std::vector<Rectangle> walls = _currentFloor->getWalls( );

	
	for ( Enemy* enemy : enemies )
	{
		boundaries.push_back( { enemy->getPosition( ).x, enemy->getPosition( ).y, Settings::TILE_SIZE, Settings::TILE_SIZE } );
	}
	

	Door* casted;
	for ( auto it = interactables.begin( ); it != interactables.end( ); ++it )
	{
		casted = dynamic_cast< Door* >( *it );
		if ( casted && casted->getIsClosed( ) == true )
			boundaries.push_back( { casted->getPos( ).x, casted->getPos( ).y, Settings::TILE_SIZE, Settings::TILE_SIZE } );
	}


	boundaries.insert( boundaries.end( ), walls.begin( ), walls.end( ) );

	_currentFloor->getObjHandler( )->tickAll( boundaries );
	_currentFloor->getObjHandler( )->renderAll( );
}

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

// returns all the enemies on the current floor -devon
std::vector<Enemy*> MapHandler::getEnemies()
{
	std::vector<Enemy*> enemies;
	Enemy* casted;

	std::map<int, GameObject*> objs = getCurrentFloor()->getObjHandler()->allObjects;
	for (auto it = objs.begin(); it != objs.end(); ++it)
	{
		casted = dynamic_cast<Enemy*>(it->second);
		if (casted)
			enemies.push_back(casted);
	}

	return enemies;
}

// returns a pointer to the player object -devon
Player* MapHandler::getPlayer() {
	return static_cast<Player*>(_currentFloor->getObjHandler()->getObject(0));
}

/*---------------------------------------------------------------------------------------------------------------------
* endGame() displays a game over/win screen
* - Andrew
* param bool win: whether or not the win condition has been met
* this function can only be reached by either of the win or lose conditions, or both, being true,
*    so only one needs to be checked
* return: sets gameEnd to true after displaying game over screen
---------------------------------------------------------------------------------------------------------------------*/
bool MapHandler::endGame( bool win )
{
	if ( win )
	{
		winScreen.render( Vector2 { 0,0 } );
	}
	else
	{
		loseScreen.render( Vector2 { 0,0 } );
	}
	return true;
}