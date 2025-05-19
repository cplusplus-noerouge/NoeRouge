/* noeRouge - audio.cpp
*  Worked on by: Ben Aguilon */

#include "audio.h"		//The .h file for this class		
#include "globals.h"	//Class that handles global variables
#include <raylib.h>		//Library with animation, rendering, interactive, and sound tools
#include <raymath.h>	//Library for  Math functions to work with Vector2, Vector3, Matrix and Quaternions

std::map<std::string, Sound> sfx = {};

/*-------------------------------------------------------------------------------------------------
*  The MusicPlayer class is a class to handle the functions needed to play audio
-------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* MusicPlayer(bool autoplay)
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Loads all music within "music" folder and adds them to list.  
	* @param:  autoplay - to optionally immediately start the music player once instantiated.
	* @return: none
	---------------------------------------------------------------------------------------------*/
MusicPlayer::MusicPlayer(bool autoplay)
{
	songs = {};
	paused = true;
	currentSongIndex = 0;
	std::string fullPath;	//path to music directory in local system 
	std::string fileName;	//string to hold the music directory path 

	for (const auto& entry : std::filesystem::directory_iterator( Settings::ASSETS_SFX ))
	{
		fullPath = entry.path().string();

		std::filesystem::path filePath(fullPath);
		fileName = filePath.filename().string();
		sfx.insert({ fileName, LoadSound(fullPath.c_str()) });
		SetSoundVolume(sfx[fileName], Settings::VOLUME_SFX );
	}

	for (const auto& entry : std::filesystem::directory_iterator( Settings::ASSETS_MUSIC ))
	{
		auto fullPath = entry.path();
		songs.push_back(LoadMusicStream(fullPath.string().c_str()));
		songs.back().looping = false;
		SetMusicVolume(songs.back(), Settings::VOLUME_MUSIC );
	}

	if (autoplay)
	{
		PlayMusicStream(songs[currentSongIndex]);
		paused = false;
	}
}

	/*---------------------------------------------------------------------------------------------
	* ~MusicPlayer( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Uses range for loop to unload all music streams
	* @param:  none
	* @return: none
	---------------------------------------------------------------------------------------------*/
MusicPlayer::~MusicPlayer( )
{
	for ( auto& song: songs )
	{
		UnloadMusicStream( song );
	}

	for ( auto& sound : sfx )
	{
		UnloadSound(sound.second);
	}
}

	/*---------------------------------------------------------------------------------------------
	* onTick()
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Checks if current song is finished and next song is played if so.
	*		   Once last song is played, it loops and plays the first song w/ modulus operator.
	*		   If paused, it immediately returns.
	* @param:  none
	* @return: none
	---------------------------------------------------------------------------------------------*/
void MusicPlayer::onTick()
{
	if ( paused )
	{
		return;
	}

	if (!IsMusicStreamPlaying(songs[currentSongIndex]))
	{
		currentSongIndex = (currentSongIndex + 1) % songs.size();
		PlayMusicStream(songs[currentSongIndex]);
	}

	UpdateMusicStream(songs[currentSongIndex]);
}

	/*---------------------------------------------------------------------------------------------
	* togglePause( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Toggles if song is paused or not, once unpaused, it continues from where it left off
	* @params: none
	* @return: none
	---------------------------------------------------------------------------------------------*/
void MusicPlayer::togglePause( )
{
	paused = !paused;
}

	/*---------------------------------------------------------------------------------------------
	* setVolume( float volume )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Sets the volume of all songs to the given value, clamped between 0.0 and 1.0
	* @param:  volume - a float which determines the volume of all songs
	* @return: none
	---------------------------------------------------------------------------------------------*/
void MusicPlayer::setVolume( float volume )
{
	volume = Clamp( volume, 0.0f, 1.0f );

	for ( const auto& song : songs )
	{
		SetMusicVolume( song, volume );
	} 
}

	/*---------------------------------------------------------------------------------------------
	* reset( bool autoplay )
	* ---------------------------------------------------------------------------------------------
	* @names:  Ben Aguilon
	* @brief:  Stops every song and resets the current song index to 0 and is paused.
	*		   If autoplay is true, it plays the first song in the list and paused is set to false.
	* @param:  autoplay - to optionally immediately start the music from the start.
	* @return: none
	---------------------------------------------------------------------------------------------*/
void MusicPlayer::reset( bool autoplay )
{
	paused = true;
	currentSongIndex = 0;

	for ( const auto& song : songs )
	{
		StopMusicStream( song );
	}

	if ( autoplay )
	{
		PlayMusicStream( songs[ currentSongIndex ] );
		paused = false;
	}
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-MusicPlayer Constructor:
*		
*		-Declared "fullPath" at the top of the constructor instead of decalaration and initialization
*		 in the for loop for easier readability and commenting
*
*		-Declared "fileName" at the top of the constructor instead of decalaration and initialization
*		 in the for loop for easier readability and commenting
*/