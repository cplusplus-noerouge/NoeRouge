#pragma once

#include <cstdlib>
#include "character.h"



class Enemy: public Character
{
public:
    Enemy(int id, Vector2 position, Vector2 size, int speed ) : Character( id, position, size, speed) { }

    void updateDirection( );

    void render( );
    void takeDamage( int damage );
    bool checkCollision( Vector2 playerPos, float attackRange ) const;
};