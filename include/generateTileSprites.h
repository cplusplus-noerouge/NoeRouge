/*
* Adam Aronow
*/

#pragma once

#include <iostream>
#include <vector>
#include "raylib.h"
#include "sprite.h"
#include "sheetSprite.h"
#include "staticSprite.h"
#include "mapGen.h"

/*---------------------------------------------
* @brief: Assigns a sprite to every visible tile
* @param: *floor = A pointer the the current floor the player is on
* @return: A vector of the sprites created
*/
std::vector<Sprite> generateTileSprites( char data[ WIDTH ][ HEIGHT ] );

/*---------------------------------------------
* @brief: Gets the name of a random wall decor texture
*   - devon
* @param: None
* @return: The name of a wall decor texture
*/
std::string getRandomWallDecor();