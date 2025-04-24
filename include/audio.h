#pragma once

/*
* By Benjamin Aguilon
* Contains class representing a music player.
* Music players have the ability load and play multiple music files in sequence before looping.
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

	std::vector<Music> songs;
	int currentSongIndex;

public:

	MusicPlayer(bool autoplay = true);	//Default constructor which loads all mp3 files.

	void onTick(); //Updates Music and loops music
};