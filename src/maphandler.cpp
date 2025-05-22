/* noeRouge - mapHandler.cpp
*  Worked on by: Devon, Andrew */

#pragma once	//only include this .h once

#include "globals.h"	//Class that handles global variables
#include "object.h"		//Class that all game objects inherit from
#include "maphandler.h"	//The .h file for this class

	//TEMPORARY sprite/texture for player win display, both need actual sprite
Sprite winScreen = Sprite( "Placeholder slash particle.png", Vector2 { 0, 0 }, 200000 );   
	//TEMPORARY sprite/texture for game over display
Sprite loseScreen = Sprite( "Placeholder block tile.png", Vector2 { 0, 0 }, 200000 );      


/*-------------------------------------------------------------------------------------------------
*  The MapHandler class acts as the driver for mapGen
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* MapHandler( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Constructor
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
MapHandler::MapHandler( )
{
	_floorMap = generateFloors( );
	_floorIndex = 0;
	_currentFloor = _floorMap[ _floorIndex ];
}

	/*---------------------------------------------------------------------------------------------
	* generateFloors( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  generates the floor maps for the game
	* @param:  none
	* @return: map<int, Floor*> - map containing the different floor maps
	*--------------------------------------------------------------------------------------------*/
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

	/*---------------------------------------------------------------------------------------------
	* tickAndRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  renders current map
	* @param:  none 
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void MapHandler::tickAndRender( )
{
	std::vector<Rectangle> boundaries;
	std::vector<Enemy*> enemies = getEnemies( );
	std::vector<Interactable*> interactables = getInteractables( );
	std::vector<Rectangle> walls = _currentFloor->getWalls( );


	for ( Enemy* enemy : enemies )
	{
		boundaries.push_back( { enemy->getPosition( ).x, enemy->getPosition( ).y, 
							  Settings::TILE_SIZE, Settings::TILE_SIZE } );
	}


	Door* casted;
	for ( auto it = interactables.begin( ); it != interactables.end( ); ++it )
	{
		casted = dynamic_cast< Door* >( *it );
		if ( casted && casted->getIsClosed( ) == true )
			boundaries.push_back( { casted->getPos( ).x, casted->getPos( ).y, 
								  Settings::TILE_SIZE, Settings::TILE_SIZE } );
	}


	boundaries.insert( boundaries.end( ), walls.begin( ), walls.end( ) );
	auto* handler = _currentFloor->getObjHandler( );     //handles obj handler path.      
	handler->tickAll( boundaries );
	handler->cleanupDeadEnemies( );                      //cleanup enemies
	handler->renderAll( );              
}
	/*---------------------------------------------------------------------------------------------
	* changeFloor( bool trueisup )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  change to another floor in the map
	* @param:  trueisup - by default the next floor will be the floor above current
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void MapHandler::changeFloor( bool trueisup )
{
	Player* player = static_cast<Player*>(_currentFloor->getObjHandler( )->getObject( 0 ));

	int nextFloor = _floorIndex;
	( trueisup ) ? nextFloor++ : nextFloor--;

		//check that the new floor exists
	if ( nextFloor < 0 || nextFloor >= Settings::NUM_OF_FLOORS )
	{
		std::cout << "\nCurrent floor is " << _floorIndex << ", insert disc 2 to go to " 
			      << nextFloor << "!";
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

	/*---------------------------------------------------------------------------------------------
	* getInteractables()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  returns all the interactables on the current floor -devon
	* @param:  none
	* @return: vector<Interactable*> - vector containing all Interactable objects
	*--------------------------------------------------------------------------------------------*/
std::vector<Interactable*> MapHandler::getInteractables()
{
	std::vector<Interactable*> interactables;
	Interactable* casted;

	std::map<int, GameObject*> objs = getCurrentFloor()->getObjHandler()->allObjects;
	for (auto it = objs.begin(); it != objs.end(); ++it)
	{
		casted = dynamic_cast< Interactable* >( it->second );
		if ( casted )
			interactables.push_back( casted );
	}
	return interactables;
}

	/*---------------------------------------------------------------------------------------------
	* MapHandler::getEnemies()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  returns all the enemies on the current floor -devon
	* @param:  none
	* @return: vector<Enemy*> - vector containing all current enemy objects
	*--------------------------------------------------------------------------------------------*/
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

	/*---------------------------------------------------------------------------------------------
	* getPlayer()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  gets a pointer to the current player object
	* @param:  none
	* @return: Player* - a pointer to the player object -devon
	*--------------------------------------------------------------------------------------------*/
Player* MapHandler::getPlayer() {
	return static_cast<Player*>(_currentFloor->getObjHandler()->getObject(0));
}

	/*---------------------------------------------------------------------------------------------
	* endGame( bool win )
	* ---------------------------------------------------------------------------------------------
	* @names:  Andrew
	* @brief:  displays a game over/win screen
	* @param:  win - whether or not the win condition has been met
	* @return: bool - true 
	* @note:   this function can only be reached by either of the win or lose conditions, or both, 
	*		   being true, so only one needs to be checked
	*--------------------------------------------------------------------------------------------*/
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

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/