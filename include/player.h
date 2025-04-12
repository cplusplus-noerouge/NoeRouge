#include <cstdio>
#include "raylib.h"

#include "object.h"
#include "character.h"
#include "sprite.h"


class Player : public Character {
   private:
   Sprite sprite;


   public:
   Player( )
   {
      sprite = Sprite( "player", position, position.y );
   }
   Player( int id ) : Character( id )
   {
      sprite = Sprite( "player", position, position.y );
   }
   Player( int id, Vector2 _position, Vector2 _size, int _speed ) : Character( id, _position, _size, _speed )
   {
      sprite = Sprite( "player", position, position.y );
   }

   void onTick( ) override
   {
      Character::onTick( );
      sprite.update( position, position.y );
   }

   void onRender( ) override;

   void updateDirection( ) override;
};

// Define the player crate function in the object handler
class Player*objectHandler::createPlayer(Vector2 position, Vector2 size, int speed) {
    class Player *player = new class Player(this->nextId++, position, size, speed);
    this->allObjects.push_back(player);
    this->numberOfObjects++;
    return player;
}

