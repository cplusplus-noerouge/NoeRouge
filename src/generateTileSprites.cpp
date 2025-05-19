/* noeRouge - generateTileSprites.cpp
*  Worked on by: Adam Aronow, Devon Johnson */

#include "generateTileSprites.h"	//The .h file for this class

extern const int WIDTH;		//maximum x of each floor in tiles from mapGen.h
extern const int HEIGHT;	//maximum y of each floor in tiles from mapGen.h

	/*---------------------------------------------------------------------------------------------
	* generateTileSprites( char data[ WIDTH ][ HEIGHT ] );
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Assigns a sprite to every visible tile
	* @param:  data - 2D array of the dungeon map
	* @return: Vector -  A vector of the sprites created
	*--------------------------------------------------------------------------------------------*/
std::vector<Sprite> generateTileSprites( char data[ WIDTH ][ HEIGHT ] )
{
	std::vector<Sprite> tileSprites = { };

	for ( int x = 0; x < WIDTH; x++ )
	{
		for ( int y = 0; y < HEIGHT; y++ )
		{
			if ( data[ x ][ y ] == '.' || data[ x ][ y ] == 'E' || data[ x ][ y ] == '<' )
			{
					// Determining the tile to reference on the sprite sheet
				Vector2 sheetOffset = { 0, 0 };
					// If there is a wall to the left of the tile
				if ( x == 0 || data[ x - 1 ][ y ] == '#' || data[ x - 1 ][ y ] == '*' )
				{
					sheetOffset.x += 16;
				}
					// If there is a wall to the right of the tile
				if ( x + 1 >= WIDTH || data[ x + 1 ][ y ] == '#' || data[ x + 1 ][ y ] == '*' )
				{
					sheetOffset.x += 32;
				}
					// If there is a wall above of the tile
				if ( y == 0 || data[ x ][ y - 1 ] == '#' || data[ x ][ y - 1 ] == '*' )
				{
					sheetOffset.y += 16;
				}
					// If there is a wall 1 space below and 2 spaces below tile
				if (    ( y + 1 >= HEIGHT || data[ x ][ y + 1 ] == '#' || data[ x ][ y + 1 ] == '*' ) 
					  && ( y + 2 >= HEIGHT || data[ x ][ y + 2 ] == '#' || data[ x ][ y + 2 ] == '*' ) )
				{
					sheetOffset.y += 32;
				}

				tileSprites.push_back( SheetSprite( "floor", { sheetOffset.x, sheetOffset.y, 16, 16 }, 
												 { ( float ) x * 16, ( float ) y * 16 }, y * 16 - 999 ) );
			}
			else if ( data[ x ][ y ] == '#' || data[ x ][ y ] == '*' )
			{
				   // If the tile below exists and isn't a wall
				if ( y + 1 < HEIGHT && data[ x ][ y + 1 ] != '#' && data[ x ][ y + 1 ] != '*' )
				{
					   // Determining the tile to reference on the sprite sheet
					float sheetOffsetX = 0;
					   // If there is a wall down and to the left of the tile
					if ( x > 0 && ( data[ x - 1 ][ y + 1 ] == '#' || data[ x - 1 ][ y + 1 ] == '*' ) )
					{
						sheetOffsetX += 16;
					}
					   // If there is a wall down and to the right of the tile
					if ( x + 1 < WIDTH && ( data[ x + 1 ][ y + 1 ] == '#' || 
											data[ x + 1 ][ y + 1 ] == '*' ) )
					{
						sheetOffsetX += 32;
					}

					tileSprites.push_back( SheetSprite( "wallA", { sheetOffsetX, 0, 16, 16 }, 
														{ ( float ) x * 16, ( float ) y * 16 }, 
														y * 16 ) );

						// Add a decoration to some walls - devon
					if ( rand() % 2 )
					{
						std::string texture = getRandomWallDecor();
						tileSprites.push_back(Sprite(texture, { (float)x * 16, 
													  (float)y * 16 }, y * 16 + 1));
					}
				}
			}
			else if ( data[ x ][ y ] == '@' )
			{
					// If the tile below exists and is a wall or door
				if ( y + 1 < HEIGHT && ( data[ x ][ y + 1 ] == '#' || data[ x ][ y + 1 ] == '*' ||
										 data[x][y + 1] == '@') )
				{
					tileSprites.push_back( Sprite( "doorBaseH", { ( float ) x * 16, ( float ) y 
												   * 16 }, y * 16 - 999 ) );
				}
				else
				{
					tileSprites.push_back( Sprite( "doorBaseV", { ( float ) x * 16, ( float ) y 
												   * 16 }, y * 16 - 999 ) );
				}
			}
			else if ( data[ x ][ y ] == '>' )
			{
				tileSprites.push_back( Sprite( "hole", { ( float ) x * 16, ( float ) y * 16 }, 
											   y * 16 - 999 ) );
			}
		}
	}

	return tileSprites;
}

	/*---------------------------------------------------------------------------------------------
	* getRandomWallDecor()
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  Gets the name of a random wall decor texture - devon
	* @param:  none
	* @return: String - The name of a wall decor texture
	*--------------------------------------------------------------------------------------------*/
std::string getRandomWallDecor()
{
	std::string options[] = { "window1","window2","window3","wallPanel1","wallPanel2","wallPanel3" };
	std::string texture;
	int index = GetRandomValue(1, 5);
	return options[index];
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-Added inline comments to externs
*
*	-General formatting
*/