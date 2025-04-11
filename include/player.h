#pragma once
#include <cstdio>
#include "raylib.h"
#include "object.h"
#include "character.h"
#include "enemies.h"

class player : public Character {
private:
   Rectangle bounds_;
   Color color_;
   float attackTimer_;
   bool isAttacking_;
   bool isBlocking_;
   float blockTimer_;
   float attackRange;    // Attack radius
   int attackDamage;      // Damage per hit

public:
    player(int id): Character(id), attackRange( 50.0f ), attackDamage( 20 ) 
    { }
    player(int id, Vector2 _position, Vector2 _size, int _speed) 
       : Character(id, _position, _size, _speed), attackRange(50.0f), attackDamage(20) 
    { }
    
    void onRender( ) override;
    void attack( std::vector<Enemy*>& enemies );
    void updateDirection() override;
    

  /* player* createPlayer( objectHandler& handler, Vector2 position, Vector2 size, int speed );
   void attack(std::vector<Enemy*>& enemies);*/
};

//// Define the player crate function in the object handler
//class player *objectHandler::createPlayer(Vector2 position, Vector2 size, int speed) {
//    class player *player = new class player(this->nextId++, position, size, speed);
//    this->allObjects.push_back(player);
//    this->numberOfObjects++;
//    return player;
//}
