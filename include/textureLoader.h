/* noeRouge - textureLoader.h
*  Worked on by: Dam Aronow */

#pragma once	//only include this .h once

#include <unordered_map>
#include <iostream>		  //Library for input and output streams
#include <string>		  //Library for string objects
#include <raylib.h>		  //Library with animation, rendering, interactive, and sound tools

	//loads a single texture and assigns it to the textureMap with a corresponding string
void loadSingleTexture( std::string mapName, std::string filePath );

	//loads every texture and assigns it to the textureMap with a corresponding string
void loadAllTextures( );

	//unloads every texture in textureMap
void unloadAllTextures( );

/*  Changes made during commenting by Evan:
*
*	-Added inline comments to #includes
*
*	-General formatting
*/