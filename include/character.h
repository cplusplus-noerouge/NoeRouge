#include "object.h"
#include "raylib.h"

#pragma once

class Character : public GameObject
{
   private:

   Vector2 size;
   int speed;

   protected:

   Vector2 position;
   Vector2 direction;
   Vector2 velocity;

   public:

   Character( int _id, Vector2 _position, Vector2 _size, int _speed );

   Character( int _id );

   ~Character( )
   {
      //destructor
   }

   void onTick( const std::vector<Rectangle> collidables ) override;

   void onRender( ) override;

   virtual void updateDirection( );

   Rectangle bounds( );

   //Checks if this character is colliding with the left side of another rectangle, same for all colliding functions.
   bool collidingLeft( Rectangle other );

   bool collidingRight( Rectangle other );

   bool collidingTop( Rectangle other );

   bool collidingBottom( Rectangle other );

   void updateCollisions( const std::vector<Rectangle> colliders );
};