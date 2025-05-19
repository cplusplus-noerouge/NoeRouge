/* noeRouge - screenHandler.cpp
*  Worked on by: Adam Aronow */

#pragma once	//only include this .h once

#include "screenHandler.h"	//The .h file for this class
	
/*-------------------------------------------------------------------------------------------------
*  The ScreenHandler class manages the dimensions and frame rate of the game, and handles the
*  CustomCamera objects
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* ScreenHandler( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Constructor, initializes window for the game
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
ScreenHandler::ScreenHandler( )
{
	InitWindow( width, height, windowName );
	SetTargetFPS( framesPerSecond );
}

	/*---------------------------------------------------------------------------------------------
	* renderAll( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Calls camera render functions and refreshes the screen
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void ScreenHandler::renderAll( )
{
	for ( CustomCamera* camera : cameras )
	{
		camera->prepareRender( );
	}

	BeginDrawing( );
	ClearBackground( BLACK );
	for ( CustomCamera* camera : cameras )
	{
		camera->renderToScreen( );
	}
	EndDrawing( );
}