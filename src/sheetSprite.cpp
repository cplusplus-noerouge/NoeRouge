/* noeRouge - sheetSprite.cpp
*  Worked on by: Adam Aronow */

#include "sheetSprite.h"    //The .h file for this class

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-------------------------------------------------------------------------------------------------
*  The SheetSprite class represents a single "sheet" that has multiple sprites in it
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* update( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, 
	*         float rotation, float scale, Color tint, Vector2 pivotPoint )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates all data members with new values
	* @param:  texture - the texture to be used for the sprite
	* @param:  sourceRect - the location of the sprite on the sheet
	* @param:  position - the sprites position on the screen
	* @param:  layer - the rendering layer of the sprite
	* @param:  rotation - rotation of sprite in degrees
	* @param:  scale - how much the sprite is to be scaled
	* @param:  tint - the color of the sprite
	* @param:  pivotPoint - where the sprite is rotated around 
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::update( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, 
						  float rotation, float scale, Color tint, Vector2 pivotPoint )
{
	this->sourceRect = sourceRect;
	Sprite::update( texture, position, layer, rotation, scale, tint, pivotPoint );
}
	
	/*---------------------------------------------------------------------------------------------
	* update( std::string texture, Rectangle sourceRect, Vector2 position, float layer, 
	*    	  float rotation, float scale, Color tint, Vector2 pivotPoint )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates all data members with new values
	* @param:  texture - the texture to be used for the sprite
	* @param:  sourceRect - the location of the sprite on the sheet
	* @param:  position - the sprites position on the screen
	* @param:  layer - the rendering layer of the sprite
	* @param:  rotation - rotation of sprite in degrees
	* @param:  scale - how much the sprite is to be scaled
	* @param:  tint - the color of the sprite
	* @param:  pivotPoint - where the sprite is rotated around
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::update( std::string texture, Rectangle sourceRect, Vector2 position, float layer,
						  float rotation, float scale, Color tint, Vector2 pivotPoint )
{
	this->sourceRect = sourceRect;
	Sprite::update( texture, position, layer, rotation, scale, tint, pivotPoint );
}

	/*---------------------------------------------------------------------------------------------
	* update( Texture2D texture, Rectangle sourceRect )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates select data members with new values
	* @param:  texture - the texture to be applied to the sprite
	* @param:  sourceRect - the location of the sprite on the sheet
	* @return:
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::update( Texture2D texture, Rectangle sourceRect )
{
	this->texture = texture;
	this->sourceRect = sourceRect;
	updateRectangles( );
}

	/*---------------------------------------------------------------------------------------------
	* update( std::string texture, Rectangle sourceRect )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates select data members with new values
	* @param:  texture - the texture to be applied to the sprite
	* @param:  sourceRect - the location of the sprite on the sheet
	* @return:
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::update( std::string texture, Rectangle sourceRect )
{
	this->texture = textureMap[ texture ];
	this->sourceRect = sourceRect;
	updateRectangles( );
}

	/*---------------------------------------------------------------------------------------------
	* updateRectangles( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates destinationRect and boundingRect to reflect new values
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::updateRectangles( )
{
	Vector2 pivotOffset = Vector2Rotate( pivotPoint, ( PI * rotation / 180 ) );
	destinationRect = { position.x + pivotPoint.x, position.y + pivotPoint.y, 
						sourceRect.width * scale, sourceRect.height * scale };

	if ( rotation == 0 )
	{
		boundingRect = { destinationRect.x - destinationRect.width/2, destinationRect.y 
			- destinationRect.height/2, destinationRect.width, destinationRect.height };
	}
	else
	{
			// safeSize = (longside/2)^2 + 1 | Represents the max width and height that could 
			//result from rotating the texture
		float safeSize = sqrt( 2 * pow( ( std::max( destinationRect.width, 
                               destinationRect.height ) / 2 ), 2 ) ) + 1;
		boundingRect = { position.x - safeSize, position.y - safeSize, safeSize * 2, safeSize * 2 };
	}
}

	/*---------------------------------------------------------------------------------------------
	* print( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  prints all sprite information to the console
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void SheetSprite::print( )
{
	std::cout << "Sprite " << this << ":\n\tsourceRect = {" << sourceRect.x << ", " << sourceRect.y 
		<< ", " << sourceRect.width	<< ", " << sourceRect.height << "}\n\tposition = {" 
		<< position.x << ", " << position.y << "}\n\tlayer = " << layer	<< "\n\trotation = " 
		<< rotation << "\n\tscale = " << scale << "\n\ttint = {" << ( int ) tint.r << ", "
		<< ( int ) tint.g << ", " << ( int ) tint.b << "}\n\tpivotPoint = {" << pivotPoint.x << ", " 
		<< pivotPoint.y << "}\n";
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