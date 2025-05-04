/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Adam
* The player class is a child class of Character that represents the playable character.
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

   Player( int id );                                                 //Class constructor based on object ID. 
   Player( int id, Vector2 _position, Vector2 _size, int _speed );   //Parameterized Class constructor.

   void onRender( ) override;                                        //Renders the character on screen.
   void attack( std::vector<Enemy*>& enemies );                      //Attacks enemy objects if within range and key is pressed.
};
