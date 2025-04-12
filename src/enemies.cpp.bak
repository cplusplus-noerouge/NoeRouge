#include "enemies.h"
// <<<<<<< combat-character-copy
#include "raylib.h"
#include <iostream>
#include <cmath>
// =======
#include "object.h"
// >>>>>>> main-copy


void Enemy::moveLeft( int distance )
{
   world_position[ 0 ] -= distance;
}

void Enemy::moveRight( int distance )
{
   world_position[ 0 ] += distance;
}

void Enemy::moveUp( int distance )
{
   world_position[ 1 ] -= distance;
}

void Enemy::moveDown( int distance )
{
   world_position[ 1 ] += distance;
}

void Enemy::render( )
{
   DrawRectangle( world_position[ 0 ], world_position[ 1 ], 50, 50, RED );
   DrawText( TextFormat( "HP: %d", health ), world_position[ 0 ], world_position[ 1 ] - 20, 12, WHITE );
}

void Enemy::takeDamage( int damage )
{
// <<<<<<< combat-character-copy
   int effectiveDamage = damage - defense;
   if ( effectiveDamage > 0 )
   {
      health -= effectiveDamage;
   }
   if ( health <= 0 )
   {
      std::cout << "Enemy defeated!" << std::endl;
   }
// =======
   Rectangle rectangle = bounds( );
   DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, RED );
// >>>>>>> main-copy
}

bool Enemy::checkCollision( Vector2 playerPos, float attackRange ) const
{
   float dx = playerPos.x - world_position[ 0 ];
   float dy = playerPos.y - world_position[ 1 ];
   float distance = sqrt( dx * dx + dy * dy );

   return distance < attackRange;
}

//Vector2 Enemy::getPosition( ) const
//{
//   return { static_cast< float >( world_position[ 0 ] ), static_cast< float >( world_position[ 1 ] ) };
//}