/*
* Worked on by:
* Adam Aronow, Andrew Thomas
*/

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "vector"
#include "baseSprite.h"

// Ideally these should be global, I just haven't figured out how to get it
// to accept the varables as part of the constructor otherwise.
const float defaultCamWidth = 320;    // The default width for all cameras
const float defaultCamHeight = 180;   // The default height for all cameras

class CustomCamera
{
	private:
	std::vector<BaseSprite*> buffer;   // The sprites being rendered to this camera at the end of the current frame
	RenderTexture2D renderTexture;   // The intermediate texture everything will be rendered to before reaching the screen
	Vector2 centeredPosition;   // The position of the camera's center in the game world
	Vector2 realPosition;   // The position of the top left corner of the camera in the game world
	Vector2 resolution;   // The width and height of the camera
	float renderScale;   // How much the renderTexture is scaled up when drawing to the screen
	Rectangle viewRectangle;   // The rectangle representation of the bounds of the camera's view in the game world
	public:
	CustomCamera( Vector2 position = { 0, 0 }, Vector2 resolution = { defaultCamWidth, defaultCamHeight }, float renderScale = 1.0f );

	CustomCamera( Vector2 resolution, float renderScale ) : CustomCamera( { 0, 0 }, resolution, renderScale )
	{

	}

	/*-------------------------------------
	* @brief: adds a sprite to the buffer
	*/
	void addToBuffer( BaseSprite* sprite );

	/*-----------------------------------------------------
	* @brief: returns the position of the camera's center
	*/
	Vector2 getPosition( );

	/*--------------------------------------------------
	* @brief: sets the position of the camera's center
	*/
	Rectangle setPosition( Vector2 position );

	/*---------------------------------------------------------------------------------------------------------
	* @brief: sorts and renders all sprites in the buffer to a texture, later used by the renderToScreen method
	*/
	void prepareRender( );

	/*--------------------------------------------------
	* @brief: renders the camera's intermediate renderTexture to the screen
	*/
	void renderToScreen( );
};