/* NoeRouge - mapGen.cpp
* Worked on by: Devon, Irene, Evan, Ben S */

#include "mapGen.h"                 //The .h file for this class
#include <generateTileSprites.h>    //Class that generates sprites for every tile in the map

/*-------------------------------------------------------------------------------------------------
*  The BspNode class creates nodes in a binary tree that will hold room data
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* split()
	* ---------------------------------------------------------------------------------------------
	* @names:  Irene,
	* @brief:  Splits the node into two child nodes
	* @param:  none
	* @return: bool - true when split was successful, else false
	*--------------------------------------------------------------------------------------------*/
bool BspNode::split( )
{
	if ( left || right ) return false;        // If already split, return false

		//Determine whether to split horizontally or vertically
	bool splitHorizontally = rand( ) % 2;
	if ( width > height && width / height >= 1.25 ) splitHorizontally = false;
	else splitHorizontally = true;

		 //Calculate the maximum possible split position
	int maxSplit = ( splitHorizontally ? height : width ) - MINSIZE;
	if ( maxSplit <= MINSIZE ) return false;             // not enough space to split

		//Randomly choose a split position
	int split = rand( ) % ( maxSplit - MINSIZE + 1 ) + MINSIZE;

		//Create left and right child nodes based on the split position
	if ( splitHorizontally )
	{
		left = new BspNode( x, y, width, split );
		right = new BspNode( x, y + split, width, height - split );
	}
	else
	{
		left = new BspNode( x, y, split, height );
		right = new BspNode( x + split, y, width - split, height );
	}
	return true;    // Return true indicating successful split
}

	/*---------------------------------------------------------------------------------------------
	* getAllLeafNodes()
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  collect and return all the leaf nodes in the BSP tree -devon
	* @param:  none
	* @return: list<BspNode*> - Pointer to a list of all BSP nodes
	*--------------------------------------------------------------------------------------------*/
std::list<BspNode*> BspNode::getAllLeafNodes( )
{
	std::list<BspNode*> leafNodes;  //empty list to store the leaf nodes

		//if this node is a leaf a leaf, add it to the list
	if ( this->left == nullptr )
	{
		leafNodes.push_back( this );
	}
		 //if this node isn't a leaf, recursively find leaves
	else
	{
		leafNodes.merge( left->getAllLeafNodes( ) );
		leafNodes.merge( right->getAllLeafNodes( ) );
	}
	return leafNodes;
}
	/*---------------------------------------------------------------------------------------------
	* addNodeCenterCoordinates(int xCoord, int yCoord)
	* ---------------------------------------------------------------------------------------------
	* @names:  Evan
	* @brief:  Adds the coordinates for the room center of the node
	* @param:  xCoord - The x coordinate of the room center of the node
	* @param:  yCoord - The y coordinate of the room center of the node
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void BspNode::addNodeCenterCoordinates( int xCoord, int yCoord )
{
	this->roomCenterPointXCoordinate = xCoord;
	this->roomCenterPointYCoordinate = yCoord;
}

	/*---------------------------------------------------------------------------------------------
	* generateBspTree( )
	* ---------------------------------------------------------------------------------------------
	* @names:  Irene, Devon
	* @brief:  Creates the BSP tree where each leaf node holds that data for one room in the
	*          dungeon map
	* @param:  none
	* @return: BspNode* - Pointer to the BSP tree
	*--------------------------------------------------------------------------------------------*/
BspNode* generateBspTree( )
{
	BspNode* root = new BspNode( 0, 0, WIDTH, HEIGHT );  // Create the root node
	std::vector<BspNode*> nodes = { root };              // Vector to store nodes for splitting
	bool split = true;

	if ( MINSIZE <= 0 )
	{
		std::cerr << "Error: MINSIZE must be greater than 0." << std::endl;
		return nullptr;
	}
	while ( split )
	{
		split = false;
		std::vector<BspNode*> newNodes;
		for ( BspNode* node : nodes )
		{
			if ( node->split( ) )
			{
				newNodes.push_back( node->left );
				newNodes.push_back( node->right );
				split = true;
			}
		}
		nodes.insert( nodes.end( ), newNodes.begin( ), newNodes.end( ) );
	}

	return root;    // Return the root node of the BSP tree
}

	/*---------------------------------------------------------------------------------------------
	* printPartitions( BspNode* node, std::vector<std::vector<char>>& map )
	* ---------------------------------------------------------------------------------------------
	* @names:  Irene
	* @brief:  Function to print the dungeon split scheme
	* @param:  node - The root node of the BSP tree
	* @param:  map  - The vector that holds the map data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void printPartitions( BspNode* node, std::vector<std::vector<char>>& map )
{
	if ( !node ) return;

		// Mark the boundaries of the node with '-' or '|'
	for ( int i = node->x; i < node->x + node->width; ++i )
	{
		map[ node->y ][ i ] = '-';
		map[ node->y + node->height - 1 ][ i ] = '-';
	}
	for ( int i = node->y; i < node->y + node->height; ++i )
	{
		map[ i ][ node->x ] = '|';
		map[ i ][ node->x + node->width - 1 ] = '|';
	}

		 // Recursively print the left and right child nodes
	printPartitions( node->left, map );
	printPartitions( node->right, map );
}

/*-------------------------------------------------------------------------------------------------
*  The Room class creates individual rooms for each node of the BSP tree
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* randRange( int minVal, int maxVal )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  Gets a random number between a lower and upper bounds
	* @param:  minVal - lower bound for randome number generation
	* @param:  maxVal - upper bound for randome number generation
	* @return: int - random generated int between minVal and maxVal
	*--------------------------------------------------------------------------------------------*/
int randRange( int minVal, int maxVal )
{
	return rand( ) % ( maxVal + 1 - minVal ) + minVal;
}

	/*---------------------------------------------------------------------------------------------
	* makeRectRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  carve out floor tiles inside the partition in a rectangle shape
	* @param:  p - the partition to put the room
	* @param:  map - pass by ref to the array of map data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void makeRectRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
	int xMax = p.x + p.width;
	int yMax = p.y + p.height;

		//define corners of room
	int xLow = randRange( p.x + 1, xMax - 2 * p.width / 3 );
	int xHigh = randRange( xLow + p.width / 2, xMax - 1 );

	int yLow = randRange( p.y + 1, yMax - 2 * p.height / 3 );
	int yHigh = randRange( yLow + p.height / 2, yMax - 1 );

		 //take xLow and add half the room width to find center x coordinate, repeat for y center coordinate
		 //assign the center of the room to the node object -Evan 
	p.addNodeCenterCoordinates( xLow + ( ( xHigh - xLow ) / 2 ), yLow + ( ( yHigh - yLow ) / 2 ) );

		 //put room in the map
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			if ( x >= xLow && x <= xHigh && y >= yLow && y <= yHigh )
			{
				map[ x ][ y ] = FLOOR;
			}
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* makeCircleRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  carve out floor tiles inside the partition in a circle shape
	* @param:  p - the partition to put the room
	* @param:  map - pass by ref to the array of map data
	* @return: none
	* @note:   https://www.redblobgames.com/grids/circle-drawing/
	*--------------------------------------------------------------------------------------------*/
void makeCircleRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
	int xMax = p.x + p.width;
	int yMax = p.y + p.height;

		 //center of circle spawns in the center 9th of partition
	int xCenter = randRange( p.x + p.width / 3, xMax - p.width / 3 );
	int yCenter = randRange( p.y + p.height / 3, yMax - p.height / 3 );

		 //Add center coordinates to this BspNode object
	p.addNodeCenterCoordinates( xCenter, yCenter );

		 //determine radius - always the maximum it can be while staying in bounds
	int radBounds[ 4 ] = {
		xCenter - p.x, //left bound
		xMax - xCenter, //right bound
		yCenter - p.y,  // top bound
		yMax - yCenter, //bot bound
	};
	int radius = *std::min_element( radBounds, radBounds + 4 );  //the lowest bound

		 //bounding box of the circle
	int top = ( int ) ceil( yCenter - radius );
	int bottom = ( int ) floor( yCenter + radius );
	int left = ( int ) ceil( xCenter - radius );
	int right = ( int ) floor( xCenter + radius );

		//put room in the map
	for ( int y = top; y < bottom; y++ )
	{
		for ( int x = left; x < right; x++ )
		{
			int dx = xCenter - x;
			int dy = yCenter - y;
			int distance_squared = dx * dx + dy * dy;
			if ( distance_squared < radius * radius )
			{
				map[ x ][ y ] = FLOOR;
			}
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* makeRoomContainer(BspNode& p, char(&map)[WIDTH][HEIGHT])
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  Fill partition with DEBUGPARTITION char '*'
	* @param:  p - the partition to put the room
	* @param:  map - pass by ref to the array of map data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void makeRoomContainer( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
	int xMax = p.x + p.width;
	int yMax = p.y + p.height;

		//put room in the map
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			if ( x > p.x && x < xMax && y > p.y && y < yMax )
			{
				map[ x ][ y ] = DEBUGPARTITION;
			}
		}
	}
}

/*  this is unused bc it looks like a limestone cave not a spaceship -devon
void makeBlobRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
   int xMax = p.x + p.width;
   int yMax = p.y + p.height;
   int iterations = p.width * p.height;

   //starting coords (always the center of partition)
   int cursorX = p.x + p.width / 2;
   int cursorY = p.y + p.height / 2;

   //Add center coordinates to this BspNode object
   p.addNodeCenterCoordinates( cursorX, cursorY );

   //the cursor wanders around smashing down walls
   for ( int i = 0; i < iterations; i++ )
   {
	  map[ cursorX ][ cursorY ] = FLOOR;

	  int dx = randRange( -1, 1 );
	  int dy = randRange( -1, 1 );

	  bool inRangeX = cursorX + dx > p.x && cursorX + dx < xMax;
	  bool inRangeY = cursorY + dy > p.y && cursorY + dy < yMax;

	  //keeps the room inside the partition
	  if ( inRangeX && inRangeY )
	  {
		 cursorX += dx;
		 cursorY += dy;
	  }
   }
}
*/

	/*---------------------------------------------------------------------------------------------
	* makeRandRoomShape(BspNode& p, char(&map)[WIDTH][HEIGHT])
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon, Ben
	* @brief:  calls one or two room making functions that overlap into one room
	* @param:  p - the partition to put the room
	* @param:  map - pass by ref to the array of map data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void makeRandRoomShape( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
   //anyone feel free to remove the for loop if 2 overlapping room shapes isn't working
	int overlapCount = ( std::rand( ) % 2 ) + 1;
	for ( int i = 0; i < overlapCount; i++ )
	{
		int randomNumber = std::rand( ) % 2;
		switch ( randomNumber )
		{
			case 0:
				makeRectRoom( p, map );
				break;
			case 1:
				makeCircleRoom( p, map );
				break;
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* cullDoorIfBad(char(&map)[WIDTH][HEIGHT], int x, int y)
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  helper function for cullBadDoors(). Erases doors if they aren't sandwiched between walls
	* @param:  map - pass by ref to the array of map data
	* @param:  x - x coordinate of the door location in the map
	* @param:  y - y coordinate of the door location in the map
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void cullDoorIfBad( char( &map )[ WIDTH ][ HEIGHT ], int x, int y )
{
	char left = map[ x - 1 ][ y ];      //The charactter to the left of the door object in the map
	char right = map[ x + 1 ][ y ];     //The charactter to the right of the door object in the map
	char above = map[ x ][ y - 1 ];     //The charactter above the door object in the map
	char below = map[ x ][ y + 1 ];     //The charactter below the door object in the map

	bool goodDoorX = left != FLOOR && right != FLOOR;
	bool goodDoorY = above != FLOOR && below != FLOOR;

	if ( !( goodDoorX || goodDoorY ) )
	{
		map[ x ][ y ] = FLOOR;

			//check for doors to the left or above that were mistakenly skipped when map[x,y] was a door
		if ( left == DOOR )
			cullDoorIfBad( map, x - 1, y );
		if ( above == DOOR )
			cullDoorIfBad( map, x, y - 1 );
	}
}

	/*---------------------------------------------------------------------------------------------
	* cullBadDoors(char(&map)[WIDTH][HEIGHT])
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon
	* @brief:  replaces doors that aren't sandwiched between walls (aka bad doors) with floors
	* @param:  map - pass by ref to the array of map data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void cullBadDoors( char( &map )[ WIDTH ][ HEIGHT ] )
{
	bool inBoundsX, inBoundsY, goodDoorY, goodDoorX;

	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
				//skip non-door tiles
			if ( map[ x ][ y ] != DOOR )
				continue;

			inBoundsX = ( x != 0 ) && ( x != WIDTH - 1 );
			inBoundsY = ( y != 0 ) && ( y != HEIGHT - 1 );

				//skip edge tiles
			if ( !inBoundsX || !inBoundsY )   //skip edge tiles
				continue;

				//for all non-edge door tiles:
			cullDoorIfBad( map, x, y );
		}
	}
}

/*-------------------------------------------------------------------------------------------------
*  The Floor class creates the floors, walls, ladders, and doors in the map
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* generateMapData()
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon, Evan, someone else I think?
	* @brief:  generates the floors and walls, and determines spawn locations for ladders and doors
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Floor::generateMapData( )
{
	leafPartitions = rootNode->getAllLeafNodes( );           //all the leaf nodes/partitions

		//fill in walls everywhere
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			data[ x ][ y ] = WALL;
		}
	}

		//carve the rooms
	for ( BspNode* leaf : leafPartitions )
	{
		makeRoomContainer( *leaf, data );
		makeRandRoomShape( *leaf, data );
	}

		//make sure the bottom and left edges are walls
	for ( int x = 0; x < WIDTH; x++ )
	{
		data[ x ][ HEIGHT - 1 ] = WALL;
	}
	for ( int y = 0; y < HEIGHT; y++ )
	{
		data[ WIDTH - 1 ][ y ] = WALL;
	}

		//Create hallways and doors
	Hallways hallways( rootNode, *this );
	cullBadDoors( data );

		//create ladders between floors. could be changed to guarantee they are a certain distance apart or something
	BspNode* ladderUpNode = leafPartitions.front( );
	int ladderUpX = ladderUpNode->roomCenterPointXCoordinate;
	int ladderUpY = ladderUpNode->roomCenterPointYCoordinate;

	data[ ladderUpX ][ ladderUpY ] = LADDER_UP;
	ladderUpLocation = scaleToTile( ladderUpX, ladderUpY );

	BspNode* ladderDownNode = leafPartitions.back( );
	int ladderDownX = ladderDownNode->roomCenterPointXCoordinate;
	int ladderDownY = ladderDownNode->roomCenterPointYCoordinate;

	data[ ladderDownX ][ ladderDownY ] = LADDER_DOWN;
	ladderDownLocation = scaleToTile( ladderDownX, ladderDownY );

		//make the walls into rectangles that can be rendered
	walls = std::vector<Rectangle>( );
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			if ( data[ x ][ y ] == WALL || data[ x ][ y ] == DEBUGPARTITION )
			{
				Rectangle rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				walls.push_back( rect );
			}
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* generateObjects()
	* ---------------------------------------------------------------------------------------------
	* @names:  Devon, Ben S
	* @brief:  creates the objects on the floor: ladders, doors, enemies, and anything added in the future
	* @param:  none
	* @return: none (adds new entities to objHandler)
	*--------------------------------------------------------------------------------------------*/
void Floor::generateObjects( )
{
		//make the object handler
	objHandler = new ObjectHandler;

		//make the ladder objects
	objHandler->createLadder( getLadderUpLocation( ), true );
	objHandler->createLadder( getLadderDownLocation( ), false );

		//make the door objects
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			if ( data[ x ][ y ] == DOOR )
			{
				objHandler->createDoor( scaleToTile( x, y ) );
			}
		}
	}

		//make health pickup object
	BspNode* hpPickupNode = *std::next( leafPartitions.begin( ) );
	float hpPickupX = hpPickupNode->roomCenterPointXCoordinate;
	float hpPickupY = hpPickupNode->roomCenterPointYCoordinate;
	objHandler->createHpPickup( { hpPickupX * TILE_SIZE, hpPickupY * TILE_SIZE } );

		// Enemy spawning happens here, yup I just undid two hours of work trying to git push, idk I'll talk about it on Monday
		// - Ben
	for ( BspNode* enemy : leafPartitions )
	{
			//the rand( ) % enemyX + 2 could be anything i just choose a small number close to the center
		int enemyX = enemy->roomCenterPointXCoordinate;
		enemyX = rand( ) % enemyX + 2;

		int enemyY = enemy->roomCenterPointYCoordinate;
		enemyY = rand( ) % enemyY + 2;

		if ( data[ enemyX ][ enemyY ] == FLOOR )
		{
			data[ enemyX ][ enemyY ] = ENEMY;

				//create an enemy object. - devon
			Vector2 EnemyPos = scaleToTile( enemyX, enemyY );
			objHandler->createEnemy( EnemyPos );
		}
	}
}

	/*---------------------------------------------------------------------------------------------
	* Floor()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  all the generation for everything on the floor (except the player) is called here
	* @param:  none
	* @return: none
	*--------------------------------------------------------------------------------------------*/
Floor::Floor( )
{
	generateMapData( );
	generateObjects( );
	_tileSprites = generateTileSprites( data );

		//prints the floor in the console. 
	for ( int y = 0; y < HEIGHT; y++ )
	{
		for ( int x = 0; x < WIDTH; x++ )
		{
			std::cout << data[ x ][ y ];
		}
		std::cout << "\n";
	}
}

//void Floor::setTileSprites( std::vector<Sprite> tileSprites )
//{
//   _tileSprites = tileSprites;
//}

	/*---------------------------------------------------------------------------------------------
	* getLadderUpLocation()
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Gets the ladder up and ladder down location
	* @param:  none
	* @return: Vector2 - ladder up and ladder down location in pixels as a vector2
	*--------------------------------------------------------------------------------------------*/
Vector2 Floor::getLadderUpLocation( )
{
	return ladderUpLocation;
}

Vector2 Floor::getLadderDownLocation( )
{
	return ladderDownLocation;
}

	/*---------------------------------------------------------------------------------------------
	* getEnemySpawn( )
	* ---------------------------------------------------------------------------------------------
	* @names:
	* @brief:  Gets Enemy spawn location
	* @param:  none
	* @return: Vector2 - Enemy spawn location in pixels as a vector2
	*--------------------------------------------------------------------------------------------*/
Vector2 Floor::getEnemySpawn( )
{

	for ( int y = 1; y < HEIGHT; y++ )
	{
		for ( int x = 1; x < WIDTH; x++ )
		{
			if ( data[ x ][ y ] == FLOOR )

			{
				return scaleToTile( x, y );
			}
		}
	}
	std::cout << std::endl;
}

/*-------------------------------------------------------------------------------------------------
*  The Hallways class connects the individual rooms on the map via hallways
*------------------------------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------------------------
	* calculateDistanceBetweenRoomCenters(std::list<BspNode*> leafNodes)
	* ---------------------------------------------------------------------------------------------
	* @names:  Evan, Ben S
	* @brief:  Calculates which 2 rooms in the map are the closest together and connects those rooms
	*          with a hallway, loops until all rooms are connected. Uses Prim's algorithm
	* @param:  leafNodes - list of all nodes that contain room data
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Hallways::calculateDistanceBetweenRoomCenters( std::list<BspNode*> leafNodes )
{
	BspNode* hallwayCurrentNode = leafNodes.front( ); //select first node in leafNodes list to start
	leafNodes.remove( hallwayCurrentNode );           //remove the starting node 
	BspNode* nextNodeToConnect = hallwayCurrentNode;  //to start set current node as next node
	int smallestDistanceBetweenCenters = WIDTH;       //Holds the smallest found distance in loop

	while ( !leafNodes.empty( ) )
	{
			//iterate through all remaining nodes to find the closest nodes by comparing center points
		for ( BspNode* node : leafNodes )
		{
			if ( calculateDistanceFromCenterOfNodes( hallwayCurrentNode, node ) <
				 smallestDistanceBetweenCenters )
			{
				nextNodeToConnect = node;
				smallestDistanceBetweenCenters =
					calculateDistanceFromCenterOfNodes( hallwayCurrentNode, node );
			}
		}
		carveHallwaysIntoMap( hallwayCurrentNode, nextNodeToConnect );   //connects the two closest rooms
		hallwayCurrentNode = nextNodeToConnect;  //move current node to be the last room connected
		leafNodes.remove( nextNodeToConnect );   //remove the now connected node from the list
		nextNodeToConnect = nullptr;             //reset for the next iteration of the loop
		smallestDistanceBetweenCenters = WIDTH;  //reset for the next iteration of the loop
	}
}
	/*---------------------------------------------------------------------------------------------
	* calculateDistanceFromCenterOfNodes(BspNode* startNode, BspNode* destinationNode)
	* ---------------------------------------------------------------------------------------------
	* @names:  Evan
	* @brief:  Uses pathagorean theorum to calculate the distance between two room's centers
	* @param:  startNode - the node that a hallway would start from
	* @param:  destinationNode - the node that a hallway would go to
	* @return: int - the distance between the two room's centers
	*--------------------------------------------------------------------------------------------*/
int Hallways::calculateDistanceFromCenterOfNodes( BspNode* startNode, BspNode* destinationNode )
{
	int distanceBetweenCenters = 0;
	int differenceBetweenXCoordinates = startNode->roomCenterPointXCoordinate 
										- destinationNode->roomCenterPointXCoordinate;
	int differenceBetweenYCoordinates = startNode->roomCenterPointYCoordinate 
										- destinationNode->roomCenterPointYCoordinate;

		//Pythagorean Theorum,  distanceBetweenRoomCenters = sqrt( a^2 + b^2 )
	distanceBetweenCenters = sqrt( ( differenceBetweenXCoordinates * differenceBetweenXCoordinates ) +
								   ( differenceBetweenYCoordinates * differenceBetweenYCoordinates ) );
	return distanceBetweenCenters;
}
	/*---------------------------------------------------------------------------------------------
	* carveHallwaysIntoMap(BspNode* startNode, BspNode* destinationNode)
	* ---------------------------------------------------------------------------------------------
	* @names:  Evan, Ben S
	* @brief:  Creates the hallways in the dungeon map by moving one tile at a time from the startNode
	*          room center to the destinationNode room center, adds doors to the map
	* @param:  startNode - The starting room of the hallway
	* @param:  destinationNode - The destination room of the node
	* @return: none
	*--------------------------------------------------------------------------------------------*/
void Hallways::carveHallwaysIntoMap( BspNode* startNode, BspNode* destinationNode )
{

	int startingNodeXCoordinate = startNode->roomCenterPointXCoordinate;
	int startingNodeYCoordinate = startNode->roomCenterPointYCoordinate;
	int destinationNodeXCoordinate = destinationNode->roomCenterPointXCoordinate;
	int destinationNodeYCoordinate = destinationNode->roomCenterPointYCoordinate;

	bool isDoorPlaced = false;

	int currentX = startingNodeXCoordinate;
	int currentY = startingNodeYCoordinate;

		//loop until the x coordinate of the destination room equals the current x coordinate
	while ( currentX != destinationNodeXCoordinate )
	{
			//ternary operator determines if hallway is carving to the left or right
		currentX += ( destinationNodeXCoordinate > currentX ) ? 1 : -1;
			//adding doors here, note it works but not well and can leave gaps
		if ( isDoorPlaced != true && floorInput->data[ currentX ][ currentY ] == DEBUGPARTITION )
		{
				// if you remove the "isDoorPlaced != true" it fills in the whole hallway which could be useful
			floorInput->data[ currentX ][ currentY ] = DOOR;
			floorInput->data[ currentX ][ currentY - 1 ] = DOOR;
			floorInput->data[ currentX ][ currentY + 1 ] = DOOR;
			isDoorPlaced = true;
		}
		else
		{
			floorInput->data[ currentX ][ currentY ] = FLOOR;
			floorInput->data[ currentX ][ currentY - 1 ] = FLOOR;
			floorInput->data[ currentX ][ currentY + 1 ] = FLOOR;
		}

	}
		//loop until the y coordinate of the destination room equals the current y coordinate
	while ( currentY != destinationNodeYCoordinate )
	{
			//ternary operator determines if hallway is carving upward or downward
		currentY += ( destinationNodeYCoordinate > currentY ) ? 1 : -1;
			//adding doors here, note it works but not well and can leave gaps
		if ( isDoorPlaced != true && floorInput->data[ currentX ][ currentY ] == DEBUGPARTITION )
		{
			floorInput->data[ currentX ][ currentY ] = DOOR;
			floorInput->data[ currentX - 1 ][ currentY ] = DOOR;
			floorInput->data[ currentX + 1 ][ currentY ] = DOOR;
			isDoorPlaced = true;
		}
		else
		{
			floorInput->data[ currentX ][ currentY ] = FLOOR;
			floorInput->data[ currentX - 1 ][ currentY ] = FLOOR;
			floorInput->data[ currentX + 1 ][ currentY ] = FLOOR;
		}
	}
}

/*  Changes made during commenting by Evan:
*
*	-Added C-style comments above methods to conform to standards
*	 as laid out in project commenting documentation
*
*	-Added inline comments to #includes
*
*   -Added inline comments to some methods
*
*	-General formatting
*/
