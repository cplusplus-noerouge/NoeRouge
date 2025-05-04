#pragma once
#include "globals.h"
#include "object.h"
#include "maphandler.h"
#include "generateTileSprites.h"
#include "enemy.h"

class Floor;
	
int MapHandler::nextId = 0;

MapHandler::MapHandler( ) : floors {}, currentHandler ( nullptr ), player ( nullptr )
{
	genFloors( );
	this->currentFloor = 0;
	this->currentHandler = this->floors[ currentFloor ]->getObjHandler( );
	this->player = dynamic_cast< Player* >( currentHandler->getObject( 0 ) );
}

int MapHandler::takeNextId( )
{
   return nextId++;
}

void MapHandler::genFloors( )
{
	for ( int i = 0; i < Settings::NUM_OF_FLOORS; i++ )
	{
		this->floors[ i ] = new Floor;
		std::vector<Enemy*> getEnemies( Settings::ENEMY_COUNT );
		floors[ i ]->getObjHandler( );
	}
}

Player* MapHandler::getPlayer( )
{
	return player;
}

std::vector<Enemy*> MapHandler::getEnemies( int num = 1 )
{
	std::vector<Enemy*> enemieslist;
	for ( int i = 0; i < num; i++ )
	{
		Vector2 enemySpawn = floors[ currentFloor ]->getEnemySpawn( );
		Enemy* enemy = currentHandler->createEnemy( enemySpawn, { Settings::TILE_SIZE, Settings::TILE_SIZE }, Settings::PLAYER_SPEED );
		enemieslist.push_back( enemy );
	}
	return enemieslist;
}

//getKey() { }?

void MapHandler::changeFloor( bool trueisup )
{
	int nextFloor = currentFloor;
	( trueisup ) ? nextFloor++ : nextFloor--;

	//check that the new floor exists
	if ( nextFloor < 0 || nextFloor >= Settings::NUM_OF_FLOORS )
	{
		std::cout << "\nCurrent floor is " << currentFloor << ", insert disc 2 to go to " << nextFloor << "!";
	}
	else
	{
		ObjectHandler* nextHandler = floors[ nextFloor ]->getObjHandler( );
		floors[ currentFloor ]->getObjHandler( )->transferObject( 0, *nextHandler );

		this->player = dynamic_cast< Player* >( nextHandler->getObject( 0 ) );
		Vector2 goingUp = floors[ nextFloor ]->getLadderDownLocation( );
		Vector2 goingDown = floors[ nextFloor ]->getLadderUpLocation( );
		( trueisup ) ? player->setPosition( goingUp ) : player->setPosition( goingDown );

		tileSprites = generateTileSprites( floors[ nextFloor ] );
		std::cout << "\n Moved from floor " << currentFloor << " to " << nextFloor;
		currentFloor = nextFloor;
	}
}