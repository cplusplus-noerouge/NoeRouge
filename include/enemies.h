/*
* NoeRogue
* Enemy Class (inherits gameObject class)
* Kaleb Flowers
*
* TO-DO :
*
*/


#pragma once

#include <cstdlib>
#include "character.h"



class Enemy: public Character
{
public:
    Enemy(int id, Vector2 position, Vector2 size, int speed ) : Character( id, position, size, speed) { }

    void updateDirection( ) override;
    void onRender( ) override;
};