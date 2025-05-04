#include "object.h"
#include "player.h"
#include "mapGen.h"

GameObject* ObjectHandler::createObject( )
{
   GameObject* newObject = new GameObject( nextId++ );
   allObjects[ newObject->getId( ) ] = newObject; //add <id, object*> to the map
   this->numberOfObjects++;
   return newObject;
}

GameObject* ObjectHandler::getObject( int id )
{
   return this->allObjects[ id ];
}

Floor* ObjectHandler::getFloor( )
{
   return this->floor;
}

void ObjectHandler::setFloor( Floor* floor )
{
   this->floor = floor;
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

void ObjectHandler::playerCreate( )
{
   Vector2 spawn = getFloor( )->getLadderDownLocation( );
   //Player* player = new Player( spawn, this );
}