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

std::vector<Sprite> generateTileSprites( Floor* floor );