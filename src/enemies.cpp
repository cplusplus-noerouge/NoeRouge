/*
* NoeRogue
* Enemy Class (inherits gameObject class)
* Kaleb Flowers
*
* TO-DO :
* 
*/
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "enemies.h"
#include "object.h"


void Enemy::updateDirection( )
{
   // line of sight to the player(Most important)


   // Attacking the player with a rectangle or circle after line of sight


   // (To do) random movements before the player is sighted
  
   
}

void Enemy::onRender( )
{
   Rectangle rectangle = bounds( );
   DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, RED );
}

// Define the player crate function in the object handler
class Enemy* ObjectHandler::createEnemy( Vector2 position, Vector2 size, int speed )
{
   class Enemy* enemy = new class Enemy( this->nextId++, position, size, speed );
   this->allObjects.push_back( enemy );
   this->numberOfObjects++;
   return enemy;
}
