/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* GameObject class
* John, Ben A, Kaleb, Reese, Ethan
* The super class for all game objects, includes Character, Player, Enemy, Interactable, Ladder, Door, and HpPickup
----------------------------------------------------------------------------------------------------------------------------------------*/
#include "object.h"
#include "objectHandler.h"
#include <vector>
#include "mapGen.h"

class ObjectHandler;   //Forward Declaration for ObjectHandler class

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Default Constructor
----------------------------------------------------------------------------------------------------------------------------------------*/
GameObject::GameObject( )
{
	id = ObjectHandler::takeNextId( );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Constructor parameterized by an ObjectHandler pointer
* @param ObjectHandler* handler : A pointer to an ObjectHandler object to be assigned to the created GameObject object
----------------------------------------------------------------------------------------------------------------------------------------*/
GameObject::GameObject( ObjectHandler* handler )
{
   this->id = handler->takeNextId( );
   this->handler = handler;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Constructor paramaterized by an ID number
* @param int id : The id number for the created GameObject object
----------------------------------------------------------------------------------------------------------------------------------------*/
GameObject::GameObject( int id )
{
	//now that the default constructor gives an id it's prob best to not use this constructor
	this->id = id;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Accessor Methods
----------------------------------------------------------------------------------------------------------------------------------------*/
int GameObject::getId( )
{
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

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Updates the state of a game object in a single frame, managed by child classes
* @param vector<Rectangle> collidables : The collection of collidables to check for GameObject collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void GameObject::onTick( const std::vector<Rectangle> collidables )
{
	printf( "I am a generic object, my id is %d, and I have been ticked\n", this->id );
	return;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Updates the state of a game object in a single frame, managed by child classes
* @param : Renders a game object on screen, managed by child classes
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void GameObject::onRender( )
{
	return;
}