#pragma once
#include "object.h"

class GameObject;

class Floor;

class ObjectHandler
{
   private:
   static int nextId; //this is shared between all object handlers (each floor has an object handler)
   
   public:
   Floor* floor;

   int numberOfObjects;

   std::map<int, GameObject* > allObjects;

   static int takeNextId( )
   {
      return nextId++;
   }

   ObjectHandler( )
   {
      this->numberOfObjects = 0;
   }
   ObjectHandler(Floor* floor)
   {
      this->floor = floor;
      this->numberOfObjects = 0;
   }
   ~ObjectHandler( )
   {
      ;;
   }

   void tickAll( const std::vector<Rectangle> collidables );
   void renderAll( );
   Floor* getFloor( );
   void setFloor( Floor* floor );
   void playerCreate( );

   void transferObject( int objId, ObjectHandler& newHandler );
   class GameObject* getObject( int id );
   class GameObject* createObject( );

   class Player* createPlayer( Vector2 position, Vector2 size, int speed );
   class Enemy* createEnemy( Vector2 position, Vector2 size, int speed );
   class Ladder* createLadder( Vector2 position, int floorChange );
   class Door* ObjectHandler::createDoor( Vector2 position );
};