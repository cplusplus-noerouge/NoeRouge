#pragma once

#include <cstdio>
#include "raylib.h"
#include "object.h"
#include "character.h"
#include "enemy.h"
#include "sprite.h"

// Player class inherits from Character base class
class Player : public Character
{
   private:
   Rectangle bounds_;       // Rectangle defining player's boundary (for collision or rendering)
   Color color_;            // Color of the player (if customized rendering is used)
   float attackTimer_;      // Timer to manage attack cooldown (not yet implemented in .cpp)
   bool isAttacking_;       // Flag to indicate if player is attacking
   bool isBlocking_;        // Flag to indicate if player is blocking
   float blockTimer_;       // Timer to manage block duration/cooldown (not yet implemented)

   float attackRange;       // Attack range in pixels
   int attackDamage;        // Amount of damage dealt per hit

   public:
   // Constructor: initializes player using base class constructor and sets default attack values
   Player( int id, Vector2 _position, Vector2 _size, int _speed )
      : Character( id, _position, _size, _speed ), attackRange( 50.0f ), attackDamage( 20 )
   { }

   // Called to render the player on screen
   void onRender( ) override;

   // Executes attack logic against enemies
   void attack( std::vector<Enemy*>& enemies );

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

// -------------------------
// Old / Commented-out Code
// -------------------------

// This version of createPlayer was likely moved into ObjectHandler.cpp
// or a utility function was preferred for clarity

//<<<<<<< combat-character-copy
//// Define the Player create function in the object handler
//class Player* objectHandler::createPlayer(Vector2 position, Vector2 size, int speed) {
//    class Player* Player = new class Player(this->nextId++, position, size, speed);
//    this->allObjects.push_back(Player);
//    this->numberOfObjects++;
//    return Player;
//}

// Alternative function signature and attack declaration (now handled in class above)
/*
Player* createPlayer(objectHandler& handler, Vector2 position, Vector2 size, int speed);
void attack(std::vector<Enemy*>& enemies);
*/
