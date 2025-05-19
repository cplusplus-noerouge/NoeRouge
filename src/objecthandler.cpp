/* noeRouge - objectHandler.cpp
*  Worked on by: John, Ben A, Kaleb, Reese, Ethan, Devon */

#include "object.h"		//Class that all game objects inherit from
#include "player.h"		//Class that handles the player movement and functionality
#include "mapGen.h"		//Class that creates the dungeon map

/*-------------------------------------------------------------------------------------------------
*  The ObjectHandler class manages and keeps track of all GameObject objects in the game
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* createObject( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Creates a GameObject object and adds it to allObjects.
	* @param:  none
	* @return: GameObject* - A pointer to the new GameObject
	*--------------------------------------------------------------------------------------------*/
GameObject* ObjectHandler::createObject( )
{
	GameObject* newObject = new GameObject( );
	allObjects[ newObject->getId( ) ] = newObject;   //add <id, object*> to the map
	this->numberOfObjects++;
	return newObject;
}

	/*---------------------------------------------------------------------------------------------
	* getObject( int id )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Returns the GameObject pointer with the passed id number
	* @param:  id - The id number of the GameObject to be returned
	* @return: GameObject* - The GameObject pointer that corresponds to id in allObjects
	*--------------------------------------------------------------------------------------------*/
GameObject* ObjectHandler::getObject( int id )
{
	return this->allObjects[ id ];
}

	/*---------------------------------------------------------------------------------------------
	* transferObject( int objId, ObjectHandler& newHandler )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Transfers a GameObject pointer from this ObjectHandler to another.
	* @param:  objId - id number of the GameObject being transfered.
	* @param:  newHandler - A reference to the ObjectHandler object the GameObject is being 
	*		   transferred to.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::transferObject( int objId, ObjectHandler& newHandler )
{
	  //assume the object exists in the current handler, if not gives error when ticking
	newHandler.allObjects[ objId ] = this->getObject( objId );
	newHandler.numberOfObjects++;

	this->allObjects.erase( objId );
	this->numberOfObjects--;
}

	/*---------------------------------------------------------------------------------------------
	* removeObject(int objId)
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  Removes the GameObject pointer from this ObjectHandler.
	* @param:  objId - id number of the GameObject being removed.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::removeObject( int objId )
{
	allObjects.erase( objId );
	numberOfObjects--;
}

	/*---------------------------------------------------------------------------------------------
	* tickAll( const std::vector<Rectangle> collidables )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  Calls the onTick function for all objects in the handler.
	* @param:  collidables - The collection of collidables to check for collision.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::tickAll( const std::vector<Rectangle> collidables )
{
	   //iterator visits all the objects. using a copy because allObjects can be edited by onTick -devon
	std::map<int, GameObject*>objsCopy = allObjects;
	for ( auto it = objsCopy.begin( ); it != objsCopy.end( ); ++it )
	{
		it->second->onTick( collidables );
	}
}

	/*---------------------------------------------------------------------------------------------
	* renderAll( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  Calls the onRender function for all objects in the handler.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::renderAll( )
{
	  //this iterator visits all the objects
	for ( auto it = allObjects.begin( ); it != allObjects.end( ); ++it )
	{
		it->second->onRender( );
	}
}
	/*---------------------------------------------------------------------------------------------
	* enemyKilled( Enemy* enemy )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Loops through allObjects and deletes any enemies flagged with isDead = true.
	*          Called after tickAll() to avoid deleting objects mid-frame.
	* @param:  enemy - A pointer to the Enemy object to be deleted.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::enemyKilled( Enemy* enemy )
{
	int id = enemy->getId( );

	if ( allObjects.count( id ) )
	{
		delete allObjects[ id ];	// Free memory
		allObjects.erase( id );     // Remove from map
		numberOfObjects--;
	}
}

	/*---------------------------------------------------------------------------------------------
	* cleanupDeadEnemies()
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Deletes enemies flagged as 'isDead' after the frame logic has completed.
	 *         Prevents memory leaks and avoids crashing from use-after-free.
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ObjectHandler::cleanupDeadEnemies( )
{
	std::vector<int> toDelete;

	for ( auto& [id, obj] : allObjects )
	{
		Enemy* enemy = dynamic_cast< Enemy* >( obj );
		if ( enemy && enemy->isDead )
		{
			toDelete.push_back( id );
		}
	}

	for ( int id : toDelete )
	{
		delete allObjects[ id ];
		allObjects.erase( id );
		numberOfObjects--;
	}
}
	//this is shared between all object handlers. starts at 1 because the player is always 0
int ObjectHandler::nextId = 1; 

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/