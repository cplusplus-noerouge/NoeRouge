#pragma once
#include "globals.h"
#include "object.h"
#include "mapGen.h"
#include "player.h"

class MapHandler {
	private:
	Floor* floors[ Settings::NUM_OF_FLOORS ];
	int currentFloor;
	ObjectHandler* handler;
	std::vector<Sprite> tileSprites;

	public:

	MapHandler( );

	Player* getPlayer( );
	std::vector<Enemy*> getEnemies(int num = 3);
	//getKey()?

	void changeFloor( );

};