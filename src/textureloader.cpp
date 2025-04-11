/*
* Adam Aronow
*/

#include <iostream>
#include <unordered_map>
#include "raylib.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

static void loadAllTextures( )
{
	textureMap[ "player" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder player down (1).png" );
	textureMap[ "enemy" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder enemy (1).png" );
	textureMap[ "projectile" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder projectile (1).png" );
	textureMap[ "wall" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder wall tile.png" );
	textureMap[ "floor" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder floor tile.png" );
}

static void unloadAllTextures( )
{
	for ( auto i = textureMap.begin( ); i != textureMap.end( ); i++ )
	{
		UnloadTexture( i->second );
	}
}