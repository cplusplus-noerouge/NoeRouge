#include "audio.h"

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
	currentSongIndex = 0;

	for (const auto& entry : std::filesystem::directory_iterator(MUSIC_PATH))
	{
		auto fullPath = entry.path();
		songs.push_back(LoadMusicStream(fullPath.string().c_str()));
		songs.back().looping = false;
		SetMusicVolume(songs.back(), DEFAULT_VOLUME);
	}

	if (autoplay)
	{
		PlayMusicStream(songs[currentSongIndex]);
	}
}

/*
---------------------------------------------------------------------------------------------------
* By: Ben Aguilon
* Decription: Checks if current song is finished and next song is played if so.
* Once last song is played, it loops and plays the first song w/ modulus operator.
* Params: None.
* Returns: None.
---------------------------------------------------------------------------------------------------
*/
void MusicPlayer::onTick()
{
	if (!IsMusicStreamPlaying(songs[currentSongIndex]))
	{
		currentSongIndex = (currentSongIndex + 1) % songs.size();
		PlayMusicStream(songs[currentSongIndex]);
	}

	UpdateMusicStream(songs[currentSongIndex]);
}

