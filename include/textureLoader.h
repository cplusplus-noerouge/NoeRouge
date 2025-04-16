/*
* Adam Aronow
*/

#pragma once
#include <unordered_map>
#include <iostream>
#include "raylib.h"

// extern std::unordered_map<std::string, Texture2D> textureMap;

/*-----------------------------------------------------------------------------------------
* @brief: loads every texture and assigns it to the textureMap with a corresponding string
*/
void loadAllTextures( );

/*---------------------------------------------
* @brief: unloads every texture in textureMap
*/
void unloadAllTextures( );