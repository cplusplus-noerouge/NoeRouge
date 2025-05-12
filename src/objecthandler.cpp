/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* ObjectHandler class
* John, Ben A, Kaleb, Reese, Ethan, Devon
* A class that manages and keeps track of all GameObject objects in the game.
----------------------------------------------------------------------------------------------------------------------------------------*/
#include "object.h"
#include "player.h"
#include "mapGen.h"

/*---------------------------------------------------------------------------------------------------------------------------------------
* createObject()
* @brief : Creates a GameObject object and adds it to allObjects.
* param : none
* return GameObject* : A pointer to the created GameObject.
----------------------------------------------------------------------------------------------------------------------------------------*/
GameObject* ObjectHandler::createObject( )
{
   GameObject* newObject = new GameObject( );
   allObjects[ newObject->getId( ) ] = newObject;   //add <id, object*> to the map
   this->numberOfObjects++;
   return newObject;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* getObject()
* @brief : Returns the GameObject pointer with the passed id number.
* param int id : The id number of the GameObject to return
* return GameObject* : The GameObject pointer stored in allObjects with the passed id number.
----------------------------------------------------------------------------------------------------------------------------------------*/
GameObject* ObjectHandler::getObject( int id )
{
   return this->allObjects[ id ];
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* transferObject()
* Devon
* @brief : Transfers a GameObject pointer from this ObjectHandler to another.
* @param int objId : id number of the GameObject being transfered.
* @param ObjectHandler& newHandler : A reference to the ObjectHandler object the GameObject is being transferred to.
* @return : none
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
* removeObject()
* Devon
* @brief : Removes the GameObject pointer from this ObjectHandler.
* @param int objId : id number of the GameObject being removed.
* @return: none
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::removeObject(int objId)
{
    allObjects.erase(objId);
    numberOfObjects--;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* tickAll()
* Devon
* @brief : Calls the onTick function for all objects in the handler.
* @param vector<Rectangle> collidables : The collection of collidables to check for collision.
* @return : none
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
* renderAll()
* Devon
* @brief : Calls the onRender function for all objects in the handler.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::renderAll( )
{
      //this iterator visits all the objects
   for ( auto it = allObjects.begin( ); it != allObjects.end( ); ++it )
   {
      it->second->onRender( );
   }
}
/*---------------------------------------------------------------------------------------------------------------------------------------
 * cleanupDeadEnemies()
 * Kaleb Flowers
 * @brief  Loops through allObjects and deletes any enemies flagged with isDead = true.
 *         Called after tickAll() to avoid deleting objects mid-frame.
 * @param Enemy* enemy : A pointer to the Enemy object to be deleted.
 * @return : none
 ---------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::enemyKilled( Enemy* enemy )
{
   int id = enemy->getId( );

   if ( allObjects.count( id ) )
   {
      delete allObjects[ id ];         // Free memory
      allObjects.erase( id );          // Remove from map
      numberOfObjects--;
   }
}
/*----------------------------------------------------------------------------------------------------------------------------------------
 * cleanupDeadEnemies()
 * Kaleb Flowers
 * @brief  Deletes enemies flagged as 'isDead' after the frame logic has completed.
 *         Prevents memory leaks and avoids crashing from use-after-free.
 * @param : none
 * @return : none
 --------------------------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::cleanupDeadEnemies()
{
    std::vector<int> toDelete;

    for (auto& [id, obj] : allObjects)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (enemy && enemy->isDead)
        {
            toDelete.push_back(id);
        }
    }

    for (int id : toDelete)
    {
        delete allObjects[id];
        allObjects.erase(id);
        numberOfObjects--;
    }
}

int ObjectHandler::nextId = 1;   //this is shared between all object handlers. starts at 1 because the player is always 0