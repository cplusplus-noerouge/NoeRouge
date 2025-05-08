#pragma once
#include "globals.h"
#include "object.h"
#include "mapGen.h"
#include "player.h"
#include "enemy.h"
#include "generateTileSprites.h"

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

};