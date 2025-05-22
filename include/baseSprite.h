/* noeRouge - baseSprite.h
*  Worked on by: Adam Aronow */

#pragma once			//only include this .h once

#include "raylib.h"     //Library with animation, rendering, interactive, and sound tools
#include <raymath.h>    //Library for  Math functions to work with Vector2, Vector3, Matrix
#include <iostream>		//Library for input and output streams

/*-------------------------------------------------------------------------------------------------
*  The BaseSprite class handles the different layers that sprites can render on
*------------------------------------------------------------------------------------------------*/
class BaseSprite
{
	protected:
	float layer;   // Determines the order that sprites render on top each other

	public:
		/*-----------------------------------------------------------------------------------------
		* BaseSprite( float layer )
		* -----------------------------------------------------------------------------------------
		* @names:  Adam Aronow
		* @brief:  Constructs a BaseSprite with a specific layer value
		* @param:  layer - The layer to assign to the BaseSprite instance
		* @return: none
		*----------------------------------------------------------------------------------------*/
	BaseSprite( float layer )
	{
		this->layer = layer;
	}
		/*-----------------------------------------------------------------------------------------
		* BaseSprite( )
		* -----------------------------------------------------------------------------------------
		* @names:  Adam Aronow
		* @brief:  Constructs a BaseSprite with default layer value of 0
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	BaseSprite( )
	{
		this->layer = 0;
	}
		
		/*-----------------------------------------------------------------------------------------
		* isWithinRect( Rectangle rect )
		* -----------------------------------------------------------------------------------------
		* @names:  Adam Aranow
		* @brief:  Checks if the sprite is within the camera
		* @param:  rect - the coordinates of the camera
		* @return: bool - if the BaseSprite object is withib the camera
		*----------------------------------------------------------------------------------------*/
	virtual bool isWithinRect( Rectangle rect )
	{
		return true;   // Method stub
	}

		/*-----------------------------------------------------------------------------------------
		* render( Vector2 cameraPosition )
		* ---------------------------------------------------------------------------------------------
		* @names:  Adam Aranow
		* @brief:  Method stub for future functionality
		* @param:  cameraPosition - current coordinates of the camera
		* @return: none
		*----------------------------------------------------------------------------------------*/
	virtual void render( Vector2 cameraPosition )
	{
		// Method stub
	}

		/*-----------------------------------------------------------------------------------------
		* print( )
		* -----------------------------------------------------------------------------------------
		* @names:  Adam Aranow
		* @brief:  Prints the layer of the class instance
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	virtual void print( )
	{
		std::cout << "BaseSprite " << this << ":\n\tlayer = " << layer;
	}

		/*-----------------------------------------------------------------------------------------
		* Overloaded Operators
		* -----------------------------------------------------------------------------------------
		* @names:  Adam Aranow
		* @brief:  Comparison operator overloads. Based on layer value.
		* @param:  sprite - a BaseSprite object
		* @return: bool
		*----------------------------------------------------------------------------------------*/
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
		//Setters and Getters
	float getLayer( )
	{
		return layer;
	}
	void setLayer( float layer )
	{
		this->layer = layer;
	}
};

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*/