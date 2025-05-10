/*
Interactable: an object with a position and an "interact" method that the player can optionally call when nearby
Ladder: interactable that changes the player's floor
Door: interactable that changes its own state, open or closed
- devon
*/
#include <iostream>
#include "interactable.h"
#include "sprite.h"
#include "customCamera.h"
#include "mapHandler.h"

extern CustomCamera mainCamera;
extern MapHandler* mapHandler;

//Interactable ==========================================
Interactable::Interactable( )
{
	position = { 0,0 };
	sprite = Sprite("missingTexture", position, position.y);
}
Interactable::Interactable(Vector2 pos)
{
	position = pos;
	sprite = Sprite("missingTexture", position, position.y);
}
Interactable::Interactable(Vector2 pos, std::string texture)
{
	position = pos;
	sprite = Sprite(texture, position, position.y);
}

void Interactable::onRender( )
{
	sprite.update(position, 0);
	mainCamera.addToBuffer(&sprite);
}

void Interactable::onTick( const std::vector<Rectangle> collidables )
{
	//do nothing
}

//Ladder ==========================================
Ladder::Ladder( )
{
	isLadderUp = false;
}

Ladder::Ladder( Vector2 pos, bool isLadderUp):
	Interactable( pos )
{
	this->isLadderUp = isLadderUp;
	if (isLadderUp)
	{
		sprite = Sprite( "ladderUp", pos, pos.y );
	}
	else
	{
		sprite = Sprite("ladderDown", pos, pos.y);
	}
};

void Ladder::interact( )
{
	//std::cout << "interacted ladder is up -> " << isLadderUp << "\n";
	mapHandler->changeFloor(isLadderUp);
}

void Ladder::onRender( )
{
	sprite.update( Vector2Subtract( position, { 0, 8 } ), position.y - 8 );
	mainCamera.addToBuffer( &sprite );
}

//creates a new ladder in 'this' object handler
Ladder* ObjectHandler::createLadder( Vector2 position, bool isLadderUp)
{
	Ladder* ladder = new Ladder( position, isLadderUp);
	allObjects[ ladder->getId( ) ] = ladder; //add <id, object*> to the map
	this->numberOfObjects++;
	return ladder;
}

//Door ==========================================
Door::Door()
{
	isClosed = true;
}

Door::Door(Vector2 pos) :
	Interactable(pos, "doorClosed")
{
	isClosed = true;
}

void Door::interact()
{
	isClosed = !isClosed;

	if (isClosed)
	{
		sprite.setTexture(closedTexture);
	}
	else
	{
		sprite.setTexture(openTexture);
	}
	//TODO add/remove from collidables
}

//creates a new ladder in 'this' object handler
Door* ObjectHandler::createDoor(Vector2 position)
{
	Door* door = new Door(position);
	allObjects[door->getId()] = door; //add <id, object*> to the map
	this->numberOfObjects++;
	return door;
}