#pragma once
#include <vector>
#include "globals.h"
#include "object.h"
#include "mapGen.h"
#include "player.h"
#include "enemy.h"
#include "generateTileSprites.h"
#include "interactable.h"

class MapHandler {
	private:
	
	std::map<int, Floor*> _floorMap;

	int _floorIndex;
	Floor* _currentFloor;
	
	std::map<int, Floor*> generateFloors( );

	public:

	MapHandler( );

	Floor* getCurrentFloor( ) { return _currentFloor; }

	void tickAndRender( );
	void changeFloor( bool trueisdown );

	std::vector<Interactable*> getInteractables();	//returns all the interactables on the current floor -devon
	std::vector<Enemy*> getEnemies();	    //returns all the enemies on the current floor -devon
};