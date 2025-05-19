/* noeRouge - rectangleSprite.cpp
*  Worked on by: Adam Aronow */

#include "rectangleSprite.h"	 //The .h file for this class

/*-------------------------------------------------------------------------------------------------
*  The RectangleSprite class creates rectangles and allows for modification of RectangleSprite
*  characteristics
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* update( Rectangle rectangle, float layer, Color color, int thickness )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates all data members with new values
	* @param:  rectangle - Raylib Rectangle object
	* @param:  layer - the rendering layer of the Rectangle
	* @param:  color - the color of the rectangle
	* @param:  thickness - the thickness of the Rectangle
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void RectangleSprite::update( Rectangle rectangle, float layer, Color color, int thickness )
{
	this->rectangle = rectangle;
	this->layer = layer;
	this->color = color;
	this->thickness = thickness;
}

    /*---------------------------------------------------------------------------------------------
	* update( Rectangle rectangle, float layer )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  updates select data members with new values
	* @param:  rectangle - Raylib Rectangle object
	* @param:  layer - the rendering layer of the Rectangle
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void RectangleSprite::update( Rectangle rectangle, float layer )
{
	this->rectangle = rectangle;
	this->layer = layer;
}

	/*---------------------------------------------------------------------------------------------
	* isWithinRect( Rectangle rect )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  checks if the sprite is within the camera
	* @param:  rect - the bounding rectangle of the camera
	* @return: bool - true if the RectangleSprite's rectangle is within rect, else returns false
	*--------------------------------------------------------------------------------------------*/
bool RectangleSprite::isWithinRect( Rectangle rect )
{
	return CheckCollisionRecs( rect, this->rectangle );
}

	/*---------------------------------------------------------------------------------------------
	* render( Vector2 cameraPosition )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  renders the texture to the camera
	* @param:  cameraPosition - current coordinates of the camers
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void RectangleSprite::render( Vector2 cameraPosition )
{
	if ( thickness == -1 )
	{
		DrawRectangle( rectangle.x - cameraPosition.x, rectangle.y - cameraPosition.y, 
					   rectangle.width, rectangle.height, color );
	}
	else
	{
		DrawRectangleLinesEx( { rectangle.x - cameraPosition.x, rectangle.y - cameraPosition.y, 
							    rectangle.width, rectangle.height }, thickness, color );
	}
}

	/*---------------------------------------------------------------------------------------------
	* print( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  prints all sprite information to the console
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void RectangleSprite::print( )
{
	std::cout << "Sprite " << this << ":\n\trectangle = {" << rectangle.x << ", " 
		<< rectangle.y << ", " << rectangle.width << ", " << rectangle.height << "}\n\tlayer = " 
		<< layer << "\n\tcolor = {" << ( int ) color.r << ", " << ( int ) color.g <<
		", " << ( int ) color.b << "}\n\tthickness = " << thickness << "\n";
}

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/