/* noeRouge - staticSprite.h
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include <raylib.h>		    //Library with animation, rendering, interactive, and sound tools
#include <raymath.h>	    //Library for  Math functions to work with Vector2, Vector3, Matrix
#include <vector>		    //Library for the vector data structure
#include <iostream>		    //Library for input and output streams
#include "sprite.h"         //Class that handles sprite objects
#include "textureLoader.h"  //Class that loads textures from local directory

/*-------------------------------------------------------------------------------------------------
*  The StaticSprite class creates sprites that do not move on the screen
*------------------------------------------------------------------------------------------------*/
class StaticSprite : public Sprite
{
	public:

		/*-----------------------------------------------------------------------------------------
		* StaticSprite( std::string texture, Vector2 position, float layer, float rotation = 0, 
		*	     		float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
		* -----------------------------------------------------------------------------------------
		* @names:
		* @brief:  updates all data members with new values
		* @param:  texture - the texture to be used for the sprite
		* @param:  position - the sprites position on the screen
		* @param:  layer - the rendering layer of the sprite
		* @param:  rotation - rotation of sprite in degrees
		* @param:  scale - how much the sprite is to be scaled
		* @param:  tint - the color of the sprite
		* @param:  pivotPoint - where the sprite is rotated around
		* @return:
		*----------------------------------------------------------------------------------------*/
	StaticSprite( std::string texture, Vector2 position, float layer, float rotation = 0, 
				  float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}
		/*-----------------------------------------------------------------------------------------
		* StaticSprite( Texture2D texture, Vector2 position, float layer, float rotation = 0, 
		*				float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
		* -----------------------------------------------------------------------------------------
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
		*----------------------------------------------------------------------------------------*/
	StaticSprite( Texture2D texture, Vector2 position, float layer, float rotation = 0, 
				  float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}
		/*-----------------------------------------------------------------------------------------
		* StaticSprite( )
		* -----------------------------------------------------------------------------------------
		* @names:
		* @brief:  Overloaded Default Constructor
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	StaticSprite( ) : Sprite( "player1", { 0, 0 }, 0 ) { }

		//checks if the sprite is within the camera
	bool isWithinRect( Rectangle rect );

		//renders the texture to the camera
	void render( Vector2 cameraPosition );
};