/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "raylib.h"
#include "vector"
#include "customCamera.h"

class ScreenHandler
{
	private:
	int width = 1280;
	int height = 720;
	int framesPerSecond = 60;
	const char* windowName = ( char* ) "noeRouge alpha v0.1";

	public:
	std::vector<CustomCamera*> cameras = {}; // The cameras actively being used

	ScreenHandler( );

	/*--------------------------------------------------------------
	* @brief: Calls camera render functions and refreshes the screen
	*/
	void renderAll( );
};