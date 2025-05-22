/* noeRouge - sheetSprite.h
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include "sprite.h"     //Class that handles sprite objects
#include <raylib.h>		//Library with animation, rendering, interactive, and sound tools

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-------------------------------------------------------------------------------------------------
*  The SheetSprite class represents a single "sheet" that has multiple sprites in it
*------------------------------------------------------------------------------------------------*/
class SheetSprite : public Sprite
{
	public:

		/*-----------------------------------------------------------------------------------------
		* SheetSprite( std::string texture, Rectangle sourceRect, Vector2 position, float layer, 
		*			   float rotation = 0, float scale = 1, Color tint = WHITE, 
		*		       Vector2 pivotPoint = Vector2 { 0, 0 } )
		* -----------------------------------------------------------------------------------------
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
		*----------------------------------------------------------------------------------------*/
	SheetSprite( std::string texture, Rectangle sourceRect, Vector2 position, float layer, 
				 float rotation = 0, float scale = 1, Color tint = WHITE, 
				 Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, sourceRect, position, layer, rotation, scale, tint, pivotPoint );
	}
		/*-----------------------------------------------------------------------------------------
		* SheetSprite( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, 
		*		         float rotation = 0, float scale = 1, Color tint = WHITE, 
		*		         Vector2 pivotPoint = Vector2 { 0, 0 } )
		* -----------------------------------------------------------------------------------------
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
		*----------------------------------------------------------------------------------------*/
	SheetSprite( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, 
				 float rotation = 0, float scale = 1, Color tint = WHITE, 
				 Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, sourceRect, position, layer, rotation, scale, tint, pivotPoint );
	}

		/*-----------------------------------------------------------------------------------------
		* SheetSprite( )
		* -----------------------------------------------------------------------------------------
		* @names:  
		* @brief:  Overloaded Default Constructor
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	SheetSprite( ) : SheetSprite( "playerWalk1", {16, 0, 16, 16}, { 0, 0 }, 0 ) { }

		////updates select data members with new values
	void update( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, 
				 float rotation, float scale, Color tint, Vector2 pivotPoint );
	void update( std::string texture, Rectangle sourceRect, Vector2 position, float layer, 
				 float rotation, float scale, Color tint, Vector2 pivotPoint );
	void update( Vector2 position, float layer ) 
	{
		Sprite::update( position, layer );
	}
	void update( Texture2D texture, Rectangle sourceRect );
	void update( std::string texture, Rectangle sourceRect );


		//updates destinationRect and boundingRect to reflect new values
	void updateRectangles( );

		//prints all sprite information to the console
	void print( );

		//Getters and Setters
	void setTexture( Texture2D texture )
	{
		this->texture = texture;
	}
	void setTexture( std::string texture )
	{
		this->texture = textureMap[ texture ];
	}
	Rectangle getSourceRect( )
	{
		return sourceRect;
	}
	void setSourceRect( Rectangle rect )
	{
		sourceRect = rect;
		updateRectangles( );
	}
	Rectangle getBoundingRect( )
	{
		return boundingRect;
	}
};

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/