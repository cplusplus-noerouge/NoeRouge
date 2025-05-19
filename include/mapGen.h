/* NoeRouge - mapGen.h
* Worked on by: Devon, Irene, Evan, Ben S */

#pragma once	//only include this .h once

#include <raylib.h>         //Library with animation, rendering, interactive, and sound tools
#include <raymath.h>        //Library for  Math functions to work with Vector2, Vector3, Matrix
#include <list>		        //Library for the list data structure
#include <iostream>	        //Library for input and output streams
#include <vector>	        //Library for the vector data structure
#include <random>	        //Library for random number generation
#include "objecthandler.h"  //Class that manages and keeps track of all GameObjects
#include "object.h"		    //Class that all game objects inherit from
#include "globals.h"		//Class that handles global variables
#include "sprite.h"         //Class that handles sprite objects

const int WIDTH = 70;                   //width/columns/maximum x of each floor in tiles
const int HEIGHT = 30;                  //height/rows/maximum y of each floor in tiles
const int MINSIZE = 10;                 //minimum for each partition/BSP leaf's width and height

const int TILE_SIZE = Settings::TILE_SIZE; //The x & y size of each tile in the game world in pixels

const char WALL = '#';            //char to represent walls
const char FLOOR = '.';           //char to represent floors
const char LADDER_UP = '<';       //ladder to the above floor
const char LADDER_DOWN = '>';     //ladder to the below floor
const char DEBUGPARTITION = '*';  //a wall that is within a partition aka an ok place for rooms to spawn.
const char PLAYER = 'p';          //represents player spawn
const char DOOR = '@';            //represents where doors are
const char ENEMY = 'E';           //represents where the enemies are

/*-------------------------------------------------------------------------------------------------
*  The BspNode class creates nodes in a binary tree that will hold room data
*------------------------------------------------------------------------------------------------*/
class BspNode
{
	public:

	int x, y, width, height;                // position and size of the node
	BspNode* left;                          // pointer to the left child node
	BspNode* right;                         // Pointer to the right child node
	int roomCenterPointXCoordinate;         // x value of the room center point coordinates
	int roomCenterPointYCoordinate;         // y value of the room center point coordinates


	BspNode( int x, int y, int width, int height ) :
		x( x ), y( y ), width( width ), height( height ), left( nullptr ), right( nullptr )
	{ }

		//Function to split the node into two child nodes
	bool split( );

		// collect and return all the leaf nodes in the BSP tree, added this method -devon
	std::list<BspNode*> getAllLeafNodes( );

		//Adds the coordinates for the room center of the node
	void addNodeCenterCoordinates( int xCoord, int yCoord );
};

	//Creates the BSP tree where each leaf node holds that data for one room
BspNode* generateBspTree( );

	// Function to print the dungeon split scheme
void printPartitions( BspNode* node, std::vector<std::vector<char>>& map );

/*-------------------------------------------------------------------------------------------------
*  The Room class creates individual rooms for each node of the BSP tree
*------------------------------------------------------------------------------------------------*/

	//Gets a random number between a lower and upper bounds
int randRange( int minVal, int maxVal );

	//carve out floor tiles inside the partition in a rectangle shape
void makeRectRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] );

	//carve out floor tiles inside the partition in a circle shape
void makeCircleRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] );

	//Fill partition with DEBUGPARTITION char '*'
void makeRoomContainer( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] );

	//calls one or two room making functions that overlap into one room
void makeRandRoomShape( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] );

/*-------------------------------------------------------------------------------------------------
*  The Floor class creates the floors, walls, ladders, and doors in the map
*------------------------------------------------------------------------------------------------*/
class Floor
{
	private:
	std::list<BspNode*> leafPartitions;   //all the leaf nodes and partitions
	std::vector<Rectangle> walls;         
	Vector2 ladderUpLocation;              
	Vector2 ladderDownLocation;           

	ObjectHandler* objHandler;     //contains all the objects on the floor

	void generateMapData( );   //generates data[][], intended to be called by Floor::Floor()
	void generateObjects( );   //populates objectHandler, intended to be called by Floor::Floor()

	public:

	char data[ WIDTH ][ HEIGHT ];           //dungeon map
		
		//generate the partitions
	BspNode* rootNode = generateBspTree( ); 
	std::vector<Sprite> _tileSprites;
	Floor( );

		//Getters and Setters
	BspNode* getMapRootNode( )
	{
		return rootNode;
	}
	std::vector<Rectangle> getWalls( )
	{
		return walls;
	}
	std::vector<Sprite> getTileSprites( )
	{
		return _tileSprites;
	}
	ObjectHandler* getObjHandler( )
	{
		return objHandler;
	}
	Vector2 getLadderUpLocation( );
	Vector2 getLadderDownLocation( );
	Vector2 getEnemySpawn( );

		/*-----------------------------------------------------------------------------------------
		* scaleToTile( int x, int y )
		* -----------------------------------------------------------------------------------------
		* @names: 
		* @brief:  scales up the coordinates of items on the data array to tiles.
		* @param:  x - the x coordinate of an object in the map
		* @param:  y - the y coordinate of an object in the map
		* @return: Vector2Multiply - the scaled coordinates
		*----------------------------------------------------------------------------------------*/
	Vector2 scaleToTile( int x, int y ) 
	{
		return Vector2Multiply( { ( float ) x,( float ) y }, Settings::TILE_DIMENSIONS );
	}
};

/*-------------------------------------------------------------------------------------------------
*  The Hallways class connects the individual rooms on the map via hallways
*------------------------------------------------------------------------------------------------*/
class Hallways
{
	private:

	std::list<BspNode*> leafNodes;  //list to hold all leafnodes for the map
	Floor* floorInput;              //pointer to the Floor object for the map           

	public:

		/*-----------------------------------------------------------------------------------------
		* Hallways(BspNode* node, Floor& floor)
		* -----------------------------------------------------------------------------------------
		* @names:  Evan
		* @brief:  Creates the hallways that connect the individual rooms
		* @param:  node - the root node of the BSP tree containing room data
		* @param:  floor - the reference to the Floor object for the dungeon map
		* @return: none
		*----------------------------------------------------------------------------------------*/
	Hallways( BspNode* node, Floor& floor )
	{
		leafNodes = node->getAllLeafNodes( );
		floorInput = &floor;
		calculateDistanceBetweenRoomCenters( leafNodes );
	}

		//Find rooms whose centers are the closest together
	void calculateDistanceBetweenRoomCenters( std::list<BspNode*> leafNodes );

		//Calculate the distance between the centers of two rooms
	int calculateDistanceFromCenterOfNodes( BspNode* startNode, BspNode* destinationNode );

		//Assign FLOOR char to vector for hallways and locate door placements
	void carveHallwaysIntoMap( BspNode* startNode, BspNode* destinationNode );
};

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
* 
*	-Added Class comments
*/