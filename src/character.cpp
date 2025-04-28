/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Ben A, Kaleb, Reese, Ethan
----------------------------------------------------------------------------------------------------------------------------------------*/

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cmath>
#include "Character.h"

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Parameterized Class constructor.
----------------------------------------------------------------------------------------------------------------------------------------*/
Character::Character(int _id, Vector2 _position, Vector2 _size, int _speed)
{
    this->setId(_id);
    position = _position;
    size = _size;
    speed = _speed;
    velocity = { 0 };
    direction = { 0 };
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* @brief : Class constructor based on object ID. 
----------------------------------------------------------------------------------------------------------------------------------------*/
Character::Character( int _id )
{
   this->setId( _id );
   position = { 0 };
   size = { 1 };
   speed = 0;
   velocity = { 0 };
   direction = { 0 };
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onTick( )
* @brief : Updates the state of the character during a single frame.
* @param vector<Rectangle> collidables : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::onTick( const std::vector<Rectangle> collidables )
{
   direction = { 0, 0 };

   updateDirection( );

   //direction is multiplied by speed, which makes velocity
   //speed is multiplied by the time between frames, which forces speed to be the same regardless of framerate.
   velocity = Vector2Scale( direction, speed * GetFrameTime( ) );

   //collisions must be done before velocity is added to position so that the character does not go past a wall before collisions are checked, but that is
   //only necessary for very high movement speed
   updateCollisions( collidables );

   position = Vector2Add( position, velocity );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* onRender( )
* @brief : Renders the character on screen.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::onRender( )
{
   Rectangle rectangle = bounds( );
   DrawRectangle( rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON );
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateDirection( )
* @brief : Sets the movement direction of the character based on control input.
* @param : none
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::updateDirection( )
{
   if ( IsKeyDown( KEY_A ) )
   {
      direction.x = -1;
   }
   else if ( IsKeyDown( KEY_D ) )
   {
      direction.x = 1;
   }
   if ( IsKeyDown( KEY_S ) )
   {
      direction.y = 1;
   }
   else if ( IsKeyDown( KEY_W ) )
   {
      direction.y = -1;
   }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateDirection( Vector2 target )
* @brief : Sets the movement direction of the character based on a target position.
* @param Vector2 target : Target used to adjust character's position.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::updateDirection( Vector2 target )
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
* bounds( )
* @brief : Creates a Rectangle representing the character's current position and size.
* @param : none
* @return Rectangle : The Rectangle representing the character's current position and size.
----------------------------------------------------------------------------------------------------------------------------------------*/
Rectangle Character::bounds()
{
	return { position.x, position.y, size.x, size.y };
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* Collision Methods
* @brief : Checks for collisions in cardinal directions.
* @param Rectangle other : The Rectangle the character is potentially colliding with.
* @return bool : True if a collision is detected, false if otherwise. 
----------------------------------------------------------------------------------------------------------------------------------------*/
bool Character::collidingLeft(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.x + rect.width + velocity.x > other.x && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x < other.x;
}

bool Character::collidingRight(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.x + velocity.x < other.x + other.width && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x + rect.width > other.x + other.width;
}

bool Character::collidingTop(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.y + rect.height + velocity.y > other.y && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y < other.y;
}

bool Character::collidingBottom(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.y + velocity.y < other.y + other.height && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y + rect.height > other.y + other.height;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* updateCollisions( )
* @brief : Detects and resolves collisions between the character and a list of colliders.
* @param vector<Rectangle> colliders : The collection of collidables to check for character collision.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::updateCollisions(const std::vector<Rectangle> colliders)
{
    Rectangle rect = bounds();

    for (Rectangle otherRect : colliders)
    {
        if (collidingLeft(otherRect) && velocity.x > 0)
        {
            velocity.x = 0;
            position.x = otherRect.x - rect.width;
        }
        else if (collidingRight(otherRect) && velocity.x < 0)
        {
            velocity.x = 0;
            position.x = otherRect.x + otherRect.width;
        }
        if (collidingTop(otherRect) && velocity.y > 0)
        {
            velocity.y = 0;
            position.y = otherRect.y - rect.height;
        }
        else if (collidingBottom(otherRect) && velocity.y < 0)
        {
            velocity.y = 0;
            position.y = otherRect.y + otherRect.height;
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* getPosition( )
* @brief : Getter for the character's position.
* @param : none
* @return Vector2 : The current position of the character.
----------------------------------------------------------------------------------------------------------------------------------------*/
Vector2 Character::getPosition( )
{
   return position;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* setPosition( )
* @brief : Setter for the character's position.
* @param Vector2 newPos : The new position to be assigned to the character.
* @return : none
----------------------------------------------------------------------------------------------------------------------------------------*/
void Character::setPosition(Vector2 newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
* getTargetDistance( )
* @brief : Calculates the distance between the character and a target.
* @param : none
* @return float : The distance between the character and a target.
----------------------------------------------------------------------------------------------------------------------------------------*/
float Character::getTargetDistance( )
{
   float dx = position.x - target.x;
   float dy = position.y - target.y;
   return sqrt( dx * dx + dy * dy );
}