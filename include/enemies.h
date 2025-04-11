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
#include "object.h"



class Enemy: public GameObject
{
public:
    Enemy(int id, Vector2 position, Vector2 size, int speed ) : GameObject( id, position, size, speed) { }

    void updateDirection( ) override;
    void onRender( )override;
};