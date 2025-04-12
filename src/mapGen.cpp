#include <iostream>
#include <vector>
#include <list>

const int WIDTH = 70;                   //width/columns/maximum x of each floor in tiles
const int HEIGHT = 30;                  //height/rows/maximum y of each floor in tiles
const int MINSIZE = 10;                 //minimum for each partition/BSP leaf's width and height

const char WALL = '#';                  //char to represent walls
const char FLOOR = '.';                 //char to represent floors
const char DEBUGPARTITION = '*';        //a wall that is within a partition aka an ok place for rooms to spawn

//BSP STUFF START=============================================================================================================================
// Class representing a node in the BSP tree
class BspNode {
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
	bool split( )
	{
		if ( left || right ) return false;        // If already split, return false

		//Determine whether to split horizontally or vertically
		bool splitHorizontally = rand( ) % 2;
		if ( width > height && width / height >= 1.25 ) splitHorizontally = false;
		else splitHorizontally = true;

		//Alternative logic for determining split direction based on aspect ratio
		//   if ( width > height && width / height >= 1.25 ) splitHorizontally = false;
		//   else if ( height > width && height / width >= 1.25 ) splitHorizontally = true;

		//Another alternative logic for determining split direction based solely on dimensions
		//  if ( width > height ) splitHorizontally = false;
		//  else if ( height > width ) splitHorizontally = true;

		//Calculate the maximum possible split position
		int maxSplit = ( splitHorizontally ? height : width ) - MINSIZE;
		if ( maxSplit <= MINSIZE ) return false;             // not enough space to split

		//Randomly choose a split position
		int split = rand( ) % ( maxSplit - MINSIZE + 1 ) + MINSIZE;

		//Create left and right child nodes based on the split position
		if ( splitHorizontally )
		{
			left = new BspNode( x, y, width, split );
			right = new BspNode( x, y + split - 1, width, height - split );
		}
		else
		{
			left = new BspNode( x, y, split, height );
			right = new BspNode( x + split - 1, y, width - split, height );
		}
		//added split - 1 for make edges around the map
		return true;                          // Return true indicating successful split
	}

	// collect and return all the leaf nodes in the BSP tree, added this method -devon
	std::list<BspNode*> getAllLeafNodes( )
	{
		std::list<BspNode*> leafNodes;        //empty list to store the leaf nodes

		if ( this->left == nullptr )
		{                                     //if this node is a leaf a leaf, add it to the list
			leafNodes.push_back( this );
		}
		else
		{                                     //if this node isn't a leaf, recursively find leaves
			leafNodes.merge( left->getAllLeafNodes( ) );
			leafNodes.merge( right->getAllLeafNodes( ) );
		}
		return leafNodes;
	}
	void addNodeCenterCoordinates( int xCoord, int yCoord )
	{
		this->roomCenterPointXCoordinate = xCoord;
		this->roomCenterPointYCoordinate = yCoord;
	}
};

BspNode* generateBspTree( ) //renamed this and removed const params -devon
{
	if ( MINSIZE <= 0 )
	{
		std::cerr << "Error: MINSIZE must be greater than 0." << std::endl;
		return nullptr;
	}

	BspNode* root = new BspNode( 0, 0, WIDTH, HEIGHT );       // Create the root node
	std::vector<BspNode*> nodes = { root };                   // Vector to store nodes for splitting
	bool split = true;
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

	return root; // Return the root node of the BSP tree
}

// Function to print the dungeon split scheme
void printPartitions( BspNode* node, std::vector<std::vector<char>>& map ) //renamed this -devon
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
//BSP STUFF END=============================================================================================================================
//ROOM STUFF START==========================================================================================================================
int randRange( int minVal, int maxVal ) //replace this with the std function im just lazy
{
	return rand( ) % ( maxVal + 1 - minVal ) + minVal;
}

void makeRectRoom( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )
{
	int xMax = p.x + p.width;
	int yMax = p.y + p.height;

	//define corners of room
	int xLow = randRange( p.x + 1, xMax - 2 * p.width / 3 );
	int xHigh = randRange( xLow + p.width / 2, xMax - 1 );

	int yLow = randRange( p.y + 1, yMax - 2 * p.height / 3 );
	int yHigh = randRange( yLow + p.height / 2, yMax - 1 );

	//take xLow and add half the room width to find center x coordinate, same thing for y center coordinate
	p.addNodeCenterCoordinates( xLow + ( ( xHigh - xLow ) / 2 ), yLow + ( ( yHigh - yLow ) / 2 ) );   //assign the center of the room to the node object -Evan 

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
void makeRoomContainer( BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] )    //Fill partition with '*'
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
//reference: https://www.redblobgames.com/grids/circle-drawing/
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
	int radius = *std::min_element( radBounds, radBounds + 4 ); //the lowest bound

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
void makeRoomOfShape( char shape, BspNode& p, char( &map )[ WIDTH ][ HEIGHT ] ) //this is prob temporary
{
	int randomNumber = std::rand( ) % 3; // Generates 0, 1, or 2

	switch ( randomNumber )
	{
		case 0:
			makeRectRoom( p, map );
			break;
		case 1:
			makeCircleRoom( p, map );
			break;
		case 2:
			makeBlobRoom( p, map );
			break;

		default:
			std::cerr << "tried to make room of unrecognized shape: " << shape;
			break;
	}

	switch ( shape )
	{
		case 'r':
			makeRectRoom( p, map );
			break;
		case 'c':
			makeCircleRoom( p, map );
			break;
		case 'b':
			makeBlobRoom( p, map );
			break;
		case 'f':
			makeRoomContainer( p, map );
			break;

		default:
			std::cerr << "tried to make room of unrecognized shape: " << shape;
			break;
	}
}
//ROOM STUFF END============================================================================================================================
//MAIN STUFF================================================================================================================================
class Floor {
	public:
	char data[ WIDTH ][ HEIGHT ];                                   //TODO make this private with accessor or something like that
	BspNode* rootNode = generateBspTree( );                          //generate the partitions
	//additional member variables are probably data structures for items and enemies

	Floor( char roomShape )
	{
		std::list<BspNode*> leaves = rootNode->getAllLeafNodes( );           //all the leaf nodes/partitons

		//fill in walls everywhere
		for ( int y = 0; y < HEIGHT; y++ )
		{
			for ( int x = 0; x < WIDTH; x++ )
			{
				data[ x ][ y ] = WALL;
			}
		}

		//carve the rooms
		for ( BspNode* leaf : leaves )
		{
			makeRoomContainer( *leaf, data );
			makeRoomOfShape( roomShape, *leaf, data );

			//makeRectRoom(*leaf, data);
			//makeRoomOfShape(roomShape, *leaf, data); //this can make cool rooms-also if u change the shape
		}

		//TODO carve the hallways
		//TODO spawn enemies and items
		//TODO stairwells between floors
	}
	BspNode* getMapRootNode( )
	{
		return rootNode;
	}
};
class Hallways
{

	std::list<BspNode*> leafNodes;         //list to hold all leafnodes for the map
	std::vector<std::vector<int>> roomGraph;
	Floor* floorInput;                      //

	public:
	Hallways( BspNode* node, Floor& floor )
	{
		leafNodes = node->getAllLeafNodes( );
		floorInput = &floor;
		calculateDistanceBetweenRoomCenters( leafNodes );
	}
	//Find rooms whose centers are the closest together
	void calculateDistanceBetweenRoomCenters( std::list<BspNode*> leafNodes )
	{
		BspNode* hallwayCurrentNode = leafNodes.front( );  //select first node in leafNodes list to start
		leafNodes.remove( hallwayCurrentNode );                            //remove the starting node so we don't compare it to itself
		BspNode* nextNodeToConnect = hallwayCurrentNode;
		int smallestDistanceBetweenCenters = WIDTH;

		while ( !leafNodes.empty( ) )
		{
			for ( BspNode* node : leafNodes )
			{
				if ( calculateDistanceFromCenterOfNodes( hallwayCurrentNode, node ) < smallestDistanceBetweenCenters )
				{
					nextNodeToConnect = node;
					smallestDistanceBetweenCenters = calculateDistanceFromCenterOfNodes( hallwayCurrentNode, node );
				}
			}
			carveHallwaysIntoMap( hallwayCurrentNode, nextNodeToConnect );
			hallwayCurrentNode = nextNodeToConnect;
			leafNodes.remove( nextNodeToConnect );
			nextNodeToConnect = nullptr;
			smallestDistanceBetweenCenters = WIDTH;
		}
	}
	//Calculate the distance between centers
	int calculateDistanceFromCenterOfNodes( BspNode* startNode, BspNode* destinationNode )
	{
		int distanceBetweenCenters = 0;
		int differenceBetweenXCoordinates = startNode->roomCenterPointXCoordinate - destinationNode->roomCenterPointXCoordinate;
		int differenceBetweenYCoordinates = startNode->roomCenterPointYCoordinate - destinationNode->roomCenterPointYCoordinate;

		//Pythagorean Theorum,  distanceBetweenRoomCenters = sqrt( a^2 + b^2 )
		distanceBetweenCenters = sqrt( ( differenceBetweenXCoordinates * differenceBetweenXCoordinates ) +
												 ( differenceBetweenYCoordinates * differenceBetweenYCoordinates ) );
		return distanceBetweenCenters;
	}
	//Assign FLOOR char to vector for hallways
	void carveHallwaysIntoMap( BspNode* startNode, BspNode* destinationNode )
	{
		int startNodeXCoordinate = startNode->roomCenterPointXCoordinate;
		int startingNodeYCoordinate = startNode->roomCenterPointYCoordinate;
		int destinationNodeXCoordinate = destinationNode->roomCenterPointXCoordinate;
		int destinationNodeYCoordinate = destinationNode->roomCenterPointYCoordinate;

		int currentX = startNodeXCoordinate;
		int currentY = startingNodeYCoordinate;

		while ( currentX != destinationNodeXCoordinate )
		{
			currentX += ( destinationNodeXCoordinate > currentX ) ? 1 : -1;  //ternary operator determines if hallway is carving to the left or right
			floorInput->data[ currentX ][ currentY ] = FLOOR;
			floorInput->data[ currentX ][ currentY - 1 ] = FLOOR;
			floorInput->data[ currentX ][ currentY + 1 ] = FLOOR;
		}
		while ( currentY != destinationNodeYCoordinate )
		{
			currentY += ( destinationNodeYCoordinate > currentY ) ? 1 : -1;  //ternary operator determines if hallway is carving upward or downward
			floorInput->data[ currentX ][ currentY ] = FLOOR;
			floorInput->data[ currentX - 1 ][ currentY ] = FLOOR;
			floorInput->data[ currentX + 1 ][ currentY ] = FLOOR;
		}
	}
};
//int main( )
//{
//   srand( ( unsigned int ) time( 0 ) );                    //seed the random number generator
//
//   Floor floor( 'r' );                                //test floor
//   Floor floor( );
//
//
//   BspNode* rootNodePTR = floor.getMapRootNode( );
//   Hallways hallways( rootNodePTR, floor );         //Create hallways
//
//   //print the floor
//   for ( int y = 0; y < HEIGHT; y++ )
//   {
//      for ( int x = 0; x < WIDTH; x++ )
//      {
//         std::cout << floor.data[ x ][ y ];
//      }
//      std::cout << "\n";
//   }
//   return 0;

