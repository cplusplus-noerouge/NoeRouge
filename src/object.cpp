#include "object.h"
#include <vector>

/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* GameObject class
* John, Ben A, Kaleb, Reese, Ethan
----------------------------------------------------------------------------------------------------------------------------------------*/\

// ----- GameObject -----

GameObject::GameObject( )
{
	id = ObjectHandler::takeNextId( );
}

GameObject::GameObject( int id )
{
	//now that the default constructor gives an id it's prob best to not use this constructor
	this->id = id;
}

int GameObject::getId( )
{
	return this->id;
}

void GameObject::setId( int id )
{
	this->id = id;
}

void GameObject::onTick( const std::vector<Rectangle> collidables )
{
	printf( "I am a generic object, my id is %d, and I have been ticked\n", this->id );
	return;
}

void GameObject::onRender( )
{
	return;
}



// ----- ObjectHandler -----

class GameObject* ObjectHandler::createObject( )
{
	class GameObject* newObject = new GameObject( nextId++ );
	allObjects[ newObject->getId( ) ] = newObject; //add <id, object*> to the map
	this->numberOfObjects++;
	return newObject;
}

class GameObject* ObjectHandler::getObject( int id )
{
	return this->allObjects[ id ];
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* transferObject() moves an object from this handler to another object handler
* - devon
* param int objId: id of the object being transfered
* param ObjectHandler &newHandler: the handler the object is being transfered to
* return: alters data in this and newHandler
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::transferObject( int objId, ObjectHandler& newHandler )
{
	//this assumes the object exists in the current handler, if it doesn't it gives an error when ticking
	newHandler.allObjects[ objId ] = this->getObject( objId );
	newHandler.numberOfObjects++;

	this->allObjects.erase( objId );
	this->numberOfObjects--;
}

void ObjectHandler::tickAll( const std::vector<Rectangle> collidables )
{
	//this iterator gets all the objects
	for ( auto it = allObjects.begin( ); it != allObjects.end( ); ++it )
	{
		it->second->onTick( collidables );
	}
}

void ObjectHandler::renderAll( )
{
	//this iterator gets all the objects
	for ( auto it = allObjects.begin( ); it != allObjects.end( ); ++it )
	{
		it->second->onRender( );
	}
}

int ObjectHandler::nextId = 1;  //this is shared between all object handlers. starts at 1 bc the player is always 0