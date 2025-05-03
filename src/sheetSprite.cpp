/*
* Worked on by:
* Adam Aronow
*/

#include "sheetSprite.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-----------------------------------------------
* @brief: updates all data members with new values
*/
void SheetSprite::update( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
{
	this->sourceRect = sourceRect;
	Sprite::update( texture, position, layer, rotation, scale, tint, pivotPoint );
}

void SheetSprite::update( std::string texture, Rectangle sourceRect, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
{
	this->sourceRect = sourceRect;
	Sprite::update( texture, position, layer, rotation, scale, tint, pivotPoint );
}

/*-----------------------------------------------
* @brief: updates select data members with new values
*/
void SheetSprite::update( Texture2D texture, Rectangle sourceRect )
{
	this->texture = texture;
	this->sourceRect = sourceRect;
	updateRectangles( );
}
void SheetSprite::update( std::string texture, Rectangle sourceRect )
{
	this->texture = textureMap[ texture ];
	this->sourceRect = sourceRect;
	updateRectangles( );
}

/*------------------------------------------------------------------------------------
* @brief: updates destinationRect and boundingRect to reflect new values
*/
void SheetSprite::updateRectangles( )
{
	Vector2 pivotOffset = Vector2Rotate( pivotPoint, ( PI * rotation / 180 ) );
	destinationRect = { position.x + pivotPoint.x, position.y + pivotPoint.y, sourceRect.width * scale, sourceRect.height * scale };

	if ( rotation == 0 )
	{
		boundingRect = { destinationRect.x + pivotOffset.x, destinationRect.y + pivotOffset.y,
			destinationRect.width, destinationRect.height };
	}
	else
	{
		// safeSize = (longside/2)^2 + 1 | Represents the max width and height that could result from rotating the texture
		float safeSize = sqrt( 2 * pow( ( std::max( destinationRect.width, destinationRect.height ) / 2 ), 2 ) ) + 1;
		boundingRect = { position.x + pivotOffset.x - safeSize, position.y + pivotOffset.y - safeSize,
			safeSize * 2, safeSize * 2 };
	}
}

/*---------------------------------------------------
* @brief: prints all sprite information to the console
*/
void SheetSprite::print( )
{
	std::cout << "Sprite " << this << ":\n\tsourceRect = {" << sourceRect.x << ", " << sourceRect.y << ", " << sourceRect.width
		<< ", " << sourceRect.height << "}\n\tposition = {" << position.x << ", " << position.y << "}\n\tlayer = " << layer
		<< "\n\trotation = " << rotation << "\n\tscale = " << scale << "\n\ttint = {" << ( int ) tint.r << ", "
		<< ( int ) tint.g << ", " << ( int ) tint.b << "}\n\tpivotPoint = {" << pivotPoint.x << ", " << pivotPoint.y << "}\n";
}