/*
* Adam Aronow
*/

#include "generateTileSprites.h"

extern const int WIDTH;
extern const int HEIGHT;

std::vector<Sprite> generateTileSprites( Floor *floor )
{
	std::vector<Sprite> tileSprites = { };

	for ( int x = 0; x < WIDTH; x++ )
	{
		for ( int y = 0; y < HEIGHT; y++ )
		{
			if ( floor->data[ x ][ y ] == '.' || floor->data[ x ][ y ] == '<' )
			{
				tileSprites.push_back( SheetSprite( "floor", { 16, 16, 16, 16 }, { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );

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
					bool downLeftNotWall = ( x > 0 && floor->data[ x - 1 ][ y + 1 ] == '#' && floor->data[ x - 1 ][ y + 1 ] == '*' );
					bool downRightNotWall = ( x + 1 < WIDTH && floor->data[ x + 1 ][ y + 1 ] == '#' && floor->data[ x + 1 ][ y + 1 ] == '*' );
					float sheetOffsetX = 16;
					if ( downLeftNotWall && downRightNotWall ) { sheetOffsetX = 48; }
					else if ( downLeftNotWall )                { sheetOffsetX = 0; }
					else if ( downRightNotWall )               { sheetOffsetX = 32; }

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

	//for ( Rectangle wall : floors[ floorOn ]->getWalls( ) )       //make the wall sprites for the starting floor
	//{
	//	wallSprites.push_back( SheetSprite( "wallA", { 48, 0, 16, 16 }, { wall.x, wall.y }, wall.y ) );
	//}

	return tileSprites;
}