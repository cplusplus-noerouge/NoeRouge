/* noeRouge - object.cpp
*  Worked on by: John, Ben A, Kaleb, Reese, Ethan */

#include "object.h"			//Class that all game objects inherit from
#include "objecthandler.h"  //Class that manages and keeps track of all GameObjects
#include <vector>			//Library for the vector data structure
#include "mapGen.h"		//Class that creates the dungeon map

class ObjectHandler;   //Forward Declaration for ObjectHandler class

/*-------------------------------------------------------------------------------------------------
*  The GameObject class is the super class for all game objects, includes Character, Player,
*  Enemy, Interactable, Ladder, Door, and HpPickup
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* GameObject( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Default Constructor, assigns the next available ID to the GameObject 
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
GameObject::GameObject( )
{
	id = ObjectHandler::takeNextId( );
}

	/*---------------------------------------------------------------------------------------------
	* GameObject( ObjectHandler* handler )
	* ---------------------------------------------------------------------------------------------
	* @names:  
	* @brief:  Constructor parameterized by an ObjectHandler pointer
	* @param:  handler -  ObjectHandler pointer to be assigned to the created GameObject object
	* @return: none
	*--------------------------------------------------------------------------------------------*/
GameObject::GameObject( ObjectHandler* handler )
{
   this->id = handler->takeNextId( );
   this->handler = handler;
}

	/*---------------------------------------------------------------------------------------------
	* GameObject( int id )
	* ---------------------------------------------------------------------------------------------
	* @names:  
	* @brief:  Constructor paramaterized by an ID number
	* @param:  id - The id number for the created GameObject object
	* @return: none
	*--------------------------------------------------------------------------------------------*/
GameObject::GameObject( int id )
{
	//now that the default constructor gives an id it's prob best to not use this constructor
	this->id = id;
}

	//Getters and Setters
int GameObject::getId( ){
	return this->id;
}
void GameObject::setId( int id )
{
	this->id = id;
}
ObjectHandler* GameObject::getHandler( )
{
   return this->handler;
}
void GameObject::setHandler( ObjectHandler* handler )
{
   this->handler = handler;
}

	/*---------------------------------------------------------------------------------------------
	* onTick( const std::vector<Rectangle> collidables )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Updates the state of a game object in a single frame, managed by child classes
	* @param:  collidables - The collection of collidables to check for GameObject collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void GameObject::onTick( const std::vector<Rectangle> collidables )
{
	printf( "I am a generic object, my id is %d, and I have been ticked\n", this->id );
	return;
}

	/*---------------------------------------------------------------------------------------------
	*onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Updates the state of a game object in a single frame, managed by child classes
	*          Renders a game object on screen, managed by child classes
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void GameObject::onRender( )
{
	return;
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/