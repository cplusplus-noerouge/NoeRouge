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
	protected:
	Vector2 position;				//coordinates in pixels
	Sprite sprite;					//sprite that gets rendered at the object's position

	public:
	Interactable( );
	Interactable(Vector2 pos);
	Interactable(Vector2 pos, std::string texture);

	virtual void interact( ) = 0;	//subclasses will override this with their own interact functionality
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
a ladder that when interacted with changes the floor the player is on, either up or down
- devon
*/
class Ladder : public Interactable
{
	private:
	bool isLadderUp;	//true if it's an up ladder, false if it's a down ladder

	public:
	Ladder( );
	Ladder(Vector2 pos, bool isLadderUp);

	void interact( );
	void onRender( ) override;
	int getIsLadderUp( )
	{
		return isLadderUp;
	}
	void setIsLadderUp(int isLadderUp)
	{
		this->isLadderUp = isLadderUp;
	}
};

/*
a door that can be interacted with to open and close it. it is impassable when closed
- devon
*/
class Door : public Interactable
{
private:
	bool isClosed;
	const std::string openTexture = "doorOpen";			//name of the texture displayed when the door is open
	const std::string closedTexture = "doorClosed";		//name of the texture displayed when the door is closed

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