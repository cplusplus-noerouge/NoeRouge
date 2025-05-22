/* noeRouge - glaboals.cpp
*  Worked on by: ? */

#include "globals.h"    // //The .h file for this class

/*-------------------------------------------------------------------------------------------------
*  file to hold global variables.
*------------------------------------------------------------------------------------------------*/
namespace Settings
{
	const std::string ASSETS_ALL = "../../../assets/";	
	const std::string ASSETS_MUSIC = ASSETS_ALL + "audio/music/";
	const std::string ASSETS_SFX = ASSETS_ALL + "audio/sfx/";
	const float VOLUME_MUSIC = 0.3f;
	const float VOLUME_SFX = 0.8f;

	const float TILE_SIZE = 16;         //The x & y size of each tile in the game world in pixels
	const Vector2 TILE_DIMENSIONS = { TILE_SIZE, TILE_SIZE };
	const int PLAYER_SPEED = 120;
	const int ENEMY_SPEED = 50;
	const int ENEMY_COUNT = 1;

}

/*  Changes made during commenting by Evan:
*
*	-General Formating
*/