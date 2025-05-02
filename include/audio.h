#pragma once

/*
* By Benjamin Aguilon
* Contains class representing a music player.
* Music players have the ability load and play multiple music files in sequence before looping.
* Music players can be paused and unpaused.
* Once unpaused, the music will continue from where it left off.
* Can change the volume of every song.
* Music can be reset to the first song.
* Destructor will unload all songs.
*/

#include <raylib.h>
#include <filesystem>
#include <vector>
#include <string>

const float DEFAULT_VOLUME = 1.0f;
const std::string MUSIC_PATH = "../../../assets/audio/music/";    // I hate this

class MusicPlayer
{

private:

   std::vector<Music> songs;    //List of all songs to be loaded from folder.
	int currentSongIndex;    //Current song index.
	bool paused;    //If the music is paused or not.

public:

	MusicPlayer(bool autoplay = true);    //Default constructor which loads all mp3 files.

	~MusicPlayer( );    //Destructor which unloads all songs.

	void onTick();    //Updates Music and loops music.

	void togglePause( );    //To stop and start music.

	void setVolume( float setVolume );    //Sets the volume of all songs.

	void reset( bool autoplay = true );    //Stops all songs and resets to first song.
};