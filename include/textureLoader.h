/*
* Adam Aronow
*/

#pragma once
#include <unordered_map>
#include <iostream>
#include <string>
#include "raylib.h"

/*---------------------------------------------
* @brief: loads a single texture and assigns it to the textureMap with a corresponding string
* @param: mapName = the label textureMap will relate the texture with
* @param: filePath = the filePath of the texture being loaded in
*/
void loadSingleTexture( std::string mapName, std::string filePath );

/*-----------------------------------------------------------------------------------------
* @brief: loads every texture and assigns it to the textureMap with a corresponding string
*/
void loadAllTextures( );

/*---------------------------------------------
* @brief: unloads every texture in textureMap
*/
void unloadAllTextures( );