/* noeRouge - animation.h
*  Worked on by : Adam Aronow */

#pragma once		 //only include this .h once

#include "raylib.h"  //Library with animation, rendering, interactive, and sound tools

	/*---------------------------------------------------------------------------------------------
	*  The Animation class handles all on screen character and environmental animations
	*--------------------------------------------------------------------------------------------*/
class Animation
{
	private:
	float interframeDelta;    // Time that has passed since last frame was drawn
	float frameLength;        // The amount of time to display each animation frame
	int frame;                // The current frame of the animation
	int maxFrame;             // The number of frames that make up the animation

	public:
		//Animation Class Constructor
	Animation( int frames, float frameLength );

		//Animation Class Default Constructor
	Animation( );

		//Method that resets an Animation back to the starting frame
	void reset( );

		//Method that advances the frames of the Animation based on elapsed time
	void onTick( );


	   //Setters and Getters
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

/*
* Changes made during commenting by Evan:
*
*	-Added inline comments above methods
*	
*	-Commented data members
*/
