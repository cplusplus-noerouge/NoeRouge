/* noeRouge - custom Camer.h
*  Worked on by: Adam Aronow, Andrew Thomas */

#pragma once	//only include this .h once

#include "raylib.h"			//Library with animation, rendering, interactive, and sound tools
#include "raymath.h"		//Library for  Math functions to work with Vector2, Vector3, Matrix
#include "vector"			//Library for the vector data structure
#include "baseSprite.h"		//Class that handles layering of sprites

	/*---------------------------------------------------------------------------------------------
	* Ideally these should be global, I just haven't figured out how to get it
	* to accept the varables as part of the constructor otherwise.
	*--------------------------------------------------------------------------------------------*/
const float DEFAULT_CAM_HEIGHT = 320;	// The default width for all cameras
const float DEFAULT_CAM_WIDTH = 180;	// The default height for all cameras

	/*---------------------------------------------------------------------------------------------
	*  The CustomCamera class handles rendering visual output to the screen
	*--------------------------------------------------------------------------------------------*/
class CustomCamera
{
	private:
	std::vector<BaseSprite*> buffer;    // The sprites being rendered to this camera at the end of the current frame
	RenderTexture2D renderTexture;		// The intermediate texture everything will be rendered to before reaching the screen
	Vector2 centeredPosition;			// The position of the camera's center in the game world
	Vector2 realPosition;				// The position of the top left corner of the camera in the game world
	Vector2 resolution;					// The width and height of the camera
	float renderScale;					// How much the renderTexture is scaled up when drawing to the screen
	
	Rectangle viewRectangle;   // The rectangle representation of the bounds of the camera's view in the game world

		//gets UI sprites ready to render, used by prepareRender -devon
	void prepareUI();

	public:
		//Parameterized Class constructor, sets position and resolution to defaults
	CustomCamera( Vector2 position = { 0, 0 }, Vector2 resolution = { DEFAULT_CAM_WIDTH, DEFAULT_CAM_HEIGHT }, 
				  float renderScale = 1.0f );

		//Parameterized Class constructor, sets position and resolution to input values
	CustomCamera( Vector2 resolution, float renderScale ) : CustomCamera( { 0, 0 }, resolution, renderScale )
	{

	}
		
		//adds a sprite to the buffer
	void addToBuffer( BaseSprite* sprite );

		//returns the position of the camera's center	
	Vector2 getPosition( );

		//sets the position of the camera's center
	Rectangle setPosition( Vector2 position );

		//sorts and renders all sprites in the buffer to a texture, later used by the renderToScreen method
	void prepareRender( );

		//renders the camera's intermediate renderTexture to the screen
	void renderToScreen( );
};

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above class declaration
*
*	-Added inline comments to #includes
*
*	-General formatting
*/