/*
* Worked on by:
* Adam Aronow
*/

#include "rectangleSprite.h"

/*-----------------------------------------------
* @brief: updates all data members with new values
*/
void RectangleSprite::update( Rectangle rectangle, float layer, Color color, int thickness )
{
	this->rectangle = rectangle;
	this->layer = layer;
	this->color = color;
	this->thickness = thickness;
}

/*-----------------------------------------------
* @brief: updates select data members with new values
*/
void RectangleSprite::update( Rectangle rectangle, float layer )
{
	this->rectangle = rectangle;
	this->layer = layer;
}

/*---------------------------------------------------
* @brief: checks if the sprite is within the camera
* @param: Rectangle rect = the bounding rectangle of the camera
*/
bool RectangleSprite::isWithinRect( Rectangle rect )
{
	return CheckCollisionRecs( rect, this->rectangle );
}

/*---------------------------------------------------
* @brief: renders the texture to the camera
*/
void RectangleSprite::render( Vector2 cameraPosition )
{
	if ( thickness == -1 )
	{
		DrawRectangle( rectangle.x - cameraPosition.x, rectangle.y - cameraPosition.y, rectangle.width, rectangle.height, color );
	}
	else
	{
		DrawRectangleLinesEx( { rectangle.x - cameraPosition.x, rectangle.y - cameraPosition.y, rectangle.width, rectangle.height }, thickness, color );
	}
}

/*---------------------------------------------------
* @brief: prints all sprite information to the console
*/
void RectangleSprite::print( )
{
	std::cout << "Sprite " << this << ":\n\trectangle = {" << rectangle.x << ", " << rectangle.y << ", " << rectangle.width
		<< ", " << rectangle.height << "}\n\tlayer = " << layer << "\n\tcolor = {" << ( int ) color.r << ", " << ( int ) color.g <<
		", " << ( int ) color.b << "}\n\tthickness = " << thickness << "\n";
}