#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"


class Floor;
	
int MapHandler::nextId = 0;

MapHandler::MapHandler( )
{
	generateFloors( );
	this->floorIndex = 0;
	this->currentFloor = std::get<0>( floorMap[ floorIndex ] );
	this->tileSprites = std::get<1>( floorMap[ floorIndex ] );
}

int MapHandler::takeNextId( )
{
   return nextId++;
}

//-- Building the Handler

void MapHandler::generateFloors( )
{
	std::map<int, std::tuple<Floor*, std::vector<Sprite>, std::vector<Enemy*>>> floorMap;
	for ( int i = 0; i < Settings::NUM_OF_FLOORS; i++ )
	{
		Floor* floor = new Floor;
		std::vector<Sprite> tileSprites = generateTileSprites( floor );
		std::vector<Enemy*> enemieslist = generateEnemies( Settings::ENEMY_COUNT );
		floorMap.insert( { i,{floor,tileSprites,enemieslist} } );
	}
	this->floorMap = floorMap;
}

std::vector<Enemy*> MapHandler::generateEnemies( int num = 1 )
{
	std::vector<Enemy*> enemieslist;
	Floor* floor = std::get<0>( floorMap[ floorIndex ] );
	for ( int i = 0; i < num; i++ )
	{
		Vector2 enemySpawn = { 0,0 };
		//Vector2 enemySpawn = floor->getEnemySpawn( );
		Enemy* enemy = new Enemy( 0, 0, 0, { 0,0,0,0 } );
		//Enemy* enemy = currentHandler->createEnemy( enemySpawn, { Settings::TILE_SIZE, Settings::TILE_SIZE }, Settings::PLAYER_SPEED );
		enemieslist.push_back( enemy );
	}
	return enemieslist;
}

Player* MapHandler::getPlayer( )
{
	return this->player;
}

std::vector<Enemy*> MapHandler::getEnemies( )
{
	return std::get<2>( floorMap[ floorIndex ] );
}

std::vector<Sprite> MapHandler::getTileSprites( )
{
	return std::get<1>( floorMap[ floorIndex ] );
}

Floor* MapHandler::getCurrentFloor( )
{
return std::get<0>( floorMap[ floorIndex ] );
}


//-- During Gameplay

void MapHandler::changeFloor( bool trueisup )
{
	int nextFloor = floorIndex;
	( trueisup ) ? nextFloor++ : nextFloor--;

	//check that the new floor exists
	if ( nextFloor < 0 || nextFloor >= Settings::NUM_OF_FLOORS )
	{
		std::cout << "\nCurrent floor is " << floorIndex << ", insert disc 2 to go to " << nextFloor << "!";
	}
	else
	{
		Floor* floorNext = std::get<0>( floorMap[ nextFloor ] );

		float distanceToUpLadder = Vector2Distance( currentFloor->getLadderUpLocation( ), player->getPosition( ) );
		float distanceToDownLadder = Vector2Distance( currentFloor->getLadderDownLocation( ), player->getPosition( ) );
		if ( trueisup && distanceToUpLadder < Settings::TILE_SIZE )
		{
			Vector2 goingUp = floorNext->getLadderDownLocation( );
			this->player->setPosition( goingUp );
			this->tileSprites = std::get<1>( floorMap[ floorIndex ] );
			std::cout << "\n Moved from floor " << floorIndex << " to " << nextFloor;
			floorIndex = nextFloor;
			currentFloor = std::get<0>( floorMap[ floorIndex ] );
		}
		else if ( !trueisup && distanceToDownLadder < Settings::TILE_SIZE )
		{
			Vector2 goingDown = floorNext->getLadderUpLocation( );
			this->player->setPosition( goingDown );
			this->tileSprites = std::get<1>( floorMap[ floorIndex ] );
			std::cout << "\n Moved from floor " << floorIndex << " to " << nextFloor;
			floorIndex = nextFloor;
			currentFloor = std::get<0>( floorMap[ floorIndex ] );
		}

	}
}