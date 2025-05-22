/* noeRouge - custom Camer.cpp
*  Worked on by: Adam Aronow, Andrew Thomas */

#include "raylib.h"			//Library with animation, rendering, interactive, and sound tools
#include "raymath.h"		//Library for  Math functions to work with Vector2, Vector3, Matrix
#include "vector"			//Library for the vector data structure
#include "baseSprite.h"		//Class that handles layering of sprites
#include "staticSprite.h"	//Class that handles fixed sprites
#include "globals.h"		//Class that handles global variables
#include "maphandler.h"		//Class that handles the objects within the map
#include "customCamera.h"	//The .h file for this class

extern MapHandler* mapHandler;  //Declare pointer to maphandler

/*-------------------------------------------------------------------------------------------------
*  The CustomCamera class handles rendering visual output to the screen
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* CustomCamera( Vector2 position, Vector2 resolution, float renderScale )
	* ---------------------------------------------------------------------------------------------
	* @names:  
	* @brief:  Constructs a new CustomCamera object
	* @param:  position - starting center coordinates of CustomCamera 
	* @param:  resolution - width and height of the CustomCamera to be rendered
	* @param:  renderScale - the scale by which to zoom in and out
	* @return: none
	*--------------------------------------------------------------------------------------------*/
CustomCamera::CustomCamera( Vector2 position, Vector2 resolution, float renderScale )
{
	buffer = { };
	renderTexture = LoadRenderTexture( ( int ) resolution.x, ( int ) resolution.y );
	this->resolution = resolution;
	setPosition( position );
	this->renderScale = renderScale;
	viewRectangle = { position.x - resolution.x / 2, position.y - resolution.y / 2, 
		resolution.x, resolution.y };
}

	/*---------------------------------------------------------------------------------------------
	* addToBuffer( BaseSprite* sprite )
	* @brief:  adds a sprite to the buffer
	* @param:  sprite - the sprite object to be added
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void CustomCamera::addToBuffer( BaseSprite* sprite )
{
	buffer.push_back( sprite );
}

	/*---------------------------------------------------------------------------------------------
	* getPosition( )
	* @brief:  returns the position of the camera's center
	* @param:  none
	* @return: Vector2 - The center position of the camera
	*--------------------------------------------------------------------------------------------*/
Vector2 CustomCamera::getPosition( )
{
	return centeredPosition;
}

	/*---------------------------------------------------------------------------------------------
	* setPosition( Vector2 position )
	* @brief:  sets the position of the camera's center
	* @param:  position - the coordinated to set the CustomCamera centerPosition to
	* @return: Rectangle - the new position of the CustomCamera
	*--------------------------------------------------------------------------------------------*/
Rectangle CustomCamera::setPosition( Vector2 position )
{
	this->centeredPosition = position;
	this->realPosition = { position.x - resolution.x / 2, position.y - resolution.y / 2 };
	viewRectangle = { realPosition.x, realPosition.y, resolution.x, resolution.y };
	return viewRectangle;
}

	/*---------------------------------------------------------------------------------------------
	* prepareRender( )
	* @brief:  sorts and renders all sprites in the buffer to a texture, later used by the 
	*		   renderToScreen method
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void CustomCamera::prepareRender( )
{
		// Culling sprites that aren't within the camera's view
		// Iteration has to occur backwards because indices are shifted back when deleting elements
	for ( int i = buffer.size( ) - 1; i >= 0; i-- )
	{
		if ( !buffer.at( i )->isWithinRect( viewRectangle ) )
		{
			buffer.erase( buffer.begin( ) + i );
		}
	}

		// Sorting buffer by layer (lowest to highest) - Andrew
	for ( int i = 0; i < buffer.size( ); i++ )
	{
		int minIndex = i;                          //variable to track lowest layer value
		for ( int j = i + 1; j < buffer.size( ); j++ )
		{
			if ( *buffer[ j ] < *buffer[ minIndex ] )
			{
				minIndex = j;
			}
		}
		BaseSprite* temp = buffer[ i ];
		buffer[ i ] = buffer[ minIndex ];
		buffer[ minIndex ] = temp;
	}

		// Rendering everything in the buffer to the intermediate texture
	BeginTextureMode( renderTexture );
	ClearBackground( BLACK );
	for ( BaseSprite* sprite : buffer )
	{
		sprite->render( realPosition );
	}
	prepareUI(); //-devon

	buffer.clear( );
	EndTextureMode( );
}

	/*---------------------------------------------------------------------------------------------
	* prepareUI()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  gets UI sprites ready to render, used by prepareRender -devon
	* @param:  none
	* @return: none
	*
	* @notes: Best practice would have been creating a UI class and using extremely high layer 
	*         values to sidestep the layer sorting vs tacking them onto the end of the camera's 
	*         render function. 
	*		  Additionally, the spacing of the hearts probably shouldn't be tied to the tile size.
	*--------------------------------------------------------------------------------------------*/
void CustomCamera::prepareUI()
{
	int hp = mapHandler->getPlayer()->getHealth();	//players health points
	int spacing = 3 * Settings::TILE_SIZE / 4;		//distance between heart containers on screen

		// Render full hearts
	for (int i = 1; i <= hp; i++)
	{
		float locationX = spacing * i;
		BaseSprite* hpSprite = new StaticSprite("fullHeart", { locationX,Settings::TILE_SIZE / 2 }, 100);
		hpSprite->render(realPosition);
	}
		// Render empty hearts
	for (int i = hp + 1; i <= mapHandler->getPlayer()->maxHp; i++)
	{
		float locationX = spacing * i;
		BaseSprite* hpSprite = new StaticSprite("emptyHeart", { locationX,Settings::TILE_SIZE / 2 }, 100);
		hpSprite->render(realPosition);
	}
}

	/*---------------------------------------------------------------------------------------------
	* renderToScreen( )
	* ---------------------------------------------------------------------------------------------
	* @names: 
	* @brief:  renders the camera's intermediate renderTexture to the screen
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void CustomCamera::renderToScreen( )
{
	DrawTexturePro( renderTexture.texture, { 0, 0, resolution.x, -resolution.y },
							{ 0, 0, resolution.x * renderScale, resolution.y * renderScale },
							{ 0, 0 }, 0, WHITE );
}

/*  Changes made during commenting by Evan:
*
*	-Edited C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
* 
*	-Added C-style comment for CustomCamera constructor
* 
*	-PrepareUI Method:*		
*		-Added inline commenting for data members
*/