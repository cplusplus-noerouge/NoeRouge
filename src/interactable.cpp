#include <iostream>
#include "interactable.h"

//interactable
Interactable::Interactable( )
{
	position = { 0,0 };
}

Interactable::Interactable(Vector2 pos)
{
	position = pos;
}

void Interactable::onRender( )
{
	//TODO, render the sprite
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

//ladder
Ladder::Ladder( )
{
	floorChange = 0;
}

Ladder::Ladder( Vector2 pos, int floorChange):
	Interactable( pos )
{
	this->floorChange = floorChange;
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