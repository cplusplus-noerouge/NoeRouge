/* noeRouge - enemy.cpp
*  Worked on by: Kaleb Flowers, Reese Edens, Ethan Sheffield */

#include "enemy.h"			//The .h file for this class
#include "character.h"		//Class that this class inherits from
#include "maphandler.h"		//Class that generates the dungeon map and handles the map methods

using namespace std;

extern MapHandler* mapHandler;    //The game's mapHandler object
extern CustomCamera mainCamera;   //Camera view of the map

/*-------------------------------------------------------------------------------------------------
* The enemy class is a child class of Character that represents the enemy
* characters that populate the map.
*-------------------------------------------------------------------------------------------------*/


	/*---------------------------------------------------------------------------------------------
	* Enemy( int id, Vector2 position, Stats stats )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Parameterized Class constructor, initializes the enemy's ID, 
	*		   stats, and position in the world.
	* @param:  id - id number of character
	* @param:  position - coordinates where the character will start in the map
	* @param:  stats - the character specific data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Enemy::Enemy( int id, Vector2 position, Stats stats )
	: Character( id, position ),   //Call Character constructor
	stats( stats )
{
	this->setId( id );
	_position = position;
	attackInterval = 0.5f;
}

	/*---------------------------------------------------------------------------------------------
	* onTick( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ethan, Reese, Kaleb
	* @brief:  Updates the state of the character during a single frame.
	* @param:  collidables - The collection of collidables to check for character collision.
	* @return: none
	---------------------------------------------------------------------------------------------*/
void Enemy::onTick( const std::vector<Rectangle> collidables )
{
	GameObject* obj = mapHandler->getCurrentFloor( )->getObjHandler( )->allObjects[ 0 ];
	Player* player = dynamic_cast< Player* >( obj );

	_target = player->getPosition( );
	moveToTarget( _target, 60.0, collidables );

	attackPlayer( player );

	if ( hitDisplayTimer > 0 )
	{
		hitDisplayTimer -= GetFrameTime( );
		if ( hitDisplayTimer <= 0 )
		{
			wasHit = false;
		}
	}

	   //Calculate velocity based on direction and frame time
	velocity = Vector2Scale( Vector2Normalize( direction ), stats.speed * GetFrameTime( ) );

	   //Update position by adding velocity
	_position = Vector2Add( _position, velocity );

	   //Check and resolve collisions with game world objects
	updateCollisions( collidables );
}

	/*---------------------------------------------------------------------------------------------
	* updateDirection( Vector2 target )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Sets the movement direction of the character based on target position.
	* @param:  target - The target's map position
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Enemy::updateDirection( Vector2 target )
{
	if ( target.x > _position.x )
	{
		direction.x = 1;
	}
	else if ( target.x < _position.x )
	{
		direction.x = -1;
	}
	if ( target.y > _position.y )
	{
		direction.y = 1;
	}
	else if ( target.y < _position.y )
	{
		direction.y = -1;
	}
}

	/*---------------------------------------------------------------------------------------------
	* onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Group Effort
	* @brief:  Renders the enemy on screen.
	* @param : none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Enemy::onRender( )
{
	animation.onTick( );
	if ( Vector2Equals( direction, { 0 , 0 } ) ) animation.reset( );
	sprite.setTexture( "alienAWalk" + std::to_string( animation.getFrame( ) ) );
	sprite.setSourceRect( { 16 + ( direction.x * 16 ), 16 + ( direction.y * 16 ), 16, 16 } );
	sprite.update( _position, _position.y );
	mainCamera.addToBuffer( &sprite );

	   //Calculate the width of the health bar relative to the enemy's max health
	float hpBarWidth = 50.0f;					// Set the width of the health bar
	float hpBarCurrentWidth = hpBarWidth *		
		( float ) stats.health / stats.health;  //Scale width based on current health 

	Vector2 screenPos = Vector2Subtract( _position, mainCamera.getPosition( ) );

	   //Draw the background of the HP bar (gray)
	DrawRectangle( hpBarPosition.x, hpBarPosition.y, hpBarWidth, 5, GRAY );

	   //Draw the HP bar (green, red if health is low)
	Color barColor = ( stats.health > stats.health * 0.2f ) ? GREEN : RED;
	DrawRectangle( hpBarPosition.x, hpBarPosition.y, hpBarCurrentWidth, 5, barColor );
	   //Always draw HP
	DrawText( TextFormat( "HP: %d", stats.health ), screenPos.x - 10, screenPos.y - 30, 15, RED );

	   //If recently hit, draw "HIT!"
	if ( wasHit )
	{
		DrawText( "HIT!", screenPos.x - 20, screenPos.y - 50, 30, RAYWHITE );
	}
}

	/*---------------------------------------------------------------------------------------------
	* takeDamage( int damage )
	* ---------------------------------------------------------------------------------------------
	* @names:  Reese Edens, Kaleb Flowers
	* @brief:  Reduces health when damage is taken, accounting for defense.
	* @param:  damage - amount of incoming damage to decrement from health
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Enemy::takeDamage( int damage )
{
	   //Reduce health by damage amount, and ensures it doesn't go below zero
	stats.health -= damage;

	   //Clamp health to minimum 0
	stats.health = ( int ) Clamp( stats.health, 0, 3 );   //Clamp between 0 and max HP (e.g. 3)

	if ( stats.health > 0 )
	{
		wasHit = true;
		hitDisplayTimer = 0.5f;   //Show hit for 0.5 seconds
		PlaySound( sfx[ "hitHurt (3).wav" ] );
		std::cout << "Enemy health is now: " << stats.health << std::endl;
	}
	else
	{
		PlaySound( sfx[ "dead.wav" ] );
		isDead = true;
	}
}

	/*---------------------------------------------------------------------------------------------
	* checkCollision( Vector2 playerPos, float attackRange ) const
	* ---------------------------------------------------------------------------------------------
	* @brief:  Checks if the player's position is within attack range of the enemy.
	* @param:  playerPos - the player's position
	* @param:  attachRange - the enemy's attack range
	* @return: bool - true if the player is within the enemy's attack range, false if otherwise
	*--------------------------------------------------------------------------------------------*/
bool Enemy::checkCollision( Vector2 playerPos, float attackRange ) const
{
	float dx = playerPos.x - _position.x;
	float dy = playerPos.y - _position.y;
	float distance = sqrt( dx * dx + dy * dy );

	   //Returns true if the distance is less than the attack range
	return distance < attackRange;
}

	/*---------------------------------------------------------------------------------------------
	* createEnemy( Vector2 position )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Enemy Object creation function defined in ObjectHandler.
	* @param:  position : Initial position of the enemy.
	* @return: Enemy* - Pointer to the created Enemy object.
	*--------------------------------------------------------------------------------------------*/
Enemy* ObjectHandler::createEnemy( Vector2 position )
{
	Stats enemyStats = { 3, 1, 16, 50 };                          //stats: hp, damage, range, speed
	Enemy* newEnemy = new Enemy( ++nextId, position, enemyStats );
	allObjects[ newEnemy->getId( ) ] = newEnemy;                  //Add <id, object*> to the map
	this->numberOfObjects++;
	return newEnemy;
}

	/*---------------------------------------------------------------------------------------------
	* attackPlayer( Player* player )
	* ---------------------------------------------------------------------------------------------
	* @names:  Kaleb Flowers
	* @brief:  Handles enemy behavior when engaging the player.
	* @param   player - A pointer to the player object being attacked.
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Enemy::attackPlayer( Player* player )
{
		// make sure both are alive
	if ( player->isDead ) return;
	if ( stats.health <= 0 ) return;                     

		 //cooldown
	timeSinceLastAttack += GetFrameTime( );             
	
	if ( timeSinceLastAttack < attackInterval ) return;
	timeSinceLastAttack = 0.f;

	   //Distance check
	if ( checkCollision( player->getPosition( ), stats.attackRange ) )
	{
		std::cout << "Enemy attacking player\n";
		player->takeDamage( stats.attackDamage );
	}
	else
	{
			// move towards player
		updateDirection( player->getPosition( ) );                 
		velocity = Vector2Scale( Vector2Normalize( direction ), stats.speed * GetFrameTime( ) );
		_position = Vector2Add( _position, velocity );

	}
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
* 
*	-General formatting
*/

