#include <iostream>
#include "interactable.h"
#include "sprite.h"
#include "customCamera.h"

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

extern CustomCamera mainCamera;
void Interactable::onRender( )
{
	sprite.update(position, position.y);
	mainCamera.addToBuffer(&sprite);
}

void Interactable::onTick( const std::vector<Rectangle> collidables )
{
	//TODO (or probably its best to do this in the player's tick actually)
	/*
	* check for nearby player.
	  if player is within interaction range (TBD, prob a const),
			make a UI bubble thing telling the player they can press E (or whatever the interact key is)
			to do whatever the interaction is.
			then make it so the player can actually press E to call interact(), but it only activates the nearest interactable
				so maybe it's best that the player is checking for interactables, not the interactables checking for the player
	*/
}

//Ladder ==========================================
Ladder::Ladder( )
{
	floorChange = 0;
}

Ladder::Ladder( Vector2 pos, int floorChange):
	Interactable( pos )
{
	this->floorChange = floorChange;
	if (floorChange > 0)
	{
		sprite = Sprite("ladderUp", pos, pos.y);
	}
	else if (floorChange < 0)
	{
		sprite = Sprite("ladderDown", pos, pos.y);
	}
};

void Ladder::interact( )
{
	std::cout << "ladder interacted";
}

Ladder* ObjectHandler::createLadder( Vector2 position, int floorChange )
{
	Ladder* ladder = new Ladder( position, floorChange);
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
	//TODO change sprite. also needs to be some way for it to be added and removed from collidables
}

Door* ObjectHandler::createDoor(Vector2 position)
{
	Door* door = new Door(position);
	allObjects[door->getId()] = door; //add <id, object*> to the map
	this->numberOfObjects++;
	return door;
}