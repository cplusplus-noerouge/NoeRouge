#pragma once  
#include <unordered_map>  
#include <string>  
#include "raylib.h"  

extern std::unordered_map<std::string, Texture2D> textureMap;  

void loadAllTextures();
