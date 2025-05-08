#pragma once
#include "objecthandler.h"
#include "sprite.h"

/*
an object with a position and an "interact" method that the player can optionally call when nearby
each subclass of interactable needs to have it's own interact() method
- devon
*/
class Interactable : public GameObject
{
	private:
	/*
	* string interactionName  //for the UI, this will prob be a thing?
	*/

	protected:
	Vector2 position;
	Sprite sprite;

	public:
	Interactable( );
	Interactable(Vector2 pos);
	Interactable(Vector2 pos, std::string texture);

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
a ladder that (TODO->) when interacted with changes the floor the player is on by floorChange amount
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
	void onRender( ) override;
	int getFloorChange( )
	{
		return floorChange;
	}
	void setFloorChange(int changeVal)
	{
		floorChange = changeVal;
	}
};

/*
a door that (TODO->) can be interacted with to open and close it. it is impassable when closed
- devon
*/
class Door : public Interactable
{
private:
	bool isClosed;
	//bool isLocked		//future thing?

public:
	Door();
	Door(Vector2 pos);

	void interact();
	bool getIsClosed()
	{
		return isClosed;
	}
	void setIsClosed(bool isClosed)
	{
		this->isClosed = isClosed;
	}
};