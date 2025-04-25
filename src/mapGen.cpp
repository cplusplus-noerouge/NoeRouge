/*
NoeRouge map generation
Devon, Irene, Evan, Ben S, possible others, 
*/
#include "mapGen.h"
#include <iostream>
#include <vector>
#include <list>

//PARITIONS =============================================================================================================================
// Class representing a node in the BSP tree
bool BspNode::split()
{
    if (left || right) return false;        // If already split, return false

    //Determine whether to split horizontally or vertically
    bool splitHorizontally = rand() % 2;
    if (width > height && width / height >= 1.25) splitHorizontally = false;
    else splitHorizontally = true;

    //Alternative logic for determining split direction based on aspect ratio
    //   if ( width > height && width / height >= 1.25 ) splitHorizontally = false;
    //   else if ( height > width && height / width >= 1.25 ) splitHorizontally = true;

    //Another alternative logic for determining split direction based solely on dimensions
    //  if ( width > height ) splitHorizontally = false;
    //  else if ( height > width ) splitHorizontally = true;

    //Calculate the maximum possible split position
    int maxSplit = (splitHorizontally ? height : width) - MINSIZE;
    if (maxSplit <= MINSIZE) return false;             // not enough space to split

    //Randomly choose a split position
    int split = rand() % (maxSplit - MINSIZE + 1) + MINSIZE;

    //Create left and right child nodes based on the split position
    if (splitHorizontally)
    {
        left = new BspNode(x, y, width, split);
        right = new BspNode(x, y + split - 1, width, height - split);
    }
    else
    {
        left = new BspNode(x, y, split, height);
        right = new BspNode(x + split - 1, y, width - split, height);
    }
    //added split - 1 for make edges around the map
    return true;                          // Return true indicating successful split
}

// collect and return all the leaf nodes in the BSP tree -devon
std::list<BspNode*> BspNode::getAllLeafNodes()
{
    std::list<BspNode*> leafNodes;        //empty list to store the leaf nodes

    if (this->left == nullptr)
    {                                     //if this node is a leaf a leaf, add it to the list
        leafNodes.push_back(this);
    }
    else
    {                                     //if this node isn't a leaf, recursively find leaves
        leafNodes.merge(left->getAllLeafNodes());
        leafNodes.merge(right->getAllLeafNodes());
    }
    return leafNodes;
}

void BspNode::addNodeCenterCoordinates(int xCoord, int yCoord)
{
    this->roomCenterPointXCoordinate = xCoord;
    this->roomCenterPointYCoordinate = yCoord;
}


BspNode* generateBspTree( )
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

//ROOMS==========================================================================================================================
//i don't want to take credit for this stupid function. unfortunately it's obvious who wrote it
int randRange( int minVal, int maxVal )
{
   return rand( ) % ( maxVal + 1 - minVal ) + minVal;
}

/*--------------------------------------------------------------------------------------------
* makeRectRoom() and makeCircleRoom() carve out floor tiles inside the partition in a shape
* - devon
* param BspNode& p: the partition to put the room
* param char&map[][]: pass by ref to the array of map data
* return: the data in char&map[][] is altered
--------------------------------------------------------------------------------------------*/
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

//a function that was just for testing and should be deleted but first it needs to be removed from the doors code -devon
//Fill partition with DEBUGPARTITION
void makeRoomContainer(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
    int xMax = p.x + p.width;
    int yMax = p.y + p.height;

    //put room in the map
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x > p.x && x < xMax && y > p.y && y < yMax)
            {
                map[x][y] = DEBUGPARTITION;
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

/*--------------------------------------------------------------------------------------------
* makeRandRoomShape() calls two room making functions that overlap into one room
* - devon, ben
* param BspNode& p: the partition to put the room
* param char&map[][]: pass by ref to the array of map data
* return: the data in char&map[][] is altered by the called functions
--------------------------------------------------------------------------------------------*/
void makeRandRoomShape(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
   //anyone feel free to remove the for loop if 2 overlapping room shapes isn't working
   for ( int i = 0; i < 2; i++ )
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

//FLOOR================================================================================================================================
/*--------------------------------------------------------------------------------------------
* Floor() constructor. all the generation for the floor happens here
* - devon
--------------------------------------------------------------------------------------------*/
Floor::Floor()
{
    walls = std::vector<Rectangle>();
    std::list<BspNode*> leaves = rootNode->getAllLeafNodes();           //all the leaf nodes/partitions

    //fill in walls everywhere
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            data[x][y] = WALL;
        }
    }

    //carve the rooms
    for (BspNode* leaf : leaves)
    {
        makeRoomContainer(*leaf, data);
        makeRandRoomShape(*leaf, data);
    }

    Hallways hallways(rootNode, *this);         //Create hallways

    //make the walls into rectangles
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (data[x][y] == WALL || data[x][y] == DEBUGPARTITION)
            {
                Rectangle rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                walls.push_back(rect);
            }
        }
    }

    objHandler = new ObjectHandler;             //make the object handler

    //create ladders between floors. could be changed to guarantee they are a certain distance apart or something
    BspNode* ladderUpNode = leaves.front();
    ladderUpX = ladderUpNode->roomCenterPointXCoordinate;
    ladderUpY = ladderUpNode->roomCenterPointYCoordinate;

    data[ladderUpX][ladderUpY] = LADDER_UP;

    BspNode* ladderDownNode = leaves.back();
    ladderDownX = ladderDownNode->roomCenterPointXCoordinate;
    ladderDownY = ladderDownNode->roomCenterPointYCoordinate;

    data[ladderDownX][ladderDownY] = LADDER_DOWN;

    //make the ladder objects
    objHandler->createLadder(getLadderUpLocation( ), 1);
    objHandler->createLadder( getLadderDownLocation( ), -1);

    //make the door objects
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (data[x][y] == DOOR)
            {
                objHandler->createDoor({(float)x * TILE_SIZE,(float)y * TILE_SIZE });
            }
        }
    }

/*--------------------------------------------------------------------------------------------
* Enemy spawning happens here, yup I just undid two hours of work trying to git push, idk I'll talk about it on Monday
* - Ben
--------------------------------------------------------------------------------------------*/
    for ( BspNode* enemy : leaves )
    {  //the rand( ) % enemyX + 2 could be anything i just choose a small number close to the center
       int enemyX = enemy->roomCenterPointXCoordinate;
       enemyX = rand( ) % enemyX + 2;

       int enemyY = enemy->roomCenterPointYCoordinate;
       enemyY = rand( ) % enemyY + 2;

       data[ enemyX ][ enemyY ] = ENEMY;
    }

    //prints the floor in the console. this is for debugging so we can see the stuff that doesn't have graphics yet like doors and ladders
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            std::cout << data[x][y];
        }
        std::cout << "\n";
    }
}

/*
returns the ladder up and ladder down location as a vector2
returns the location as pixels
parameters - none
*/
Vector2 Floor::getLadderUpLocation()
{
    return { (float)ladderUpX * TILE_SIZE, (float)ladderUpY * TILE_SIZE };
}

Vector2 Floor::getLadderDownLocation( )
{
   return { ( float ) ladderDownX * TILE_SIZE, ( float ) ladderDownY * TILE_SIZE };
}
Vector2 Floor::getEnemySpawn( )
{
  
   for ( int y = 0; y < HEIGHT; y++ )
   {
      for ( int x = 0; x < WIDTH; x++ )
      {
         if ( data[ x ][ y ] == FLOOR )

         {
            return { ( float ) x * TILE_SIZE, ( float ) y * TILE_SIZE };
         }
      }
   }
   std::cout << std::endl;
}

//HALLWAYS==========================================================================================================================
/*--------------------------------------------------------------------------------------------
* Hallways connected from the middle of each room
* - Evan, doors by Ben
--------------------------------------------------------------------------------------------*/
void Hallways::calculateDistanceBetweenRoomCenters(std::list<BspNode*> leafNodes)
{
    BspNode* hallwayCurrentNode = leafNodes.front();  //select first node in leafNodes list to start
    leafNodes.remove(hallwayCurrentNode);                            //remove the starting node so we don't compare it to itself
    BspNode* nextNodeToConnect = hallwayCurrentNode;
    int smallestDistanceBetweenCenters = WIDTH;

    while (!leafNodes.empty())
    {
        for (BspNode* node : leafNodes)
        {
            if (calculateDistanceFromCenterOfNodes(hallwayCurrentNode, node) < smallestDistanceBetweenCenters)
            {
                nextNodeToConnect = node;
                smallestDistanceBetweenCenters = calculateDistanceFromCenterOfNodes(hallwayCurrentNode, node);
            }
        }
        carveHallwaysIntoMap(hallwayCurrentNode, nextNodeToConnect);
        hallwayCurrentNode = nextNodeToConnect;
        leafNodes.remove(nextNodeToConnect);
        nextNodeToConnect = nullptr;
        smallestDistanceBetweenCenters = WIDTH;
    }
}

int Hallways::calculateDistanceFromCenterOfNodes(BspNode* startNode, BspNode* destinationNode)
{
    int distanceBetweenCenters = 0;
    int differenceBetweenXCoordinates = startNode->roomCenterPointXCoordinate - destinationNode->roomCenterPointXCoordinate;
    int differenceBetweenYCoordinates = startNode->roomCenterPointYCoordinate - destinationNode->roomCenterPointYCoordinate;

    //Pythagorean Theorum,  distanceBetweenRoomCenters = sqrt( a^2 + b^2 )
    distanceBetweenCenters = sqrt((differenceBetweenXCoordinates * differenceBetweenXCoordinates) +
        (differenceBetweenYCoordinates * differenceBetweenYCoordinates));
    return distanceBetweenCenters;
}

void Hallways::carveHallwaysIntoMap(BspNode* startNode, BspNode* destinationNode)
{

    int startingNodeXCoordinate = startNode->roomCenterPointXCoordinate;
    int startingNodeYCoordinate = startNode->roomCenterPointYCoordinate;
    int destinationNodeXCoordinate = destinationNode->roomCenterPointXCoordinate;
    int destinationNodeYCoordinate = destinationNode->roomCenterPointYCoordinate;

    bool isDoorPlaced = false;

    int currentX = startingNodeXCoordinate;
    int currentY = startingNodeYCoordinate;

    while (currentX != destinationNodeXCoordinate)
    {

        currentX += (destinationNodeXCoordinate > currentX) ? 1 : -1;  //ternary operator determines if hallway is carving to the left or right
        //adding doors here, note it works but not well and can leave gaps
        if (isDoorPlaced != true && floorInput->data[currentX][currentY] == DEBUGPARTITION)
        { // if you remove the "isDoorPlaced != true" it fills in the whole hallway which could be useful
            floorInput->data[currentX][currentY] = DOOR;
            floorInput->data[currentX][currentY - 1] = DOOR;
            floorInput->data[currentX][currentY + 1] = DOOR;
            isDoorPlaced = true;
        }
        else {
            floorInput->data[currentX][currentY] = FLOOR;
            floorInput->data[currentX][currentY - 1] = FLOOR;
            floorInput->data[currentX][currentY + 1] = FLOOR;
        }

    }
    while (currentY != destinationNodeYCoordinate)
    {

        currentY += (destinationNodeYCoordinate > currentY) ? 1 : -1;  //ternary operator determines if hallway is carving upward or downward
        //adding doors here, note it works but not well and can leave gaps
        if (isDoorPlaced != true && floorInput->data[currentX][currentY] == DEBUGPARTITION)
        {
            floorInput->data[currentX][currentY] = DOOR;
            floorInput->data[currentX - 1][currentY] = DOOR;
            floorInput->data[currentX + 1][currentY] = DOOR;
            isDoorPlaced = true;
        }
        else {
            floorInput->data[currentX][currentY] = FLOOR;
            floorInput->data[currentX - 1][currentY] = FLOOR;
            floorInput->data[currentX + 1][currentY] = FLOOR;
        }
    }
}
