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

/*---------------------------------------------------------------------------------------------------------------------------------------
* transferObject() moves an object from this handler to another object handler
* - devon
* param int objId: id of the object being transfered
* param ObjectHandler &newHandler: the handler the object is being transfered to
* return: no return, alters data in this and newHandler
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::transferObject( int objId, ObjectHandler& newHandler )
{
   //this assumes the object exists in the current handler, if it doesn't it gives an error when ticking
   newHandler.allObjects[ objId ] = this->getObject( objId );
   newHandler.numberOfObjects++;

   this->allObjects.erase( objId );
   this->numberOfObjects--;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* removeObject() removes an object from the handler
* - devon
* param int objId: id of the object being removed
* return: no return
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::removeObject(int objId)
{
    allObjects.erase(objId);
    numberOfObjects--;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* tickAll() ticks all objects in the handler
* - someone else, devon
* param: no params
* return: no return
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::tickAll( const std::vector<Rectangle> collidables )
{
    //this iterator visits all the objects. using a copy because allObjects can be edited by onTick -devon
    std::map<int, GameObject*>objsCopy = allObjects;
    for ( auto it = objsCopy.begin( ); it != objsCopy.end( ); ++it )
    {
        it->second->onTick( collidables );
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* renderAll() renders all objects in the handler
* - someone else, devon
* return: no return
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::renderAll( )
{
   //this iterator visits all the objects
   for ( auto it = allObjects.begin( ); it != allObjects.end( ); ++it )
   {
      it->second->onRender( );
   }
}

int ObjectHandler::nextId = 1;  //this is shared between all object handlers. starts at 1 bc the player is always 0