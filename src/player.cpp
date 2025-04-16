#include "player.h"
#include "customCamera.h"
#include "sprite.h"

extern CustomCamera mainCamera;

void Player::updateDirection()
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

void Player::onRender()
{
   mainCamera.setPosition( position ); // Updating the camera position should be moved to its own class or function later on
   sprite.update( position, position.y );
   mainCamera.addToBuffer( &sprite );
}
