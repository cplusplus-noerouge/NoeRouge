/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>

// To be commented by Evan
class BaseSprite
{
	protected:
	float layer;   // Determines the order that sprites render on top each other

	public:
	BaseSprite( float layer )
	{
		this->layer = layer;
	}

	BaseSprite( )
	{
		this->layer = 0;
	}

	/*---------------------------------------------------
	* @brief: Checks if the sprite is within the camera
	*/
	virtual bool isWithinRect( Rectangle rect )
	{
		return true;   // Method stub
	}

	virtual void render( Vector2 cameraPosition )
	{
		// Method stub
	}

	virtual void print( )
	{
		std::cout << "BaseSprite " << this << ":\n\tlayer = " << layer;
	}

	// Comparison operator overloads. Based on layer value.
	bool operator < ( BaseSprite sprite )
	{
		return layer < sprite.layer;
	}
	bool operator <= ( BaseSprite sprite )
	{
		return layer <= sprite.layer;
	}
	bool operator > ( BaseSprite sprite )
	{
		return layer > sprite.layer;
	}
	bool operator >= ( BaseSprite sprite )
	{
		return layer >= sprite.layer;
	}
	bool operator == ( BaseSprite sprite )
	{
		return layer == sprite.layer;
	}
	bool operator != ( BaseSprite sprite )
	{
		return layer != sprite.layer;
	}

	float getLayer( )
	{
		return layer;
	}
	void setLayer( float layer )
	{
		this->layer = layer;
	}
};