/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "staticSprite.h"

/*---------------------------------------------------
* @brief: overrides checking if the sprite is within the camera
* @param: Rectangle rect = the bounding rectangle of the camera
*/
bool StaticSprite::isWithinRect( Rectangle rect )
{
	return true;
}

/*---------------------------------------------------
* @brief: renders the texture to the camera
*/
void StaticSprite::render( Vector2 cameraPosition )
{
	Vector2 origin = { pivotPoint.x + destinationRect.width / 2, pivotPoint.y + destinationRect.height / 2 };
	DrawTexturePro( texture, sourceRect, destinationRect, origin, rotation, tint );
}