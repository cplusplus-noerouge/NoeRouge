
//-- Headerfile to hold global variables.
#pragma once
#include <string>
#include <raylib.h>

namespace Settings
{
	//-- Audio
	extern const std::string ASSETS_ALL;
	extern const std::string ASSETS_MUSIC;
	extern const std::string ASSETS_SFX;
	extern const float VOLUME_MUSIC;
	extern const float VOLUME_SFX;

	//-- Gameplay
	extern const int PLAYER_SPEED;
	extern const float TILE_SIZE;
	extern const int ENEMY_COUNT;
	inline const int NUM_OF_FLOORS = 4;
	
}

namespace Controls
{
	//-- Movement
	inline bool moveUp( )
	{
		return IsKeyDown( KEY_W );
	}
	inline bool moveDown( )
	{
		return IsKeyDown( KEY_S );
	}
	inline bool moveLeft( )
	{
		return IsKeyDown( KEY_A );
	}
	inline bool moveRight( )
	{
		return IsKeyDown( KEY_D );
	}

	//-- Combat
	inline bool attack( )
	{
		return IsKeyPressed( KEY_SPACE );
	}
	inline bool defend( )
	{
		return IsKeyDown( KEY_LEFT_SHIFT );
	}
	inline bool dodge( )
	{
		return IsKeyDown( KEY_LEFT_SHIFT );
	}

	//-- Interaction
	inline bool ladderUp( )
	{
		return IsKeyPressed( KEY_RIGHT_BRACKET );
	}
	inline bool ladderDown( )
	{
		return IsKeyPressed( KEY_LEFT_BRACKET );
	}
}