/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "screenHandler.h"

ScreenHandler::ScreenHandler( )
{
	InitWindow( width, height, windowName );
	SetTargetFPS( framesPerSecond );
}

/*--------------------------------------------------------------
* @brief: Calls camera render functions and refreshes the screen
*/
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