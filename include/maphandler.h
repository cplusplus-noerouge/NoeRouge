#pragma once
#include "globals.h"
#include "object.h"
#include "mapGen.h"
#include "player.h"

class MapHandler {
	private:
	Floor* floors[ Settings::NUM_OF_FLOORS ];
	static int nextId;
	int currentFloor;
	ObjectHandler* currentHandler;
	std::vector<Sprite> tileSprites;
	Player* player;
	public:

	MapHandler( );

	void genFloors( );

	Player* getPlayer( );
	std::vector<Enemy*> getEnemies(int num);
	//getKey()?

	void changeFloor( bool trueisdown );

	static int takeNextId( );

};