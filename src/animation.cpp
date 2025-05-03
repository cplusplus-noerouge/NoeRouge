/*
* Worked on by:
* Adam Aronow
*/

#include "animation.h"

Animation::Animation( int frames, float frameLength )
{
	interframeDelta = 0;
	this->frameLength = frameLength;
	frame = 1;
	maxFrame = frames;
}

Animation::Animation( )
{
	interframeDelta = 0;
	frameLength = 0.1;
	frame = 1;
	maxFrame = 2;
}

/*--------------------------------------------------
* @brief: resets back to the start of the animation
*/
void Animation::reset( )
{
	interframeDelta = 0;
	frame = 1;
}

void Animation::onTick( )
{
	interframeDelta += GetFrameTime( );
	if ( interframeDelta >= frameLength )
	{
		float frameIncrease = interframeDelta / frameLength;
		frame += (int) frameIncrease;
		interframeDelta = ( frameIncrease - ( int ) frameIncrease ) * frameLength;
		frame = ( frame - 1 ) % maxFrame + 1;
	}
}