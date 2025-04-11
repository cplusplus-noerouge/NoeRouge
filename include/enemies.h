#pragma once

#include "raylib.h"

class Enemy{
private:
    int world_position[2];
    int local_position[2];
    // Inventory is a float array of item ids
    // The decimal value can be used for item durability (if applicable)
    float *inventoryPtr;
    int health;
    int defense;
    char graphic;
    // etc...

public:
    // Constructor
    Enemy( int x, int y, int hp, int def, char gfx )
        : health( hp ), defense( def ), graphic( gfx )
    {
        world_position[ 0 ] = x;
        world_position[ 1 ] = y;
    }

    // Movement functions
    void moveLeft(int distance);
    void moveRight(int distance);
    void moveUp(int distance);
    void moveDown(int distance);

    // Combat and rendering
    void render( );
    void takeDamage( int damage );

    // Collision detection
    bool checkCollision( Vector2 playerPos, float attackRange ) const;

    // Getter for position
    Vector2 getPosition( ) const
    {
        return { static_cast< float >( world_position[ 0 ] ), static_cast< float >( world_position[ 1 ] ) };
    }

    // Getters for health
    int getHealth( ) const { return health; }
};

