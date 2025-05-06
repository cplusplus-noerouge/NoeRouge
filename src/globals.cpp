#include "globals.h"

namespace Settings
{
	const std::string ASSETS_ALL = "../../../assets/";	
	const std::string ASSETS_MUSIC = ASSETS_ALL + "audio/music/";
	const std::string ASSETS_SFX = ASSETS_ALL + "audio/sfx/";
	const float VOLUME_MUSIC = 0.3f;
	const float VOLUME_SFX = 0.8f;

	const float TILE_SIZE = 16;               //The x & y size of each tile in the game world in pixels
	const Vector2 TILE_DIMENSIONS = { 16,16 };
	const int PLAYER_SPEED = 300;
	const int ENEMY_COUNT = 1;
	//NUM_OF_FLOORS initialized in the globals.h file due to array requirements.
}