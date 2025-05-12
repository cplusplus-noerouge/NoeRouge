/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* ObjectHandler class
* John, Ben A, Kaleb, Reese, Ethan, Devon
* A class that manages and keeps track of all GameObject objects in the game.
----------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include "object.h"

class GameObject;   //Forward declaration for the GameObject class
class Enemy;        //Forward declaration for the Enemy class

class ObjectHandler
{
   private:

   static int nextId;                        //The ID number value for the next added GameObject object
   
   public:

   int numberOfObjects;                      //Total number of GameObject objects in the ObjectHandler object
   std::map<int, GameObject* > allObjects;   //A hashmap that stores an ID number with a GameObject pointer

   /*---------------------------------------------------------------------------------------------------------------------------------------
    * takeNextId( )
    * @brief : Increments nextId and then returns it's value
    * @param : none
    * @return : Incremented nextId
    ----------------------------------------------------------------------------------------------------------------------------------------*/
   static int takeNextId( )
   {
      return ++nextId;
   }

  /*---------------------------------------------------------------------------------------------------------------------------------------
   * @brief : Default Constructor
   ----------------------------------------------------------------------------------------------------------------------------------------*/
   ObjectHandler( )
   {
      this->nextId = 0;
      this->numberOfObjects = 0;
   }
   /*---------------------------------------------------------------------------------------------------------------------------------------
    * @brief : Destructor
    ----------------------------------------------------------------------------------------------------------------------------------------*/
   ~ObjectHandler( )                     
   {
      ;;
   }

   void tickAll( const std::vector<Rectangle> collidables );         //Calls the onTick function for all objects in the handler.
   void renderAll( );                                                //Calls the onRender function for all objects in the handler.
   void enemyKilled( Enemy* enemy );                                 //Loops through allObjects and deletes any enemies flagged with isDead = true.
   void cleanupDeadEnemies( );                                       //Deletes enemies flagged as 'isDead' after the frame logic has completed.

   void transferObject( int objId, ObjectHandler& newHandler );      //Transfers a GameObject pointer from this ObjectHandler to another.
   void removeObject(int objId);                                     //Removes the GameObject pointer from this ObjectHandler.
   class GameObject* getObject( int id );                            //Returns the GameObject pointer with the passed id number.
   class GameObject* createObject( );                                //Creates a GameObject object and adds it to allObjects.

   class Player* createPlayer( Vector2 position );                   //Creates a Player object and adds it to allObjects. Defined in player.cpp.
   class Enemy* createEnemy( Vector2 position );                     //Creates an Enemy object and adds it to allObjects. Defined in enemy.cpp.
   class Ladder* createLadder( Vector2 position, bool isLadderUp);   //Creates a Ladder object and adds it to allObjects. Defined in interactable.cpp.
   class Door* createDoor( Vector2 position );                       //Creates a Door object and adds it to allObjects. Defined in interactable.cpp.
   class HpPickup* createHpPickup(Vector2 position);                 //Creates a HpPickup object and adds it to allObjects. Defined in interactable.cpp.
};