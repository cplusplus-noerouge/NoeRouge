/*
* Worked on by:
* Adam Aronow
*/

#pragma once

#include "raylib.h"

class Animation
{
	private:
	float interframeDelta;
	float frameLength;
	int frame;
	int maxFrame;

	public:
	Animation( int frames, float frameLength );

	Animation( );

	/*--------------------------------------------------
	* @brief: resets back to the start of the animation
	*/
	void reset( );

	void onTick( );

	float getInterframeDelta( )
	{
		return interframeDelta;
	}
	void setInterframeDelta( float value )
	{
		interframeDelta = value;
	}
	float getFrameLength( )
	{
		return frameLength;
	}
	void setFrameLength( float value )
	{
		frameLength = value;
	}
	int getFrame( )
	{
		return frame;
	}
	void setFrame( int value )
	{
		frame = value;
	}
	int getMaxFrame( )
	{
		return maxFrame;
	}
	void setMaxFrame( int value )
	{
		maxFrame = value;
	}
};