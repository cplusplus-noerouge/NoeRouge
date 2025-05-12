/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* GameObject class
* John, Ben A, Kaleb, Reese, Ethan
* The super class for all game objects, includes Character, Player, Enemy, Interactable, Ladder, Door, and HpPickup 
----------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include "raylib.h"
#include "objectHandler.h"

class ObjectHandler;                                                 //Forward Declaration for ObjectHandler class

class GameObject
{
	private:

	int id;                                                           //ID number for the GameObject object

	protected:

	ObjectHandler* handler;                                           //A pointer to an ObjectHandler object

	public:

	GameObject( );                                                    //Default Constructor
	GameObject( ObjectHandler* handler );                             //Constructor parameterized by an ObjectHandler pointer
	GameObject( int id );                                             //Constructor paramaterized by an ID number
	~GameObject( )                                                    //GameObject's Destructor
	{

	}
	int getId( );                                                      //Getter for the Object's ID number
	ObjectHandler* getHandler( );                                      //Getter for the ObjectHandler pointer
	void setId( int id );                                              //Setter for the Object's ID number
	void setHandler( ObjectHandler* handler );                         //Setter for the ObjectHandler pointer

	virtual void onTick( const std::vector<Rectangle> collidables );   //Updates the state of a game object in a single frame, managed by child classes
	virtual void onRender( );                                          //Renders a game object on screen, managed by child classes
};