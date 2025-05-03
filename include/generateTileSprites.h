/*
* Adam Aronow
*/

#pragma once

#include <iostream>
#include <vector>
#include "raylib.h"
#include "sprite.h"
#include "sheetSprite.h"
#include "mapGen.h"

/*---------------------------------------------
* @brief: Assigns a sprite to every visible tile
* @param: *floor = A pointer the the current floor the player is on
* @return: A vector of the sprites created
*/
std::vector<Sprite> generateTileSprites( Floor* floor );