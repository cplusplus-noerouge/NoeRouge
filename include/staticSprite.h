/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "vector"
#include <iostream>
#include "sprite.h"
#include "textureLoader.h"

// To be commented by Evan
class StaticSprite : public Sprite
{
	public:
	StaticSprite( std::string texture, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	StaticSprite( Texture2D texture, Vector2 position, float layer, float rotation = 0, float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	StaticSprite( ) : Sprite( "player1", { 0, 0 }, 0 ) { }

	/*---------------------------------------------------
	* @brief: checks if the sprite is within the camera
	* @param: Rectangle rect = the bounding rectangle of the camera
	*/
	bool isWithinRect( Rectangle rect );

	/*---------------------------------------------------
	* @brief: renders the texture to the camera
	*/
	void render( Vector2 cameraPosition );
};