/*
* Adam Aronow
*/

#include "raylib.h"
#include "raymath.h"
#include "vector"
//#include "textureloader.cpp"
#include <iostream>

const float defaultCamWidth = 320;
const float defaultCamHeight = 180;

class Sprite
{
	protected:
	Texture2D texture;
	Vector2 position;
	Rectangle sourceRect;
	Rectangle destinationRect;
	Rectangle boundingRect;
	float layer;
	float rotation = 0;
	int scale = 1;
	Color tint = WHITE;
	Vector2 pivotPoint;

	public:
	Sprite( std::string texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	Sprite( Texture2D texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
	{
		update( texture, position, layer, rotation, scale, tint, pivotPoint );
	}

	         // Constructors with fewer parameters
	Sprite( Texture2D texture, Vector2 position, float layer, float rotation, float scale, Color tint )
		: Sprite( texture, position, layer, rotation, scale, tint, Vector2 { 0, 0 } )
	{;}
	Sprite( Texture2D texture, Vector2 position, float layer, float rotation, float scale )
		: Sprite( texture, position, layer, rotation, scale, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( Texture2D texture, Vector2 position, float layer, float rotation )
		: Sprite( texture, position, layer, rotation, 1, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( Texture2D texture, Vector2 position, float layer )
		: Sprite( texture, position, layer, 0, 1, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( std::string texture, Vector2 position, float layer, float rotation, float scale, Color tint )
		: Sprite( texture, position, layer, rotation, scale, tint, Vector2 { 0, 0 } )
	{;}
	Sprite( std::string texture, Vector2 position, float layer, float rotation, float scale )
		: Sprite( texture, position, layer, rotation, scale, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( std::string texture, Vector2 position, float layer, float rotation )
		: Sprite( texture, position, layer, rotation, 1, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( std::string texture, Vector2 position, float layer )
		: Sprite( texture, position, layer, 0, 1, WHITE, Vector2 { 0, 0 } )
	{;}
	Sprite( )
	{;}

	/*-----------------------------------------------
	* @brief: updates all data members with new values
	*/
	void update( Texture2D texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
	{
		this->texture = texture;
		this->position = position;
		this->layer = layer;
		this->rotation = rotation;
		this->scale = scale;
		this->tint = tint;
		this->pivotPoint = pivotPoint;
		updateRectangles( );
	}
	void update( std::string texture, Vector2 position, float layer, float rotation, float scale, Color tint, Vector2 pivotPoint )
	{
		//this->texture = textureMap[texture];
		this->position = position;
		this->layer = layer;
		this->rotation = rotation;
		this->scale = scale;
		this->tint = tint;
		this->pivotPoint = pivotPoint;
		updateRectangles( );
	}
	void update( Vector2 position, float layer )
	{
		this->position = position;
		this->layer = layer;
		this->rotation = rotation;
		updateRectangles( );
	}

	void updateRectangles( )
	{
		Vector2 pivotOffset = Vector2Rotate( pivotPoint, (PI * rotation / 180) );
		destinationRect = { position.x + pivotPoint.x, position.y + pivotPoint.y, ( float ) texture.width * scale, ( float ) texture.height * scale };
		sourceRect = { 0, 0, ( float ) texture.width, ( float ) texture.height };

		if ( rotation == 0 )
		{
			boundingRect = { destinationRect.x + pivotOffset.x, destinationRect.y + pivotOffset.y,
				destinationRect.width, destinationRect.height };
		}
		else
		{
			// safeSize = (longside/2)^2 + 1 | Represents the max width and height that could result from rotating the texture
			float safeSize = sqrt( 2 * pow( ( std::max( destinationRect.width, destinationRect.height ) / 2 ), 2 ) ) + 1;
			boundingRect = { position.x + pivotOffset.x - safeSize, position.y + pivotOffset.y - safeSize,
				safeSize * 2, safeSize * 2 };
		}
	}

	void render( Vector2 cameraPosition )
	{
		Rectangle realDestination = { destinationRect.x - cameraPosition.x, destinationRect.y - cameraPosition.y,
			destinationRect.width, destinationRect.height };
		Vector2 origin = { pivotPoint.x + destinationRect.width / 2, pivotPoint.y + destinationRect.height / 2 };
		DrawTexturePro( texture, sourceRect, realDestination, origin, rotation, tint );
	}

	void print( )
	{
		std::cout << "Sprite " << this << ":\n\tposition = {" << position.x << ", " << position.y << "}\n\tlayer = " << layer
			<< "\n\trotation = " << rotation << "\n\tscale = " << scale << "\n\ttint = {" << (int)tint.r << ", "
			<< ( int ) tint.g << ", " << ( int ) tint.b << "}\n\tpivotPoint = {" << pivotPoint.x << ", " << pivotPoint.y << "}\n";
	}

	bool operator < ( Sprite sprite )
	{
		return layer < sprite.layer;
	}
	bool operator <= ( Sprite sprite )
	{
		return layer <= sprite.layer;
	}
	bool operator > ( Sprite sprite )
	{
		return layer > sprite.layer;
	}
	bool operator >= ( Sprite sprite )
	{
		return layer >= sprite.layer;
	}
	bool operator == ( Sprite sprite )
	{
		return layer == sprite.layer;
	}
	bool operator != ( Sprite sprite )
	{
		return layer != sprite.layer;
	}

	Texture2D getTexture( )
	{
		return texture;
	}
	void setTexture( Texture2D texture )
	{
		this->texture = texture;
		updateRectangles( );
	}
	Vector2 getPosition( )
	{
		return position;
	}
	void setPosition( Vector2 position )
	{
		this->position = position;
		updateRectangles( );
	}
	Rectangle getBoundingRect( )
	{
		return boundingRect;
	}
	float getLayer( )
	{
		return layer;
	}
	void setLayer( float layer )
	{
		this->layer = layer;
	}
	float getRotation( )
	{
		return rotation;
	}
	void setRotation( float rotation )
	{
		this->rotation = rotation;
		updateRectangles( );
	}
	float getScale( )
	{
		return scale;
	}
	void setScale( float scale )
	{
		this->scale = scale;
		updateRectangles( );
	}
	Color getTint( )
	{
		return tint;
	}
	void setTint( Color tint )
	{
		this->tint = tint;
	}
	Vector2 getPivotPoint( )
	{
		return pivotPoint;
	}
	void setPivotPoint( Vector2 pivotPoint )
	{
		this->pivotPoint = pivotPoint;
		updateRectangles( );
	}
};

class CustomCamera
{
	private:
	std::vector<Sprite*> buffer;
	RenderTexture2D renderTexture;
	Vector2 centeredPosition;
	Vector2 realPosition;
	Vector2 resolution;
	float renderScale;               // How much the renderTexture is scaled up when drawing to the screen
	Rectangle viewRectangle;
	public:
	CustomCamera( Vector2 position, Vector2 resolution, float renderScale )
	{
		buffer = { };
		renderTexture = LoadRenderTexture( (int) resolution.x, ( int ) resolution.y );
		this->resolution = resolution;
		setPosition( position );
		this->renderScale = renderScale;
		viewRectangle = { position.x - resolution.x / 2, position.y - resolution.y / 2, resolution.x, resolution.y };
	}
	CustomCamera( Vector2 resolution, float renderScale ) : CustomCamera( Vector2 { 0, 0 }, resolution, renderScale )
	{;}
	CustomCamera( ) : CustomCamera( Vector2 { defaultCamWidth, defaultCamHeight }, 1.0f )
	{;}

	void addToBuffer( Sprite* sprite )
	{
		buffer.push_back( sprite );
	}

	Vector2 getPosition( )
	{
		return centeredPosition;
	}

	Rectangle setPosition( Vector2 position )
	{
		this->centeredPosition = position;
		this->realPosition = { position.x - resolution.x / 2, position.y - resolution.y / 2 };
		viewRectangle = { realPosition.x, realPosition.y, resolution.x, resolution.y };
		return viewRectangle;
	}

	/*---------------------------------------------------------------------------------------------------------
	* @brief: sorts and renders all sprites in the buffer to a texture, later used by the renderToScreen method
	*/
	void prepareRender( )
	{
		   // Culling sprites that aren't within the camera's view
		   // Iteration has to occur backwards because indices are shifted back when deleting elements
		for ( int i = buffer.size( ) - 1; i >= 0; i-- )
		{
			if ( !CheckCollisionRecs( viewRectangle, buffer.at( i )->getBoundingRect() ) )
			{
				buffer.erase( buffer.begin() + i );
			}
		}

		   // Sorting buffer by layer (lowest to highest)
		// TODO: Implement layer sorting
      
		   // Rendering everything in the buffer to a texture
		BeginTextureMode( renderTexture );
		ClearBackground( BLACK );
		for ( Sprite *sprite : buffer )
		{
			sprite->render( realPosition );
		}
		buffer.clear( );
		EndTextureMode( );
	}

	void renderToScreen( )
	{
		{
			DrawTexturePro( renderTexture.texture, { 0, 0, resolution.x, -resolution.y },
								 {0, 0, resolution.x * renderScale, resolution.y * renderScale },
								 {0, 0}, 0, WHITE );
		}
	}
};

class ScreenHandler
{
	private:
	int width = 1280;
	int height = 720;
	int framesPerSecond = 60;
	const char* windowName = (char*)"noeRouge alpha v0.1";

	public:
	std::vector<CustomCamera*> cameras = {}; // The cameras actively being used

	ScreenHandler( )
	{
		InitWindow( width, height, windowName );
		SetTargetFPS( framesPerSecond );
	}

	/*--------------------------------------------------------------
	* @brief: Calls camera render functions and refreshes the screen
	*/
	void renderAll( )
	{
		for ( CustomCamera *camera : cameras )
		{
			camera->prepareRender( );
		}

		BeginDrawing( );
		ClearBackground( BLACK );
		for ( CustomCamera *camera : cameras )
		{
			camera->renderToScreen( );
		}
		EndDrawing( );
	}
};