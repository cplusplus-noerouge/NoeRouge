/* noeRouge - object.h
*  Worked on by: John, Ben A, Kaleb, Reese, Ethan */

#pragma once	//only include this .h once

#include <cstdio>			//Library for performing standard input and output operations
#include <vector>			//Library for the vector data structure
#include <map>				//Library for the map data structure
#include <raylib.h>			//Library with animation, rendering, interactive, and sound tools
#include "objecthandler.h"  //Class that manages and keeps track of all GameObjects

/*-------------------------------------------------------------------------------------------------
*  Forward Declaration for ObjectHandler class
*------------------------------------------------------------------------------------------------*/
class ObjectHandler;	

/*-------------------------------------------------------------------------------------------------
*  The GameObject class is the super class for all game objects, includes Character, Player, 
*  Enemy, Interactable, Ladder, Door, and HpPickup
*------------------------------------------------------------------------------------------------*/
class GameObject
{
	private:

	int id;                  //ID number for the GameObject object

	protected:

	ObjectHandler* handler;  //A pointer to an ObjectHandler object

	public:

		//Default Constructor
	GameObject( );           

		//Constructor parameterized by an ObjectHandler pointer
	GameObject( ObjectHandler* handler );     

		//Constructor paramaterized by an ID number
	GameObject( int id );             

		//GameObject's Destructor
	~GameObject( )     
	{

	}
	
		//Getter for the Object's ID number
	int getId( );   

		//Getter for the ObjectHandler pointer
	ObjectHandler* getHandler( );             

		//Setter for the Object's ID number
	void setId( int id );                             

		//Setter for the ObjectHandler pointer
	void setHandler( ObjectHandler* handler );                        

		//Updates the state of a game object in a single frame, managed by child classes
	virtual void onTick( const std::vector<Rectangle> collidables ); 

		//Renders a game object on screen, managed by child classes
	virtual void onRender( );                                          
};

/*  Changes made during commenting by Evan:
*
*	-Added inline comments to #includes
*
*	-General formatting
*/