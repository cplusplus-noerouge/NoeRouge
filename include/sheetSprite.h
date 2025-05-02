/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "sprite.h"
#include "raylib.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

class SheetSprite : public Sprite
{
	public:
	SheetSprite( std::string texture, Rectangle sourceRect, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, sourceRect, position, layer, rotation, scale, tint, pivotPoint );
	}

	SheetSprite( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, sourceRect, position, layer, rotation, scale, tint, pivotPoint );
	}

	SheetSprite( ) : SheetSprite( "playerWalk1", {16, 0, 16, 16}, { 0, 0 }, 0 ) { }

	/*-----------------------------------------------
	* @brief: updates all data members with new values
	*/
	void update( Texture2D texture, Rectangle sourceRect, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint );
	void update( std::string texture, Rectangle sourceRect, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint );

	/*-----------------------------------------------
	* @brief: updates select data members with new values
	*/
	void update( Vector2 position, float layer ) 
	{
		Sprite::update( position, layer );
	}
	void update( Texture2D texture, Rectangle sourceRect );
	void update( std::string texture, Rectangle sourceRect );

	/*------------------------------------------------------------------------------------
	* @brief: updates destinationRect and boundingRect to reflect new values
	*/
	void updateRectangles( );

	/*---------------------------------------------------
	* @brief: prints all sprite information to the console
	*/
	void print( );

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