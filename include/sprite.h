/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "vector"
#include <iostream>
#include "baseSprite.h"
#include "textureLoader.h"

class Sprite : public BaseSprite
{
	protected:
	Texture2D texture;   // The texture to be rendered to the camera
	Vector2 position;   // The position in the game world (or position on screen for UI)
	// The rectangle determining what portion of the texture to be rendered
	// (this class always uses the whole texture)
	Rectangle sourceRect;
	Rectangle destinationRect;   // The rectangle determining where to render the texture to
	Rectangle boundingRect;   // The actual rough area the texture takes up (can be different to destination)
	float rotation;   // The rotation of the sprite
	int scale;   // The scale of the sprite
	Color tint = WHITE;   // The color the sprite is tinted
	Vector2 pivotPoint;   // The point the sprite rotates around (relative to its center)

	public:
	Sprite( std::string texture, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	Sprite( Texture2D texture, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	Sprite( ) : Sprite( "player1", { 0, 0 }, 0 ) { }

	/*-----------------------------------------------
	* @brief: updates all data members with new values
	*/
	void update( Texture2D texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint );
	void update( std::string texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint );

	/*-----------------------------------------------
	* @brief: updates select data members with new values
	*/
	void update( Vector2 position, float layer );

	/*------------------------------------------------------------------------------------
	* @brief: updates sourceRect, destinationRect, and boundingRect to reflect new values
	*/
	void updateRectangles( );

	/*---------------------------------------------------
	* @brief: checks if the sprite is within the camera
	* @param: Rectangle rect = the bounding rectangle of the camera
	*/
	bool isWithinRect( Rectangle rect );

	/*---------------------------------------------------
	* @brief: renders the texture to the camera
	*/
	void render( Vector2 cameraPosition );

	/*---------------------------------------------------
	* @brief: prints all sprite information to the console
	*/
	void print( );

	Texture2D getTexture( )
	{
		return texture;
	}
	void setTexture( Texture2D texture )
	{
		this->texture = texture;
		updateRectangles( );
	}
	Vector2 getPosition( )
	{
		return position;
	}
	void setPosition( Vector2 position )
	{
		this->position = position;
		updateRectangles( );
	}
	Rectangle getBoundingRect( )
	{
		return boundingRect;
	}
	float getRotation( )
	{
		return rotation;
	}
	void setRotation( float rotation )
	{
		this->rotation = rotation;
		updateRectangles( );
	}
	float getScale( )
	{
		return scale;
	}
	void setScale( float scale )
	{
		this->scale = scale;
		updateRectangles( );
	}
	Color getTint( )
	{
		return tint;
	}
	void setTint( Color tint )
	{
		this->tint = tint;
	}
	Vector2 getPivotPoint( )
	{
		return pivotPoint;
	}
	void setPivotPoint( Vector2 pivotPoint )
	{
		this->pivotPoint = pivotPoint;
		updateRectangles( );
	}
};