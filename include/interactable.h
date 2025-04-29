#pragma once
#include "object.h"
#include "sprite.h"

/*
an object with a position and an "interact" method that the player can optionally call when nearby
each subclass of interactable needs to have it's own interact() method
- devon
*/
class Interactable : public GameObject
{
	private:
	Vector2 position;
	//other members probably:
	/*
	* Sprite sprite, string interactionName
	*/

	public:
	Interactable( );
	Interactable(Vector2 pos);

	virtual void interact( ) = 0;
	void onRender( ) override;
	void onTick( const std::vector<Rectangle> collidables ) override;

	Vector2 getPos( )
	{
		return position;
	}
	void setPos( Vector2 pos )
	{
		position = pos;
	}
};

/*
a ladder that when interacted with changes the floor the player is on by floorChange amount
- devon
*/
class Ladder : public Interactable
{
	private:
	int floorChange; //amount the floor index is changed by on interaction.

	public:
	Ladder( );
	Ladder(Vector2 pos, int floorChange);

	void interact( );
	int getFloorChange( )
	{
		return floorChange;
	}
	void setFloorChange(int changeVal)
	{
		floorChange = changeVal;
	}
};