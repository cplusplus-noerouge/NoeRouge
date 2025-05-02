/*
* Adam Aronow
*/

#include "generateTileSprites.h"

extern const int WIDTH;
extern const int HEIGHT;

/*---------------------------------------------
* @brief: Assigns a sprite to every visible tile
* @param: *floor = A pointer the the current floor the player is on
* @return: A vector of the sprites created
*/
std::vector<Sprite> generateTileSprites( Floor *floor )
{
	std::vector<Sprite> tileSprites = { };

	for ( int x = 0; x < WIDTH; x++ )
	{
		for ( int y = 0; y < HEIGHT; y++ )
		{
			if ( floor->data[ x ][ y ] == '.' || floor->data[ x ][ y ] == '<' )
			{
				// Determining the tile to reference on the sprite sheet
				Vector2 sheetOffset = { 0, 0 };
				// If there is a wall to the left of the tile
				if ( x == 0 || floor->data[ x - 1 ][ y ] == '#' || floor->data[ x - 1 ][ y ] == '*' )
				{
					sheetOffset.x += 16;
				}
				// If there is a wall to the right of the tile
				if ( x + 1 >= WIDTH || floor->data[ x + 1 ][ y ] == '#' || floor->data[ x + 1 ][ y ] == '*' )
				{
					sheetOffset.x += 32;
				}
				// If there is a wall above of the tile
				if ( y == 0 || floor->data[ x ][ y - 1 ] == '#' || floor->data[ x ][ y - 1 ] == '*' )
				{
					sheetOffset.y += 16;
				}
				// If there is a wall 1 space below and 2 spaces below tile
				if (    ( y + 1 >= HEIGHT || floor->data[ x ][ y + 1 ] == '#' || floor->data[ x ][ y + 1 ] == '*' ) 
					  && ( y + 2 >= HEIGHT || floor->data[ x ][ y + 2 ] == '#' || floor->data[ x ][ y + 2 ] == '*' ) )
				{
					sheetOffset.y += 32;
				}

				tileSprites.push_back( SheetSprite( "floor", { sheetOffset.x, sheetOffset.y, 16, 16 }, { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );

				if ( floor->data[ x ][ y ] == '<' )
				{
					tileSprites.push_back( Sprite( "ladderUp", { ( float ) x * 16, ( float ) y * 16 - 8 }, y * 16 - 8 ) );
				}
			}
			else if ( floor->data[ x ][ y ] == '#' || floor->data[ x ][ y ] == '*' )
			{
				   // If the tile below exists and isn't a wall
				if ( y + 1 < HEIGHT && floor->data[ x ][ y + 1 ] != '#' && floor->data[ x ][ y + 1 ] != '*' )
				{
					   // Determining the tile to reference on the sprite sheet
					float sheetOffsetX = 0;
					   // If there is a wall down and to the left of the tile
					if ( x > 0 && ( floor->data[ x - 1 ][ y + 1 ] == '#' || floor->data[ x - 1 ][ y + 1 ] == '*' ) )
					{
						sheetOffsetX += 16;
					}
					   // If there is a wall down and to the right of the tile
					if ( x + 1 < WIDTH && ( floor->data[ x + 1 ][ y + 1 ] == '#' || floor->data[ x + 1 ][ y + 1 ] == '*' ) )
					{
						sheetOffsetX += 32;
					}

					tileSprites.push_back( SheetSprite( "wallA", { sheetOffsetX, 0, 16, 16 }, { ( float ) x * 16, ( float ) y * 16 }, y * 16 ) );
				}
			}
			else if ( floor->data[ x ][ y ] == '@' )
			{
				// If the tile below exists and is a wall
				if ( y + 1 < HEIGHT && ( floor->data[ x ][ y + 1 ] == '#' || floor->data[ x ][ y + 1 ] == '*' ) )
				{
					tileSprites.push_back( Sprite( "doorBaseH", { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );
				}
				else
				{
					tileSprites.push_back( Sprite( "doorBaseV", { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );
				}
			}
			else if ( floor->data[ x ][ y ] == '>' )
			{
				tileSprites.push_back( Sprite( "hole", { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );
				tileSprites.push_back( Sprite( "ladderDown", { ( float ) x * 16, ( float ) y * 16 - 8 }, y * 16 - 8 ) );
			}
		}
	}

	return tileSprites;
}