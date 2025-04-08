//Notes: - We should probably try to keep every line under 100 characters

#pragma once

#include <raylib.h>
#include <list>
#include <vector>
#include <random>

const int WIDTH = 70;                   //width/columns/maximum x of each floor in tiles
const int HEIGHT = 30;                  //height/rows/maximum y of each floor in tiles
const int MINSIZE = 10;                 //minimum for each partition/BSP leaf's width and height

const int TILE_SIZE = 24;               //The x & y size of each tile in the game world in pixels

const char WALL = '#';                  //char to represent walls
const char FLOOR = '.';                 //char to represent floors
const char DEBUGPARTITION = '*';        //a wall that is within a partition aka an ok place for rooms to spawn
const char PLAYER = 'p';                //represents player spawn

//BSP STUFF START=============================================================================================================================
// Class representing a node in the BSP tree

class BspNode 
{
public:

    int x, y, width, height;                // position and size of the node
    BspNode* left;                          // pointer to the left child node
    BspNode* right;                         // Pointer to the right child node
    int roomCenterPointXCoordinate;         // x value of the room center point coordinates
    int roomCenterPointYCoordinate;         // y value of the room center point coordinates

    BspNode(int x, int y, int width, int height) :
        x(x), y(y), width(width), height(height), left(nullptr), right(nullptr)
    {
    }

    //Function to split the node into two child nodes
    bool split();

    // collect and return all the leaf nodes in the BSP tree, added this method -devon
    std::list<BspNode*> getAllLeafNodes();

    void addNodeCenterCoordinates(int xCoord, int yCoord);
};

BspNode* generateBspTree(); //renamed this and removed const params -devon

// Function to print the dungeon split scheme
void printPartitions(BspNode* node, std::vector<std::vector<char>>& map); //renamed this -devon

//BSP STUFF END=============================================================================================================================
//ROOM STUFF START==========================================================================================================================

//replace this with the std function im just lazy
int randRange(int minVal, int maxVal);

void makeRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

//Fill partition with '*'
void makeRoomContainer(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeCircleRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeBlobRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

//this is prob temporary
void makeRoomOfShape(char shape, BspNode& p, char(&map)[WIDTH][HEIGHT]);

//ROOM STUFF END============================================================================================================================
//MAIN STUFF================================================================================================================================

class Floor 
{
private:

    std::vector<Rectangle> walls;

public:

    char data[WIDTH][HEIGHT];                                   //TODO make this private with accessor or something like that
    BspNode* rootNode = generateBspTree();                          //generate the partitions
    //additional member variables are probably data structures for items and enemies

    Floor(char roomShape);

    BspNode* getMapRootNode()
    {
        return rootNode;
    }

    std::vector<Rectangle> getWalls()
    {
        return walls;
    }

    Vector2 getPlayerSpawn();
};

class Hallways
{
private:

    std::list<BspNode*> leafNodes;         //list to hold all leafnodes for the map
    std::vector<std::vector<int>> roomGraph;
    Floor* floorInput;                      //

public:

    Hallways(BspNode* node, Floor& floor)
    {
        leafNodes = node->getAllLeafNodes();
        floorInput = &floor;
        calculateDistanceBetweenRoomCenters(leafNodes);
    }

    //Find rooms whose centers are the closest together
    void calculateDistanceBetweenRoomCenters(std::list<BspNode*> leafNodes);

    //Calculate the distance between centers
    int calculateDistanceFromCenterOfNodes(BspNode* startNode, BspNode* destinationNode);

    //Assign FLOOR char to vector for hallways
    void carveHallwaysIntoMap(BspNode* startNode, BspNode* destinationNode);
};