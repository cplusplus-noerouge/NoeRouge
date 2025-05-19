/* noeRouge - mapHandler.h
*  Worked on by: Devon, Andrew */

#pragma once	//only include this .h once

#include <vector>				//Library for the vector data structure
#include "globals.h"			//Class that handles global variables
#include "object.h"				//Class that all game objects inherit from
#include "mapGen.h"				//Class that creates the dungeon map
#include "player.h"				//Class that handles the player movement and functionality
#include "enemy.h"				//Class that represents the enemy characters that populate the map
#include "generateTileSprites.h"//Class that generates sprites for every tile in the map
#include "interactable.h"	    //Class that creates interactable objects

/*-------------------------------------------------------------------------------------------------
*  The MapHandler class acts as the driver for mapGen
*------------------------------------------------------------------------------------------------*/
class MapHandler {
	private:
	
	std::map<int, Floor*> _floorMap;

	int _floorIndex;
	Floor* _currentFloor;	
	
		//generates the floor maps for the game
	std::map<int, Floor*> generateFloors( );

	public:
		//MapHandler constructor
	MapHandler( );
		
		//returns the floor that the player is on
	Floor* getCurrentFloor( ) { return _currentFloor; }

		//returns all the interactables on the current floor -devon
	std::vector<Interactable*> getInteractables();	

		//returns all the enemies on the current floor -devon
	std::vector<Enemy*> getEnemies();			    

		//get a pointer to the player object -devon
	Player* getPlayer();							

		//renders current map
	void tickAndRender( );

		//change to another floor in the map
	void changeFloor( bool trueisdown );

		//displays a game over/win screen
	bool MapHandler::endGame( bool win ); // - Andrew
};

/*  Changes made during commenting by Evan:
*
*	-Added inline comments to #includes
* 
*	-General formatting
* 
*	-Commented prototypes
*/