/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Kaleb Flowers, Reese Edens, Ethan Sheffield
* The enemy class is a child class of Character that represents the enemy characters that populate the map.
*
* * TO-DO :
* - Add attack functionality?
* - Add AI behavior?
* - Include more interaction with player?
----------------------------------------------------------------------------------------------------------------------------------------*/

#include <raylib.h>
#include <iostream>
#include <cmath>
#include <raymath.h>
#include <vector>
#include "object.h"
#include "character.h"
#include "enemy.h"
#include "audio.h"

using namespace std;

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Parameterized Class constructor, initializes the enemy's ID, stats, and position in the world.
----------------------------------------------------------------------------------------------------------------------------------------*/
Enemy::Enemy( int id, int x, int y, Stats stats )
	: Character( id, { static_cast< float >( x ), static_cast< float >( y ) }, { 50.0f, 50.0f }, stats.speed ), // Call Character constructor
	stats( stats )
{
	position.x = x;
	position.y = y;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onTick( )
* @brief : Updates the state of the character during a single frame.
* @param vector<Rectangle> collidables : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::onTick( const std::vector<Rectangle> collidables )
{
	//Update movement direction (likely handled by inherited Character method)
	updateDirection( position );

	//Calculate velocity based on direction and frame time
	velocity = Vector2Scale( direction, speed * GetFrameTime( ) );

	//Update position by adding velocity
	position = Vector2Add( position, velocity );

	//Check and resolve collisions with game world objects
	updateCollisions( collidables );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateDirection( )
* @brief : Sets the movement direction of the character based on target position.
* @param vector<Rectangle> target : The target's map position
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::updateDirection( Vector2 target )
{
	if ( target.x > position.x )
	{
		direction.x = -1;
	}
	else if ( target.x < position.x )
	{
		direction.x = 1;
	}
	if ( target.y < position.y )
	{
		direction.y = 1;
	}
	else if ( target.y < position.y )
	{
		direction.y = -1;
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onRender( )
* @brief : Renders the enemy on screen.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::onRender( )
{
	//Draw the enemy as a red rectangle
	DrawRectangle( Enemy::position.x, Enemy::position.y, 100, 100, RED );

	//Draw the enemy's health above the rectangle
	DrawText( TextFormat( "HP: %d", stats.health ), Enemy::position.x, Enemy::position.y, 35, BLACK );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* takeDamage( )
* @brief : Reduces health when damage is taken, accounting for defense.
* @param int damage : amount of incoming damage to decrement from health
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::takeDamage( int damage )
{
	//Reduce health by damage amount, and ensures it doesn't go below zero
	stats.health -= damage;
	stats.health = ( int ) Clamp( stats.health, 0, stats.health );

	if ( stats.health > 0 )
	{
		cout << "Enemy took " << damage << " damage!" << endl;
		cout << "Enemy health is now: " << stats.health << endl;
	}
	else if ( stats.health <= 0 )
	{
		PlaySound( sfx[ "hitHurt (3).wav" ] );
		//Reset health to initial value (could be defined in Stats struct), Assuming initial health is 3
		stats.health = 3;

		//Reset position to some default value
		Enemy::position.x = 100;
		Enemy::position.y = 100;
		std::cout << "Enemy is dead!" << std::endl;
		std::cout << "Enemy respawned!" << std::endl;
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* checkCollision( )
* @brief : Checks if the player's position is within attack range of the enemy.
* @param Vector2 playerPos : the player's position
* @param float attachRange : the enemy's attack range
* @return bool : Returns true if the player is within the enemy's attack range, false if otherwise
----------------------------------------------------------------------------------------------------------------------------------------*/
bool Enemy::checkCollision( Vector2 playerPos, float attackRange ) const
{
	float dx = playerPos.x - position.y;
	float dy = playerPos.y - position.x;
	float distance = sqrt( dx * dx + dy * dy );

	//Returns true if the distance is less than the attack range
	return distance < attackRange;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* createEnemy( )
* Kaleb Flowers
* @brief : Enemy Object creation function defined in ObjectHandler.
* @param Vector2 position : Initial position of the enemy.
* @param Vector2 size : Initial size of the enemy.
* @param int speed : Initial speed of the enemy.
* @return Enemy* : Pointer to the created Enemy object.
----------------------------------------------------------------------------------------------------------------------------------------*/
Enemy* ObjectHandler::createEnemy( Vector2 position, Vector2 size, int speed )
{
	Stats enemyStats = { 3, 1, 25, 5 }; // stats: hp, damage, range, speed
	Enemy* newEnemy = new Enemy( nextId++, position.x, position.y, enemyStats );
	allObjects[ newEnemy->getId( ) ] = newEnemy; // Add <id, object*> to the map
	this->numberOfObjects++;
	return newEnemy;

}