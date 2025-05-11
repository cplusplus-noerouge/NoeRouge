#pragma once
#include "object.h"

class GameObject;

class ObjectHandler
{
   private:
   static int nextId; //this is shared between all object handlers (each floor has an object handler)
   
   public:

   int numberOfObjects;

   std::map<int, GameObject* > allObjects;

   static int takeNextId( )
   {
      return ++nextId;
   }

   ObjectHandler( )
   {
      this->nextId = 0;
      this->numberOfObjects = 0;
   }
   ~ObjectHandler( )
   {
      ;;
   }

   void tickAll( const std::vector<Rectangle> collidables );
   void renderAll( );

   void transferObject( int objId, ObjectHandler& newHandler );     //transfer an object from this handler to another one
   void removeObject(int objId);                                    //remove the object from the handler
   class GameObject* getObject( int id );
   class GameObject* createObject( );

   class Player* createPlayer( Vector2 position );
   class Enemy* createEnemy( Vector2 position );
   class Ladder* createLadder( Vector2 position, bool isLadderUp);
   class Door* createDoor( Vector2 position );
   class HpPickup* createHpPickup(Vector2 position);
};