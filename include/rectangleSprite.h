/* noeRouge - rectangleSprite.h
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include <raylib.h>		//Library with animation, rendering, interactive, and sound tools
#include <raymath.h>	//Library for  Math functions to work with Vector2, Vector3, Matrix
#include <vector>		//Library for the vector data structure
#include <iostream>		//Library for input and output streams
#include "baseSprite.h"	//Class that handles layering of sprites

/*-------------------------------------------------------------------------------------------------
*  The RectangleSprite class creates rectangles and allows for modification of RectangleSprite
*  characteristics
*------------------------------------------------------------------------------------------------*/
class RectangleSprite : public BaseSprite
{
	protected:
	Rectangle rectangle;   // The rectangle being drawn to the screen
	int thickness;         // The thickness of the rectangle, -1 makes it a solid color
	Color color;           // The color of the rectangle

	public:
		
		/*-----------------------------------------------------------------------------------------
		* RectangleSprite( Rectangle rectangle, float layer, Color color = WHITE, 
		*                  int thickness = -1 )
		* -----------------------------------------------------------------------------------------
		* @names:
		* @brief:  RectangleSprite Constructor
		* @param:  rectangle - a Rectangle object 
		* @param:  layer - the layer to set the Rectangle object to
		* @param:  color - sets rectangle color to WHITE 
		* @param:  thickness - sets rectangle to solid
		* @return: none
		*----------------------------------------------------------------------------------------*/
	RectangleSprite( Rectangle rectangle, float layer, Color color = WHITE, int thickness = -1 )
	{
		update( rectangle, layer, color, thickness );
	}
		
		/*-----------------------------------------------------------------------------------------
		* RectangleSprite( { 0, 0, 1, 1 }, 0 ) { }
		* -----------------------------------------------------------------------------------------
		* @names:
		* @brief:  Overloaded Default Constructor
		* @param:  none
		* @return: none
		*----------------------------------------------------------------------------------------*/
	RectangleSprite( ) : RectangleSprite( { 0, 0, 1, 1 }, 0 ) { }

		//updates all data members with new values
	void update( Rectangle rectangle, float layer, Color color, int thickness );
	
		//updates select data members with new values
	void update( Rectangle rectangle, float layer );

		//checks if the sprite is within the camera
	bool isWithinRect( Rectangle rect );

		//renders the texture to the camera
	void render( Vector2 cameraPosition );

		//prints all sprite information to the console
	void print( );

		//Getters and Setters
	Rectangle getRectangle( )
	{
		return rectangle;
	}
	void setRectangle( Rectangle rectangle )
	{
		this->rectangle = rectangle;
	}
	int getThickness( )
	{
		return thickness;
	}
	void setThickness( int thickness )
	{
		this->thickness = thickness;
	}
	Color getColor( )
	{
		return color;
	}
	void setColor( Color color )
	{
		this->color = color;
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