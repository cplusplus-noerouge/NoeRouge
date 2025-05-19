/* noeRouge - screenHandler.h
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include <raylib.h>			//Library with animation, rendering, interactive, and sound tools
#include <vector>			//Library for the vector data structure
#include "customCamera.h"	//Class that handles rendering visual output to the screen

/*-------------------------------------------------------------------------------------------------
*  The ScreenHandler class manages the dimensions and frame rate of the game, and handles the 
*  CustomCamera objects
*------------------------------------------------------------------------------------------------*/
class ScreenHandler
{
	private:

	int width = 1280;			//width of camera in pixels
	int height = 720;           //height of camera in pixels
	int framesPerSecond = 60;   //frames to render per second
	const char* windowName = ( char* ) "noeRouge alpha v0.1";	//name of the game window

	public:

	std::vector<CustomCamera*> cameras = {}; // The cameras actively being used
		
		//Constructor
	ScreenHandler( );

		//Calls camera render functions and refreshes the screen
	void renderAll( );
};