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

// To be commented by Evan
class RectangleSprite : public BaseSprite
{
	protected:
	Rectangle rectangle;   // The rectangle being drawn to the screen
	int thickness;         // The thickness of the rectangle, -1 makes it a solid color
	Color color;           // The color of the rectangle

	public:
	RectangleSprite( Rectangle rectangle, float layer, Color color = WHITE, int thickness = -1 )
	{
		update( rectangle, layer, color, thickness );
	}

	RectangleSprite( ) : RectangleSprite( { 0, 0, 1, 1 }, 0 ) { }

	/*-----------------------------------------------
	* @brief: updates all data members with new values
	*/
	void update( Rectangle rectangle, float layer, Color color, int thickness );
	

	/*-----------------------------------------------
	* @brief: updates select data members with new values
	*/
	void update( Rectangle rectangle, float layer );

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