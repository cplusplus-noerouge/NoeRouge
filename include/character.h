#include "object.h"
#include "raylib.h"

#pragma once

class Character : public GameObject
{
   private:

   Vector2 size;
   

   protected:

   Vector2 position;
   Vector2 direction;
   Vector2 velocity;
   
   // Position of target. For enemies this will usually be the player, the player's last known location, or their spawn point.
   Vector2 target; 
   
   public:
   int speed; // Speed of the character in pixels per second
   

   Character( int _id, Vector2 _position, Vector2 _size, Vector2 target, int _speed );

   Character( int _id, Vector2 _position, Vector2 _size, int _speed );

   Character( int _id );

   ~Character( )
   {
      //destructor
   }

   void onTick( const std::vector<Rectangle> collidables ) override;

   void onRender( ) override;

   virtual void updateDirection( );

   void updateDirection( Vector2 target );

   Rectangle bounds( );

   //Checks if this character is colliding with the left side of another rectangle, same for all colliding functions.
   bool collidingLeft( Rectangle other );

   bool collidingRight( Rectangle other );

   bool collidingTop( Rectangle other );

   bool collidingBottom( Rectangle other );

   void updateCollisions( const std::vector<Rectangle> colliders );

   Vector2 getPosition( );
   void setPosition(Vector2 newPos);

   void moveToTarget( Vector2 target, float distanceMaintained, std::vector<Rectangle> colliders );

   Ray relationToTarget( );

   bool updateLOS( const std::vector<Rectangle> colliders );

   float getTargetDistance( );

};