/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class

* Ben A, Kaleb, Reese, Ethan, Thomas, Adam
* Player Class (inherits from Character class)
* Inherits sprite functionality from Sprite class.
* Inherits character functionality from Character class.
* Player class represents the player character in the game.
* It handles player movement, rendering, and attacking functionality.
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
   float attackRange;                            //Attack radius
   int attackDamage;                             //Damage per hit
   int health;                                   //Player health
   int dodgeCooldown;                            //Cooldown length of dodge ability
   float walkTimer;                              //Time between steps
   SheetSprite sprite;                           //Set of 9 sprites for the player
   Animation animation = Animation( 4, 0.15 );   //Players movement animation

public:

    /*-----------------------------------------------------------------------------------------------------------------------------------
     * @brief : Parameterized Class constructor.
    ------------------------------------------------------------------------------------------------------------------------------------*/

    Player(int id, Vector2 _position, Vector2 _size, int _speed) 
       : Character(id, _position, _size, _speed), attackRange(50.0f), attackDamage( 1 ), health( 5 ), dodgeCooldown( 0 )
    { 
       Animation animation = Animation( 4, 0.1 );
       sprite = SheetSprite( "playerWalk1", { 16, 0, 16, 16 }, position, position.y );
       walkTimer = 0.0f;
    }
    
    void updateDirection( ) override;                               //Sets the movement direction of the character based on control input.
    void onTick(const std::vector<Rectangle> colliders) override;   //Updates the state of the player during a single frame.
    void onRender( ) override;                                      //Renders the player on screen.
    void attack( std::vector<Enemy*>& enemies );                    //Attacks enemy objects if within range and key is pressed.
    void defend( std::vector<Enemy*>& enemies );                    //Allows the player to defend against enemy attacks.
    void takeDamage( int damage, bool& playerDefeated );            //Decrements player health based off enemy damage and checks for player death.
    void dodge();                                                   //Increases players speed by 1.4 times for 1 second when input and cools down for another 2 seconds
};

