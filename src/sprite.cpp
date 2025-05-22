/* noeRouge - sprite.cpp
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include "sprite.h"		//The .h file for this class

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-------------------------------------------------------------------------------------------------
*  The Sprite class is a base class for all visual objects in the game and has methods
*  for managing those visual objects
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* update( Texture2D texture, Vector2 position, float layer, float rotation, 
	*	      float scale, Color tint, Vector2 pivotPoint )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates all data members with new values
	* @param:  texture - the texture to be used for the sprite
	* @param:  position - the sprites position on the screen
	* @param:  layer - the rendering layer of the sprite
	* @param:  rotation - rotation of sprite in degrees
	* @param:  scale - how much the sprite is to be scaled
	* @param:  tint - the color of the sprite
	* @param:  pivotPoint - where the sprite is rotated around
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Sprite::update( Texture2D texture, Vector2 position, float layer, float rotation, 
					 float scale, Color tint, Vector2 pivotPoint )
{
	this->texture = texture;
	this->position = position;
	this->layer = layer;
	this->rotation = rotation;
	this->scale = scale;
	this->tint = tint;
	this->pivotPoint = pivotPoint;
	updateRectangles( );
}
	/*---------------------------------------------------------------------------------------------
	* update( std::string texture, Vector2 position, float layer, float rotation, 
	*		  float scale, Color tint, Vector2 pivotPoint )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates all data members with new values
	* @param:  texture - the texture to be used for the sprite
	* @param:  position - the sprites position on the screen
	* @param:  layer - the rendering layer of the sprite
	* @param:  rotation - rotation of sprite in degrees
	* @param:  scale - how much the sprite is to be scaled
	* @param:  tint - the color of the sprite
	* @param:  pivotPoint - where the sprite is rotated around
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Sprite::update( std::string texture, Vector2 position, float layer, float rotation, 
					 float scale, Color tint, Vector2 pivotPoint )
{
	this->texture = textureMap[ texture ];
	this->position = position;
	this->layer = layer;
	this->rotation = rotation;
	this->scale = scale;
	this->tint = tint;
	this->pivotPoint = pivotPoint;
	updateRectangles( );
}

	/*---------------------------------------------------------------------------------------------
	* update( Vector2 position, float layer )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates select data members with new values
	* @param:  position - the sprites position on the screen
	* @param:  layer - the rendering layer of the sprite
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Sprite::update( Vector2 position, float layer )
{
	this->position = position;
	this->layer = layer;
	updateRectangles( );
}

	/*---------------------------------------------------------------------------------------------
	* updateRectangles( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates sourceRect, destinationRect, and boundingRect to reflect new values
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Sprite::updateRectangles( )
{
	Vector2 pivotOffset = Vector2Rotate( pivotPoint, ( PI * rotation / 180 ) );
	destinationRect = { position.x + pivotPoint.x, position.y + pivotPoint.y, 
		                ( float ) texture.width * scale, ( float ) texture.height * scale };
	sourceRect = { 0, 0, ( float ) texture.width, ( float ) texture.height };

	if ( rotation == 0 )
	{
		boundingRect = { destinationRect.x - destinationRect.width / 2, 
			             destinationRect.y - destinationRect.height / 2,
			destinationRect.width, destinationRect.height };
	}
	else
	{
			// safeSize = (longside/2)^2 + 1 | Represents the max width and height that could 
			//result from rotating the texture
		float safeSize = sqrt( 2 * pow( ( std::max( destinationRect.width,
													destinationRect.height ) / 2 ), 2 ) ) + 1;
		boundingRect = { position.x - safeSize, pivotOffset.y - safeSize, safeSize * 2, 
			             safeSize * 2 };
	}
}

	/*---------------------------------------------------------------------------------------------
	* isWithinRect( Rectangle rect )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  checks if the sprite is within the camera
	* @param:  rect - the bounding rectangle of the camera
	* @return: bool - true is there is a collision, else false
	*--------------------------------------------------------------------------------------------*/
bool Sprite::isWithinRect( Rectangle rect )
{
	return CheckCollisionRecs( rect, this->boundingRect );
}

	/*---------------------------------------------------------------------------------------------
	* render( Vector2 cameraPosition )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  renders the texture to the camera
	* @param:  cameraPosition - the dimensions of the current camera 
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Sprite::render( Vector2 cameraPosition )
{
	Rectangle realDestination = { destinationRect.x - cameraPosition.x, destinationRect.y 
		                          - cameraPosition.y,	destinationRect.width, 
		                          destinationRect.height };

	Vector2 origin = { pivotPoint.x + destinationRect.width / 2, pivotPoint.y 
		               + destinationRect.height / 2 };
	DrawTexturePro( texture, sourceRect, realDestination, origin, rotation, tint );
}

	/*---------------------------------------------------------------------------------------------
	* print( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  prints all sprite information to the console
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/ 
void Sprite::print( )
{
	std::cout << "Sprite " << this << ":\n\tposition = {" << position.x << ", " << position.y 
		<< "}\n\tlayer = " << layer	<< "\n\trotation = " << rotation << "\n\tscale = " 
		<< scale << "\n\ttint = {" << ( int ) tint.r << ", " << ( int ) tint.g << ", " 
		<< ( int ) tint.b << "}\n\tpivotPoint = {" << pivotPoint.x << ", " << pivotPoint.y 
		<< "}\n";
}

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/