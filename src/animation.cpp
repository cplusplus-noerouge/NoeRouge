/* noeRouge - animation.cpp  
*  Worked on by : Adam Aronow */

#include "animation.h"  //The .h file for this class

/*-------------------------------------------------------------------------------------------------
*  The Animation class handles all on screen character and environmental animations
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* Animation( int frames, float frameLength )
	* ---------------------------------------------------------------------------------------------
	* @names:  Adam Aronow
	* @brief:  Animation Class Constructor
	* @param:  frames - Number of frames that make up the animation
	* @param:  frameLength - The amount of time to display each frame
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Animation::Animation( int frames, float frameLength )
{
	interframeDelta = 0;
	this->frameLength = frameLength;
	frame = 1;
	maxFrame = frames;
}

	/*---------------------------------------------------------------------------------------------
	* Animation( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Adam Aronow
	* @brief:  Animation Class Default Constructor
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Animation::Animation( )
{
	interframeDelta = 0;
	frameLength = 0.1;
	frame = 1;
	maxFrame = 2;
}

	/*---------------------------------------------------------------------------------------------
	* reset( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Adam Aronow
	* @brief:  Method that resets an Animation back to the starting frame
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Animation::reset( )
{
	interframeDelta = 0;
	frame = 1;
}

	/*---------------------------------------------------------------------------------------------
	* onTick( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Adam Aronow
	* @brief:  Method that advances the frames of the Animation based on
	*		   elapsed time
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Animation::onTick( )
{
	float frameIncrease;    //The number of frames to advance the Animation by

		//Track the time elapsed since last frame was drawn
	interframeDelta += GetFrameTime( );

	if ( interframeDelta >= frameLength )
	{
			//Calculate the number of frames to advance by
		frameIncrease = interframeDelta / frameLength;
			//Set current frame to value of frameIncrease
		frame += ( int ) frameIncrease;
			//Subtract float by int to get decimal value of interframeDelta and multiply by frameLength
		interframeDelta = ( frameIncrease - ( int ) frameIncrease ) * frameLength;
			//loops the Animation back to it's first frame when maxFrame is reached
		frame = ( frame - 1 ) % maxFrame + 1;
	}
}

/*
* Changes made during commenting by Evan:
*
*	-onTick Method:
*		- Moved declaration of "frameIncrease" to the top of the method
*		  instead of declaration and initialization in one line 
*		  in the if statement	
*		- Commented the logic of the if statement
*	
*	-Added C-style comments above methods
*/