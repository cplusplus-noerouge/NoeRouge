#include "player.h"

void player::updateDirection()
{
    if (IsKeyDown(KEY_A))
    {
        direction.x = -1;
    }
    else if (IsKeyDown(KEY_D))
    {
        direction.x = 1;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y = 1;
    }
    else if (IsKeyDown(KEY_W))
    {
        direction.y = -1;
    }
}

void player::onRender()
{
    Rectangle rectangle = bounds();
    DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON);
}

// Define the player create function in the object handler
class player* ObjectHandler::createPlayer( Vector2 position, Vector2 size, int speed )
{
   class player* player = new class player( this->nextId++, position, size, speed );
   this->allObjects.push_back( player );
   this->numberOfObjects++;
   return player;
}
