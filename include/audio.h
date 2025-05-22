/* noeRouge - audio.h
*  Worked on by: Ben Aguilon */

	/*---------------------------------------------------------------------------------------------
	* By Benjamin Aguilon
	* Contains class representing a music player.
	* Music players have the ability load and play multiple music files in sequence before looping.
	* Music players can be paused and unpaused.
	* Once unpaused, the music will continue from where it left off.
	* Can change the volume of every song.
	* Music can be reset to the first song.
	* Destructor will unload all songs.
	*--------------------------------------------------------------------------------------------*/

#pragma once	        //only include this .h once

#include "raylib.h"     //Library with animation, rendering, interactive, and sound tools
#include <filesystem>   //Library with tools for performing operations on file systems 
#include <vector>		//Library for the vector data structure
#include <string>		//Library for string objects
#include <map>			//Library for the map data structure


extern std::map<std::string, Sound> sfx;

	/*---------------------------------------------------------------------------------------------
	*  The MusicPlayer class is a class to handle the functions needed to play audio
	---------------------------------------------------------------------------------------------*/
class MusicPlayer
{
private:

    std::vector<Music> songs;	//List of all songs to be loaded from folder
	int currentSongIndex;		//Current song index
	bool paused;				//If the music is paused or not

public:
	
		//Loads all music within "music" folder and adds them to list
	MusicPlayer(bool autoplay = true); 

		//Destructor that uses range for loop to unload all music streams
	~MusicPlayer( );   

		//Checks if current song is finished and if next song has started
	void onTick();   

		// Toggles if song is paused or not, once unpaused, it continues from where it left off
	void togglePause( );    

		//Sets the volume of all songs to the given value, clamped between 0.0 and 1.0
	void setVolume( float setVolume );    

		//Stops every song and resets the current song index to 0 and is paused
	void reset( bool autoplay = true );  
};

/*  Changes made during commenting by Evan:
*
*	-Made C-style comments above methods into in line comments 
*
*	-Added inline comments to #includes
*/