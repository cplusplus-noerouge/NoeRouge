#pragma once
#include <cstdio>
#include "raylib.h"
#include "object.h"
#include "character.h"
#include "sprite.h"

class Player : public Character 
{

private:
   Rectangle bounds_;
   Color color_;
   float attackTimer_;
   bool isAttacking_;
   bool isBlocking_;
   float blockTimer_;
   float attackRange;    // Attack radius
   int attackDamage;      // Damage per hit
   Sprite sprite;

public:
    Player(int id): Character(id), attackRange( 50.0f ), attackDamage( 20 ) 
    { 
       sprite = Sprite( "player", position, position.y );
    }
    Player(int id, Vector2 _position, Vector2 _size, int _speed) 
       : Character(id, _position, _size, _speed), attackRange(50.0f), attackDamage(20) 
    { 
       sprite = Sprite( "player", position, position.y );
    }
    
    void onRender( ) override;
    //void attack( std::vector<Enemy*>& enemies );
    void updateDirection() override;
    

  /* Player* createPlayer( objectHandler& handler, Vector2 position, Vector2 size, int speed );
   void attack(std::vector<Enemy*>& enemies);*/
};
// <<<<<<< combat-character-copy
//// Define the Player crate function in the object handler
//class Player *objectHandler::createPlayer(Vector2 position, Vector2 size, int speed) {
//    class Player *Player = new class Player(this->nextId++, position, size, speed);
//    this->allObjects.push_back(Player);
//    this->numberOfObjects++;
//    return Player;
//}
// =======
