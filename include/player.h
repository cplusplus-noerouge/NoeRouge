/*
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan
* Reese Edens, Kaleb Flowers
* Player Class (inherits from Character class)
* Inherits sprite functionality from Sprite class.
* Inherits character functionality from Character class.
* Player class represents the player character in the game.
* It handles player movement, rendering, and attacking functionality.
* Player.h 
   
*/

#pragma once
#include "raylib.h"
#include "character.h"
#include "sheetSprite.h"
#include "animation.h"
#include "enemy.h"

const float WALK_TIMER_MAX = 0.5f;

class Player : public Character 
{

private:
   float attackRange;    // Attack radius
   int attackDamage;      // Damage per hit
   int health;           // Player health
   float walkTimer;      // Time between steps
   SheetSprite sprite;
   Animation animation = Animation( 4, 0.15 );

public:

   Player( Vector2 spawn, ObjectHandler* handler )
      : Character( 0, spawn, handler ), attackRange( 50.0f ), attackDamage( 1 ), health( 5 )
   {
      Animation animation = Animation( 4, 0.1 );
      sprite = SheetSprite( "playerWalk1", { 16, 0, 16, 16 }, position, position.y );
      walkTimer = 0.0f;
   }
    //Player(int id): Character(id), attackRange( 50.0f ), attackDamage( 1 ), health( 5 )
    Player(int id, Vector2 _position, Vector2 _size, int _speed) 
       : Character(id, _position, _size, _speed), attackRange(50.0f), attackDamage( 1 ), health( 5 )
    { 
       Animation animation = Animation( 4, 0.1 );
       sprite = SheetSprite( "playerWalk1", { 16, 0, 16, 16 }, position, position.y );
       walkTimer = 0.0f;
    }
    
    void updateDirection( ) override;
    void onTick(const std::vector<Rectangle> colliders) override;
    void onRender( ) override;
    void attack( std::vector<Enemy*>& enemies );
    void takeDamage( int damage, bool& playerDefeated );  //Decrements player health based off enemy damage and checks for player death.
                   
    //void updateDirection() override;
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
