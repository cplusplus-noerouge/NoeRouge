/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "sprite.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-----------------------------------------------
* @brief: updates all data members with new values
*/
void Sprite::update( Texture2D texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
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
void Sprite::update( std::string texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
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

/*-----------------------------------------------
* @brief: updates select data members with new values
*/
void Sprite::update( Vector2 position, float layer )
{
	this->position = position;
	this->layer = layer;
	updateRectangles( );
}

/*------------------------------------------------------------------------------------
* @brief: updates sourceRect, destinationRect, and boundingRect to reflect new values
*/
void Sprite::updateRectangles( )
{
	Vector2 pivotOffset = Vector2Rotate( pivotPoint, ( PI * rotation / 180 ) );
	destinationRect = { position.x + pivotPoint.x, position.y + pivotPoint.y, ( float ) texture.width * scale, ( float ) texture.height * scale };
	sourceRect = { 0, 0, ( float ) texture.width, ( float ) texture.height };

	if ( rotation == 0 )
	{
		boundingRect = { destinationRect.x - destinationRect.width / 2, destinationRect.y - destinationRect.height / 2,
			destinationRect.width, destinationRect.height };
	}
	else
	{
		// safeSize = (longside/2)^2 + 1 | Represents the max width and height that could result from rotating the texture
		float safeSize = sqrt( 2 * pow( ( std::max( destinationRect.width, destinationRect.height ) / 2 ), 2 ) ) + 1;
		boundingRect = { position.x - safeSize, pivotOffset.y - safeSize, safeSize * 2, safeSize * 2 };
	}
}

/*---------------------------------------------------
* @brief: checks if the sprite is within the camera
* @param: Rectangle rect = the bounding rectangle of the camera
*/
bool Sprite::isWithinRect( Rectangle rect )
{
	return CheckCollisionRecs( rect, this->boundingRect );
}

/*---------------------------------------------------
* @brief: renders the texture to the camera
*/
void Sprite::render( Vector2 cameraPosition )
{
	Rectangle realDestination = { destinationRect.x - cameraPosition.x, destinationRect.y - cameraPosition.y,
		destinationRect.width, destinationRect.height };
	Vector2 origin = { pivotPoint.x + destinationRect.width / 2, pivotPoint.y + destinationRect.height / 2 };
	DrawTexturePro( texture, sourceRect, realDestination, origin, rotation, tint );
}

/*---------------------------------------------------
* @brief: prints all sprite information to the console
*/
void Sprite::print( )
{
	std::cout << "Sprite " << this << ":\n\tposition = {" << position.x << ", " << position.y << "}\n\tlayer = " << layer
		<< "\n\trotation = " << rotation << "\n\tscale = " << scale << "\n\ttint = {" << ( int ) tint.r << ", "
		<< ( int ) tint.g << ", " << ( int ) tint.b << "}\n\tpivotPoint = {" << pivotPoint.x << ", " << pivotPoint.y << "}\n";
}