/*
* Worked on by:
* Adam Aronow, Andrew Thomas
*/

#include "raylib.h"
#include "raymath.h"
#include "vector"
#include "baseSprite.h"
#include "staticSprite.h"
#include "globals.h"
#include "maphandler.h"
#include "customCamera.h"

extern MapHandler* mapHandler;

CustomCamera::CustomCamera( Vector2 position, Vector2 resolution, float renderScale )
{
	buffer = { };
	renderTexture = LoadRenderTexture( ( int ) resolution.x, ( int ) resolution.y );
	this->resolution = resolution;
	setPosition( position );
	this->renderScale = renderScale;
	viewRectangle = { position.x - resolution.x / 2, position.y - resolution.y / 2, resolution.x, resolution.y };
}

/*-------------------------------------
* @brief: adds a sprite to the buffer
*/
void CustomCamera::addToBuffer( BaseSprite* sprite )
{
	buffer.push_back( sprite );
}

/*-----------------------------------------------------
* @brief: returns the position of the camera's center
*/
Vector2 CustomCamera::getPosition( )
{
	return centeredPosition;
}

/*--------------------------------------------------
* @brief: sets the position of the camera's center
*/
Rectangle CustomCamera::setPosition( Vector2 position )
{
	this->centeredPosition = position;
	this->realPosition = { position.x - resolution.x / 2, position.y - resolution.y / 2 };
	viewRectangle = { realPosition.x, realPosition.y, resolution.x, resolution.y };
	return viewRectangle;
}

/*---------------------------------------------------------------------------------------------------------
* @brief: sorts and renders all sprites in the buffer to a texture, later used by the renderToScreen method
*/
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

/*--------------------------------------------------
* @brief: gets UI sprites ready to render, used by prepareRender -devon
* Notes for the future: Best practice would have been creating a UI class and using extremely high layer values to sidestep 
* the layer sorting vs tacking them onto the end of the camera's render function. 
* Additionally, the spacing of the hearts probably shouldn't be tied to the tile size.
*/
void CustomCamera::prepareUI()
{
	int hp = mapHandler->getPlayer()->getHealth();
	int spacing = 3 * Settings::TILE_SIZE / 4;

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

/*--------------------------------------------------
* @brief: renders the camera's intermediate renderTexture to the screen
*/
void CustomCamera::renderToScreen( )
{
	DrawTexturePro( renderTexture.texture, { 0, 0, resolution.x, -resolution.y },
							{ 0, 0, resolution.x * renderScale, resolution.y * renderScale },
							{ 0, 0 }, 0, WHITE );
}
