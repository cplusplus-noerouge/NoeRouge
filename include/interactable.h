/* noeRouge - interactable.h
*  Worked on by: Devon */

#pragma once	//only include this .h once

#include "objecthandler.h"	//Class that manages and keeps track of all GameObjects
#include "sprite.h"         //Class that handles sprite objects

/*-------------------------------------------------------------------------------------------------
*  The Interactable class creates an object with a position and an "interact" method that the 
*  player can optionally call when nearby
*  each subclass of interactable needs to have it's own interact() method - devon
*------------------------------------------------------------------------------------------------*/
class Interactable : public GameObject
{
	protected:
	Vector2 position;	//coordinates in pixels
	Sprite sprite;		//sprite that gets rendered at the object's position

	public:
		
		//Default constructor for Interactable objects
	Interactable( );

		//Creates an Interactable object with a starting position
	Interactable(Vector2 pos);

		//Creates an Interactable object with a starting position and a texture
	Interactable(Vector2 pos, std::string texture);

		//subclasses will override this with their own interact functionality
	virtual void interact( ) = 0;	

		//renders the current state of the Interactable object
	void onRender( ) override;

		//Method stub for future functionality
	void onTick( const std::vector<Rectangle> collidables ) override;
		
		//Getters and Setters
	Vector2 getPos( )
	{
		return position;
	}
	void setPos( Vector2 pos )
	{
		position = pos;
	}
};

/*-------------------------------------------------------------------------------------------------
*  The Ladder class creates an object that when interacted with changes the floor the player is on, 
*  either up or down - devon
*------------------------------------------------------------------------------------------------*/
class Ladder : public Interactable
{
	private:
	bool isLadderUp;	//true if it's an up ladder, false if it's a down ladder

	public:
		//Default ladder constructor
	Ladder( );

		//Creates a ladder object with a starting location and whether it is an up ladder
	    //and assigns the appropriate texture
	Ladder(Vector2 pos, bool isLadderUp);

		//Changes which floor the player is on when a Ladder object is interacted with
	void interact( );

		//Renders the current state of the Ladder object
	void onRender( ) override;

		//Getters and Setters
	int getIsLadderUp( )
	{
		return isLadderUp;
	}
	void setIsLadderUp(int isLadderUp)
	{
		this->isLadderUp = isLadderUp;
	}
};

/*-------------------------------------------------------------------------------------------------
*  The Door class creates an object that can be interacted with to open and close it. it is 
*  impassable when closed - devon
*------------------------------------------------------------------------------------------------*/
class Door : public Interactable
{
private:
	bool isClosed;	//Whether the Door is in the open or closed state
	const std::string openTexture = "doorOpen";		//name of the "door open" texture 
	const std::string closedTexture = "doorClosed";	//name of the "door closed" texture  

public:
	
		//Renders the current state of the Ladder object
	Door();

		//Creates a Door object with coordinates and initialize the door closed
	Door(Vector2 pos);

		//Open or close a Door and it's neighbor Doors, update the Door's sprite
	void interact();

		//Getters and Setters
	bool getIsClosed()
	{
		return isClosed;
	}
	void setIsClosed(bool isClosed)
	{
		this->isClosed = isClosed;
	}
};

/*-------------------------------------------------------------------------------------------------
*  The HpPickup class creates an object  that the player can pick up to restore hp - devon
*------------------------------------------------------------------------------------------------*/
class HpPickup : public Interactable
{
private:
	static const int hpRestored = 1;	//amount of health restored by an HpPickUp object

public:

		//Method for future functionality
	HpPickup();
		
		//Called Interactables constructor to create a healthpack
	HpPickup(Vector2 pos);

		//plays sound effect and heals players health upon interaction with a healthpack
	void interact();
};

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above classes to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
* 
*	-Added comments to prototypes
*
*	-General formatting
*/
