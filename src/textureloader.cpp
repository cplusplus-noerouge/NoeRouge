/*
* Adam Aronow
*/

#include "textureLoader.h"

extern std::unordered_map<std::string, Texture2D> textureMap;

/*-----------------------------------------------------------------------------------------
* @brief: loads every texture and assigns it to the textureMap with a corresponding string
*/
void loadAllTextures( )
{
	textureMap[ "missingTexture" ] = LoadTexture((char*)"../../../assets/graphics/missingTexture.png");
	textureMap[ "player" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder player down (1).png" );
	textureMap[ "enemy" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder enemy (1).png" );
	textureMap[ "projectile" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder projectile (1).png" );
	textureMap[ "wall" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder wall tile.png" );
	textureMap[ "floor" ] = LoadTexture( ( char* ) "../../../assets/graphics/placeholders/Placeholder floor tile.png" );
	textureMap[ "ladderUp" ] = LoadTexture((char*)"../../../assets/graphics/placeholders/Placeholder ladderUp.png");
	textureMap[ "ladderDown" ] = LoadTexture((char*)"../../../assets/graphics/placeholders/Placeholder ladderDown.png");
	textureMap[ "doorClosed" ] = LoadTexture((char*)"../../../assets/graphics/doorBaseV.png");
	textureMap[ "doorOpen" ] = LoadTexture((char*)"../../../assets/graphics/doorV.png");
}

/*---------------------------------------------
* @brief: unloads every texture in textureMap
*/
void unloadAllTextures( )
{
	for ( auto i = textureMap.begin( ); i != textureMap.end( ); i++ )
	{
		UnloadTexture( i->second );
	}
}