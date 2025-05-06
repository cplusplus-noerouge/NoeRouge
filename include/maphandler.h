#pragma once
#include "globals.h"
#include "object.h"
#include "mapGen.h"
#include "player.h"
#include "enemy.h"
#include "generateTileSprites.h"

class MapHandler {
	private:
	
	std::map<int, std::tuple<Floor*, std::vector<Sprite>, std::vector<Enemy*>>> floorMap;
	static int nextId;
	Player* player;

	int floorIndex;
	Floor* currentFloor;
	std::vector<Sprite> tileSprites;
	

	public:

	MapHandler( );

	void generateFloors( );
	std::vector<Enemy*> generateEnemies( int num );

	Player* getPlayer( );
	std::vector<Enemy*> getEnemies( );
	std::vector<Sprite> getTileSprites();
	Floor* getCurrentFloor( );
	//getKey()?

	void onTick( );
	void onRender( );
	void changeFloor( bool trueisdown );

	static int takeNextId( );

};