/*
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan
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
   bool isInvincible = false; // Tracks if the player is invincible-KF
   float invincibilityTimer = 0.0f; // Timer for invincibility frames-KF
   const float invincibilityDuration = 0.7f; // Duration of invincibility in seconds-KF
   float walkTimer;      // Time between steps
   SheetSprite sprite;
   Animation animation = Animation( 4, 0.15 );

public:
      //for I-Frame
     void setInvincible( bool invincible );
     void updateInvincibility( ); // Updates the invincibility timer
     bool getIsInvincible( ) const
      {
         return isInvincible;
      }

    void defend( std::vector<Enemy*>& enemies ); // Defend against enemy attacks

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
