/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Kaleb Flowers, Reese Edens, Ethan Sheffield
* The enemy class is a child class of Character that represents the enemy characters that populate the map.
*
* * TO-DO :
* - implement enemyKilled in objectHandler
----------------------------------------------------------------------------------------------------------------------------------------*/
#include "enemy.h"
#include "character.h"
#include "maphandler.h"

using namespace std;

extern MapHandler* mapHandler;
extern CustomCamera mainCamera;   //Camera view of the map

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Parameterized Class constructor, initializes the enemy's ID, stats, and position in the world.
----------------------------------------------------------------------------------------------------------------------------------------*/
Enemy::Enemy( int id, Vector2 position, Stats stats )
	: Character( id, position ),   //Call Character constructor
	stats( stats )
{
	this->setId( id );
	_position = position;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onTick( )
* @brief : Updates the state of the character during a single frame.
* @param vector<Rectangle> collidables : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::onTick( const std::vector<Rectangle> collidables )
{
	GameObject* obj = mapHandler->getCurrentFloor( )->getObjHandler( )->allObjects[ 0 ];
	Player* player = dynamic_cast< Player* >( obj );

	_target = player->getPosition( );
	//moveToTarget( _target, 60.0, collidables );

	//updateDirection( _target );

	attackPlayer( player );

	//Calculate velocity based on direction and frame time
	velocity = Vector2Scale( Vector2Normalize( direction ), stats.speed * GetFrameTime( ) );

	//Update position by adding velocity
	_position = Vector2Add( _position, velocity );

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

/*---------------------------------------------------------------------------------------------------------------------------------------
* onRender( )
* @brief : Renders the enemy on screen.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::onRender( )
{
	//Animating the enemy
	animation.onTick( );
	//Freezing the animation at frame 1 if the player isn't moving
	//WARNING! This logic will need to be revised when implementing other animations that aren't just for walking.
	if ( Vector2Equals( direction, { 0 , 0 } ) )
	{
		animation.reset( );
	}
	sprite.setTexture( "alienAWalk" + std::to_string( animation.getFrame( ) ) );

	//Setting the position referenced on the sheet based on the direction the plaer is facing
	sprite.setSourceRect( { 16 + ( direction.x * 16 ), 16 + ( direction.y * 16 ), 16, 16 } );


	sprite.update( _position, _position.y );
	mainCamera.addToBuffer( &sprite );

	//Draw the enemy's health above the rectangle
	DrawText( TextFormat( "HP: %d", stats.health ), _position.x, _position.y, 35, BLACK );
}


/*---------------------------------------------------------------------------------------------------------------------------------------
* takeDamage( )
* Reese. Edens
* @brief : Reduces health when damage is taken, accounting for defense.
* @param int damage : amount of incoming damage to decrement from health
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Enemy::takeDamage( int damage )
{
	//Reduce health by damage amount, and ensures it doesn't go below zero
	stats.health -= damage;

	// Clamp health to minimum 0
	stats.health = ( int ) Clamp( stats.health, 0, 3 ); // Clamp between 0 and max HP (e.g. 3)

	if ( stats.health > 0 )
	{
		// Still alive, show hit and current HP
		Vector2 screenPos = getNearestPosition();
		DrawText( "HIT!", static_cast< int >( screenPos.x - 20 ), static_cast< int >( screenPos.y - 20 ), 30, RAYWHITE );
		DrawText( TextFormat( "HP: %d", stats.health ), static_cast< int >( _position.x ), static_cast< int >( _position.y - 30 ), 25, BLACK );
		PlaySound( sfx[ "hitHurt (3).wav" ] );
		std::cout << "Enemy health is now: " << stats.health << std::endl;
	}
	else
	{
		PlaySound( sfx[ "hitHurt (3).wav" ] );
		//mapHandler->getCurrentFloor( )->getObjHandler( )->enemyKilled( this ); //not implemented
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
	float dx = playerPos.x - _position.x;
	float dy = playerPos.y - _position.y;
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
Enemy* ObjectHandler::createEnemy( Vector2 position )
{
	Stats enemyStats = { 3, 1, 16, 50 };                              //stats: hp, damage, range, speed
	Enemy* newEnemy = new Enemy( ++nextId, position, enemyStats );
	allObjects[ newEnemy->getId( ) ] = newEnemy;                     //Add <id, object*> to the map
	this->numberOfObjects++;
	return newEnemy;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* attackPlayer( )
* Kaleb Flowers
* @brief :  
* @param Vector2 position :  
*
----------------------------------------------------------------------------------------------------------------------------------------*/

void Enemy::attackPlayer( Player* player )
{
	// make sure both are alive
	if (stats.health <= 0 ) return;

	// distance check
	if ( checkCollision( player->getPosition( ), stats.attackRange ) )
	{
		player->takeDamage( stats.attackDamage );
	}

	//cooldown
	timeSinceLastAttack += GetFrameTime( );
	if ( timeSinceLastAttack < attackInterval ) return;
	timeSinceLastAttack = 0.f;
}