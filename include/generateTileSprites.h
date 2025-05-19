/* noeRouge - generateTileSprites.h
*  Worked on by: Adam Aronow, Devon Johnson*/

#pragma once	//only include this .h once

#include <iostream>			//Library for input and output streams
#include <vector>			//Library for the vector data structure
#include "raylib.h"			//Library with animation, rendering, interactive, and sound tools
#include "sprite.h"         //Class that handles sprite objects
#include "sheetSprite.h"	//Class that handles sprite sheets
#include "staticSprite.h"	//Class that handles fixed sprites
#include "mapGen.h"			//Class that nadles the map object

	//Assigns a sprite to every visible tile
std::vector<Sprite> generateTileSprites( char data[ WIDTH ][ HEIGHT ] );

	//Gets the name of a random wall decor texture - devon
std::string getRandomWallDecor();

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*/