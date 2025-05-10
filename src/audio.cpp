#include "audio.h"
#include <raylib.h>
#include <raymath.h>
#include "globals.h"

std::map<std::string, Sound> sfx = {};

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Loads all music within "music" folder and adds them to list.  
* Params: autoplay, to optionally immediately start the music player once instantiated.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
MusicPlayer::MusicPlayer(bool autoplay)
{
	songs = {};
	paused = true;
	currentSongIndex = 0;

	for (const auto& entry : std::filesystem::directory_iterator( Settings::ASSETS_SFX ))
	{
		std::string fullPath = entry.path().string();

		std::filesystem::path filePath(fullPath);
		std::string filename = filePath.filename().string();
		sfx.insert({ filename, LoadSound(fullPath.c_str()) });
		SetSoundVolume(sfx[filename], Settings::VOLUME_SFX );
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

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Uses range for loop to unload all music streams.
* Params: None.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
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

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Checks if current song is finished and next song is played if so.
* Once last song is played, it loops and plays the first song w/ modulus operator.
* If paused, it immediately returns.
* Params: None.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
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

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Toggles if song is paused or not, once unpaused, it continues from where it left off.
* Params: None.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
void MusicPlayer::togglePause( )
{
	paused = !paused;
}

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Sets the volume of all songs to the given value, clamped between 0.0 and 1.0.
* Params: volume, a float which determines the volume of all songs.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
void MusicPlayer::setVolume( float volume )
{
	volume = Clamp( volume, 0.0f, 1.0f );

	for ( const auto& song : songs )
	{
		SetMusicVolume( song, volume );
	} 
}

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Stops every song and resets the current song index to 0 and is paused.
* If autoplay is true, it plays the first song in the list and paused is set to false.
* Params: autoplay, to optionally immediately start the music from the start.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
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