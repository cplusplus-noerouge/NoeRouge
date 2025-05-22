/* noeRouge - sprite.h
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include <raylib.h>			//Library with animation, rendering, interactive, and sound tools
#include <raymath.h>		//Library for  Math functions to work with Vector2, Vector3, Matrix
#include <vector>			//Library for the vector data structure
#include <iostream>			//Library for input and output streams
#include "baseSprite.h"		//Class that handles layering of sprites
#include "textureLoader.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-------------------------------------------------------------------------------------------------
*  The Sprite class is a base class for all visual objects in the game and has methods
*  for managing those visual objects
*------------------------------------------------------------------------------------------------*/
class Sprite : public BaseSprite
{
	protected:
	Texture2D texture;         // The texture to be rendered to the camera
	Vector2 position;		   // The position in the game world (or position on screen for UI)
	// (this class always uses the whole texture)
	Rectangle sourceRect;      // The rectangle determining what portion of the texture to be rendered
	Rectangle destinationRect; // The rectangle determining where to render the texture to
	Rectangle boundingRect;    // The actual rough area the texture takes up (can be different to destination)
	float rotation;			   // The rotation of the sprite
	int scale;				   // The scale of the sprite
	Color tint = WHITE;		   // The color the sprite is tinted
	Vector2 pivotPoint;        // The point the sprite rotates around (relative to its center)

	public:

		/*-----------------------------------------------------------------------------------------
		* Sprite( std::string texture, Vector2 position, float layer, float rotation = 0,
		*	      float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
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
	Sprite( std::string texture, Vector2 position, float layer, float rotation = 0,
			float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}
		
		/*-----------------------------------------------------------------------------------------
		* prite( Texture2D texture, Vector2 position, float layer, float rotation = 0, 
		*	     float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
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
	Sprite( Texture2D texture, Vector2 position, float layer, float rotation = 0, 
			float scale = 1, Color tint = WHITE, Vector2 pivotPoint = Vector2 { 0, 0 } )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}
		
		/*-----------------------------------------------------------------------------------------
		* Sprite( ) : Sprite( "player1", { 0, 0 }, 0 )
		* -----------------------------------------------------------------------------------------
		* @names:
		* @brief:  Overlaoded Default Constructor
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	Sprite( ) : Sprite( "player1", { 0, 0 }, 0 ) { }

		//updates all data members with new values
	void update( Texture2D texture, Vector2 position, float layer, float rotation, 
				 float scale, Color tint, Vector2 pivotPoint );
	void update( std::string texture, Vector2 position, float layer, float rotation, 
				 float scale, Color tint, Vector2 pivotPoint );

		//updates select data members with new values
	void update( Vector2 position, float layer );

		//updates sourceRect, destinationRect, and boundingRect to reflect new values
	virtual void updateRectangles( );

		//checks if the sprite is within the camera
	virtual bool isWithinRect( Rectangle rect );

		//renders the texture to the camera
	virtual void render( Vector2 cameraPosition );

		//prints all sprite information to the console
	void print( );

		//Setters and Getters
	Texture2D getTexture( )
	{
		return texture;
	}
	void setTexture( Texture2D texture )
	{
		this->texture = texture;
		updateRectangles( );
	}
	void setTexture( std::string texture )
	{
		this->texture = textureMap[ texture ];
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

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/