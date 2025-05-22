/* noeRouge - textureLoader.cpp
*  Worked on by: Dam Aronow */

#include "textureLoader.h"	//The .h file for this class

extern std::unordered_map<std::string, Texture2D> textureMap;

	/*---------------------------------------------------------------------------------------------
	* loadSingleTexture( std::string mapName, std::string filePath )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  loads a single texture and assigns it to the textureMap with a corresponding string
	* @param:  mapName - the label textureMap will relate the texture with
	* @param:  filePath - the filePath of the texture being loaded in
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void loadSingleTexture( std::string mapName, std::string filePath )
{
	textureMap[ mapName ] = LoadTexture( filePath.c_str( ) );
}

	/*---------------------------------------------------------------------------------------------
	* loadAllTextures( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  loads every texture and assigns it to the textureMap with a corresponding string
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void loadAllTextures( )
{
	std::string filePath;
	   
		// Player textures
	filePath = "../../../assets/graphics/player/";
	for ( int i = 1; i <= 4; i++ )
	{
		loadSingleTexture( "playerWalk"    + std::to_string( i ), filePath + "playerWalk"    +
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "playerWalkGun" + std::to_string( i ), filePath + "playerWalkGun" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "playerWalkAim" + std::to_string( i ), filePath + "playerWalkAim" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "playerShoot"   + std::to_string( i ), filePath + "playerShoot"   + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "playerHurt"    + std::to_string( i ), filePath + "playerHurt"    + 
						   std::to_string( i ) + ".png" );
	}
	for ( int i = 1; i <= 3; i++ )
	{
		loadSingleTexture( "shootFlash" + std::to_string( i ), filePath + "shootFlash" + 
						   std::to_string( i ) + ".png" );
	}
	loadSingleTexture( "playerProjectile", filePath + "playerProjectile.png" );

		// Alien textures
	filePath = "../../../assets/graphics/alien/";
	for ( int i = 1; i <= 4; i++ )
	{
		loadSingleTexture( "alienAWalk" + std::to_string( i ), filePath + "alienAWalkSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienAHurt" + std::to_string( i ), filePath + "alienAHurtSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienBWalk" + std::to_string( i ), filePath + "alienBWalkSheet" +
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienBHurt" + std::to_string( i ), filePath + "alienBHurtSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienCWalk" + std::to_string( i ), filePath + "alienCWalkSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienCHurt" + std::to_string( i ), filePath + "alienCHurtSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienDWalk" + std::to_string( i ), filePath + "alienDWalkSheet" + 
						   std::to_string( i ) + ".png" );
		loadSingleTexture( "alienDHurt" + std::to_string( i ), filePath + "alienDHurtSheet" + 
						   std::to_string( i ) + ".png" );
	}
	loadSingleTexture( "enemyProjectile", filePath + "enemyProjectile.png" );

		// Tile textures
	filePath = "../../../assets/graphics/tiles/";
	loadSingleTexture( "creditImage", filePath + "creditImage.png" );
    loadSingleTexture( "planetTitle", filePath + "greenPlanetBackGround.png" );
	loadSingleTexture( "spaceBackground", filePath + "spaceBackground.png" );
	loadSingleTexture( "ladderDown", filePath + "ladderDown.png" );
	loadSingleTexture( "ladderUp", filePath + "ladderUp.png" );
	loadSingleTexture( "hole", filePath + "hole.png" );
	loadSingleTexture( "doorH", filePath + "doorH.png" );
	loadSingleTexture( "doorV", filePath + "doorV.png" );
	loadSingleTexture( "doorBaseH", filePath + "doorBaseH.png" );
	loadSingleTexture( "doorBaseV", filePath + "doorBaseV.png" );
	loadSingleTexture( "floor", filePath + "floorSheet.png" );
	loadSingleTexture( "wallA", filePath + "wallSheetA.png" );
	loadSingleTexture( "wallB", filePath + "wallSheetB.png" );
	loadSingleTexture( "wallC", filePath + "wallSheetC.png" );
	loadSingleTexture( "window1", filePath + "window1.png" );
	loadSingleTexture( "window2", filePath + "window2.png");
	loadSingleTexture( "window3", filePath + "window3.png");
	loadSingleTexture( "wallPanel1", filePath + "wallPanel1.png");
	loadSingleTexture( "wallPanel2", filePath + "wallPanel2.png");
	loadSingleTexture( "wallPanel3", filePath + "wallPanel3.png");

		// Item textures
	filePath = "../../../assets/graphics/items/";
	loadSingleTexture( "ammoBox",    filePath + "ammoBox.png" );
	loadSingleTexture( "boots",      filePath + "boots.png" );
	loadSingleTexture( "gun",        filePath + "gun.png" );
	loadSingleTexture( "healthPack", filePath + "healthPack.png" );

		// Misc textures
	filePath = "../../../assets/graphics/";
	loadSingleTexture( "missingTexture", filePath + "missingTexture.png" );
	loadSingleTexture( "gameOverOverlay", filePath + "gameOverOverlay.png" );
	loadSingleTexture( "winOverlay", filePath + "WinOverlay.png" );

		// UI textures
	filePath = "../../../assets/graphics/ui/";
	loadSingleTexture("fullHeart", filePath + "fullHeart.png");
	loadSingleTexture("emptyHeart", filePath + "emptyHeart.png");

		//these are temporary because I'm not sure how the door graphics are supposed to be used - devon
	loadSingleTexture("doorOpen", "../../../assets/graphics/doorOpen.png");
	loadSingleTexture("doorClosed", "../../../assets/graphics/doorClosed.png");
}

	/*---------------------------------------------------------------------------------------------
	* unloadAllTextures( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  unloads every texture in textureMap
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void unloadAllTextures( )
{
	for ( auto i = textureMap.begin( ); i != textureMap.end( ); i++ )
	{
		UnloadTexture( i->second );
	}
}

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*	-General formatting
*/