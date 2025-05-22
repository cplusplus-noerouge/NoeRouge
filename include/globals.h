/* noeRouge - glaboals.h
*  Worked on by: ? */

#pragma once	//only include this .h once

#include <string>	//Library for string objects
#include <raylib.h> //Library with animation, rendering, interactive, and sound tools

/*-------------------------------------------------------------------------------------------------
*  file to hold global variables.
*------------------------------------------------------------------------------------------------*/

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
	extern const int ENEMY_SPEED;
	extern const float TILE_SIZE;
	extern const Vector2 TILE_DIMENSIONS;
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
		return IsKeyDown( KEY_K );
	}
	inline bool dodge( )
	{
		return IsKeyDown( KEY_J );
	}

		//-- Interaction
	inline bool interact()
	{
		return IsKeyPressed(KEY_E);
	}
}

/*  Changes made during commenting by Evan:
*
*	-General Formating
*/