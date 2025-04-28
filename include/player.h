/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Adam
----------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "raylib.h"
#include "character.h"
#include "sprite.h"
#include "enemy.h"

class Player : public Character 
{

private:
   float attackRange;     //Attack radius
   int attackDamage;      //Damage per hit
   Sprite sprite;         //Player sprite

public:

    Player( int id );
    Player( int id, Vector2 _position, Vector2 _size, int _speed );
    
    void onRender( ) override;
    void updateDirection( ) override;
    void attack( std::vector<Enemy*>& enemies );
};
