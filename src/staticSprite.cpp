/* noeRouge - staticSprite.cpp
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include "staticSprite.h"	//The .h file for this class
/*-------------------------------------------------------------------------------------------------
*  The StaticSprite class creates sprites that do not move on the screen
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* isWithinRect( Rectangle rect )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  overrides checking if the sprite is within the camera
	* @param:  rect - the bounding rectangle of the camera
	* @return: bool - true
	*--------------------------------------------------------------------------------------------*/
bool StaticSprite::isWithinRect( Rectangle rect )
{
	return true;
}

	/*---------------------------------------------------------------------------------------------
	* render( Vector2 cameraPosition )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  renders the texture to the camera
	* @param:  cameraPosition - the current coordinates of the camera
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void StaticSprite::render( Vector2 cameraPosition )
{
	Vector2 origin = { pivotPoint.x + destinationRect.width / 2, pivotPoint.y 
		               + destinationRect.height / 2 };
	DrawTexturePro( texture, sourceRect, destinationRect, origin, rotation, tint );
}