/* noeRouge - interactable.cpp
*  Worked on by: Devon */

#include <iostream>		    //Library for input and output streams
#include "customCamera.h"	//Class that handles rendering visual output to the screen
#include "interactable.h"	//The .h file for this class
#include "mapHandler.h"     //Class that handles the map object
#include "sprite.h"         //Class that handles sprite objects

extern CustomCamera mainCamera;
extern MapHandler* mapHandler;

/*-------------------------------------------------------------------------------------------------
* Interactable: an object with a position and an "interact" method that the player can optionally 
*               call when nearby
* Ladder: interactable that changes the player's floor
* Door: interactable that changes its own state, open or closed
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* Interactable( )
	* ---------------------------------------------------------------------------------------------
	* @names
	* @brief:  Default constructor for Interactable objects
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Interactable::Interactable( )
{
	position = { 0,0 };
	sprite = Sprite("missingTexture", position, position.y);
}

	/*---------------------------------------------------------------------------------------------
	* Interactable(Vector2 pos)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Creates an Interactable object with a starting position
	* @param:  pos - the objects starting coordinates
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Interactable::Interactable(Vector2 pos)
{
	position = pos;
	sprite = Sprite("missingTexture", position, position.y);
}

	/*---------------------------------------------------------------------------------------------
	* Interactable(Vector2 pos, std::string texture)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Creates an Interactable object with a starting position and a texture
	* @param:  pos - the objects starting coordinates
	* @param:  texture - the texture to be rendered to the object
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Interactable::Interactable(Vector2 pos, std::string texture)
{
	position = pos;
	sprite = Sprite(texture, position, position.y);
}

	/*---------------------------------------------------------------------------------------------
	* onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  renders the current state of the Interactable object
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Interactable::onRender( )
{
	sprite.update(position, 0);
	mainCamera.addToBuffer(&sprite);
}

	/*---------------------------------------------------------------------------------------------
	* onTick( const std::vector<Rectangle> collidables )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Method stub for future functionality
	* @param:  collidables
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Interactable::onTick( const std::vector<Rectangle> collidables )
{
	//do nothing
}

	/*---------------------------------------------------------------------------------------------
	* Ladder( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Default ladder constructor
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Ladder::Ladder( )
{
	isLadderUp = false;
}
	
	/*---------------------------------------------------------------------------------------------
	* Ladder( Vector2 pos, bool isLadderUp)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Creates a ladder object with a starting location and whether it is an up ladder
	*          and assigns the appropriate texture    
	* @param:  pos - the ladders starting coordinates
	* @param:  isLadderUp - whether the ladder is an up ladder 
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Ladder::Ladder( Vector2 pos, bool isLadderUp):
	Interactable( pos )
{
	this->isLadderUp = isLadderUp;
	if (isLadderUp)
	{
		sprite = Sprite( "ladderUp", pos, pos.y );
	}
	else
	{
		sprite = Sprite("ladderDown", pos, pos.y);
	}
};

	/*---------------------------------------------------------------------------------------------
	* interact( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Changes which floor the player is on when a Ladder object is interacted with
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Ladder::interact( )
{
	mapHandler->changeFloor(isLadderUp);
}

	/*---------------------------------------------------------------------------------------------
	* onRender( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Renders the current state of the Ladder object
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Ladder::onRender( )
{
	sprite.update( Vector2Subtract( position, { 0, 8 } ), position.y - 8 );
	mainCamera.addToBuffer( &sprite );
}

	/*---------------------------------------------------------------------------------------------
	* createLadder( Vector2 position, bool isLadderUp)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  creates a new ladder in 'this' object handler
	* @param:  position - coordinates of the new Ladder object
	* @param:  isLadderUp - whether this object is an up ladder
	* @return: Ladder* - new Ladder object pointer
	*--------------------------------------------------------------------------------------------*/
Ladder* ObjectHandler::createLadder( Vector2 position, bool isLadderUp)
{
	Ladder* ladder = new Ladder( position, isLadderUp);
	allObjects[ ladder->getId( ) ] = ladder; //add <id, object*> to the map
	this->numberOfObjects++;
	return ladder;
}

	/*---------------------------------------------------------------------------------------------
	* Door()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Deafult Door Constructor
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Door::Door()
{
	isClosed = true;
}

	/*---------------------------------------------------------------------------------------------
	* Door(Vector2 pos)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Creates a Door object with coordinates and initialize the door closed
	* @param:  pos - coordinates to place the Door at
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Door::Door(Vector2 pos) :
	Interactable(pos, "doorClosed")
{
	isClosed = true;
}

	/*---------------------------------------------------------------------------------------------
	* interact()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Open or close a Door and it's neighbor Doors, update the Door's sprite
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Door::interact()
{
	isClosed = !isClosed;

	if ( isClosed )
	{
		sprite.setTexture( closedTexture );
	}
	else
	{
		sprite.setTexture( openTexture );
	}

	std::vector<Interactable*> interacts = mapHandler->getInteractables( );
	for ( auto it = interacts.begin( ); it != interacts.end( ); ++it )
	{
		Door* casted = dynamic_cast< Door* >( *it );
		if ( casted && ( casted->getId( ) != this->getId( ) ) )
		{
			if ( Vector2Distance( this->getPos( ), casted->getPos( ) ) < ( Settings::TILE_SIZE * 2.1f ) ) //I picked 2.1 at random.
			{
				if ( isClosed )
				{
					casted->isClosed = true;
					casted->sprite.setTexture( closedTexture );
				}
				else
				{
					casted->isClosed = false;
					casted->sprite.setTexture( openTexture );
				}
			}
		}
			
	}
}

//creates a new door in 'this' object handler

	/*---------------------------------------------------------------------------------------------
	* createDoor(Vector2 position)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  creates a new door in 'this' object handler
	* @param:  position - the coordinates to create the Door at
	* @return: Door* - Pointer to new Door object
	*--------------------------------------------------------------------------------------------*/

Door* ObjectHandler::createDoor(Vector2 position)
{
	Door* door = new Door(position);
	allObjects[door->getId()] = door; //add <id, object*> to the map
	this->numberOfObjects++;
	return door;
}

	/*---------------------------------------------------------------------------------------------
	* HpPickup()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Method for future functionality
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
HpPickup::HpPickup()
{
	//do nothing
}

	/*---------------------------------------------------------------------------------------------
	* HpPickup(Vector2 pos)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Called Interactables constructor to create a healthpack 
	* @param:  pos - coordinates to create the healthpack at
	* @return: none
	*--------------------------------------------------------------------------------------------*/
HpPickup::HpPickup(Vector2 pos)
	:Interactable(pos, "healthPack")
{
	//do nothing
}

	/*---------------------------------------------------------------------------------------------
	* interact()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  plays sound effect and heals players health upon interaction with a healthpack
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void HpPickup::interact()
{
	PlaySound(sfx["itemPickup.mp3"]);
	mapHandler->getPlayer()->healHp(hpRestored);

		//remove the healthpickup from its object handler, removing it from the game
	mapHandler->getCurrentFloor()->getObjHandler()->removeObject(getId());
}

	/*---------------------------------------------------------------------------------------------
	* createHpPickup(Vector2 position)
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  creates a new hpPickup in 'this' object handler
	* @param:  position - coordinates to create a healthpack at
	* @return: HpPickup* - pointer to a new HpPickUp object
	*--------------------------------------------------------------------------------------------*/
HpPickup* ObjectHandler::createHpPickup(Vector2 position)
{
	HpPickup* hpPickup = new HpPickup(position);
	allObjects[hpPickup->getId()] = hpPickup; //add <id, object*> to the map
	this->numberOfObjects++;
	return hpPickup;
}

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*/